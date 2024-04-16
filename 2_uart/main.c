#include "gpio.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define BUTTON_1 13
#define BUTTON_2 14
#define BUTTON_3 15
#define BUTTON_4 16
#define LED_1 17
#define LED_2 18
#define LED_3 19
#define LED_4 20


ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }
    return count;
}

void led_matrix_on() {
  for (int i = LED_1; i <= LED_4; i++) {
    GPIO->OUTCLR = (1 << i);
  }
}

void led_matrix_off() {
  for (int i = LED_1; i <= LED_4; i++) {
    GPIO->OUTSET = (1 << i);
  }
}

void led_matrix_toggle() {
  if ((GPIO->OUTSET >> 17) & 1) {
    led_matrix_on();
  } else {
    led_matrix_off();
  }
}

void board_init() {
  GPIO->PIN_CNF[BUTTON_1] = 0xC;
  GPIO->PIN_CNF[BUTTON_2] = 0xC;

  for (int i = LED_1; i <= LED_4; i++) {
    GPIO->DIRSET = (1 << i);
  }
}

#define BUTTON_1_MASK (1 << BUTTON_1)
#define BUTTON_2_MASK (1 << BUTTON_2)

int main() {
  uart_init();
  board_init();

  iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235 ,2022,'B');

  int sleep;
  while (1) {
    if (!(GPIO->IN & BUTTON_1_MASK))
      uart_send('A');

    if (!(GPIO->IN & BUTTON_2_MASK))
      uart_send('B');

    if (uart_read() != '\0')
      led_matrix_toggle();

    sleep = 10000;
    while (--sleep)
      ;
  }
  return 1;
}