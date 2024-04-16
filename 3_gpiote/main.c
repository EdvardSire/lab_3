#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

#define BUTTON_1_PIN 13
#define LED_1_PIN 17
#define LED_2_PIN 18
#define LED_3_PIN 19
#define LED_4_PIN 20
#define OUTPUT 1

int main() {
  GPIO->PIN_CNF[BUTTON_1_PIN] = 0xC;
  for (int pin_index = LED_1_PIN; pin_index <= (LED_4_PIN); pin_index++) {
    GPIO->PIN_CNF[pin_index] = OUTPUT;
    GPIO->OUTSET = (1 << pin_index);
  }

    uint32_t MODE_MASK = (1 << 0);
    uint32_t PSEL_MASK = (13 << 8);
    uint32_t POLARITY_MASK = (1 << 16);
    uint32_t OUTINIT_MASK = 0;
    GPIOTE->CONFIG[0] = MODE_MASK | PSEL_MASK | POLARITY_MASK | OUTINIT_MASK;

  // Create GPIOTE task
  for (int i = 0; i < 4; i++) {
    uint32_t MODE_MASK = (3 << 0);
    uint32_t PSEL_MASK = ((LED_1_PIN + i) << 8);
    uint32_t POLARITY_MASK = (3 << 16);
    uint32_t OUTINIT_MASK = (0 << 20);
    GPIOTE->CONFIG[i+1] = MODE_MASK | PSEL_MASK | POLARITY_MASK | OUTINIT_MASK;
  }

  uint32_t CHANNEL_1_MASK = (1 << 0); 
  uint32_t CHANNEL_2_MASK = (1 << 1);
  uint32_t CHANNEL_3_MASK = (1 << 2);
  uint32_t CHANNEL_4_MASK = (1 << 3);
  PPI->CHEN = CHANNEL_1_MASK | CHANNEL_2_MASK | CHANNEL_3_MASK | CHANNEL_4_MASK;
 
  // EventEndPoint
  PPI->PPI_CH[0].EEP = (uint32_t) & (GPIOTE->IN[0]);
  PPI->PPI_CH[1].EEP = (uint32_t) & (GPIOTE->IN[0]);
  PPI->PPI_CH[2].EEP = (uint32_t) & (GPIOTE->IN[0]);
  PPI->PPI_CH[3].EEP = (uint32_t) & (GPIOTE->IN[0]);

  // TaskEndPoint
  PPI->PPI_CH[0].TEP = (uint32_t) & (GPIOTE->OUT[1]);
  PPI->PPI_CH[1].TEP = (uint32_t) & (GPIOTE->OUT[2]);
  PPI->PPI_CH[2].TEP = (uint32_t) & (GPIOTE->OUT[3]);
  PPI->PPI_CH[3].TEP = (uint32_t) & (GPIOTE->OUT[4]);

  while (1)
    ;
  return 0;
}