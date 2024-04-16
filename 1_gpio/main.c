#include <stdint.h>

#define OUTPUT 1
#define __GPIO_BASE_ADDRESS__ 0x50000000
#define __RESERVED0_SIZE__ 321
#define __RESERVED1_SIZE__ 120
#define __PIN_CNF_SIZE__ 32
#define __BUTTON_1_PIN__ 15
#define __BUTTON_2_PIN__ 16
// #define __BUTTON_3_PIN__ 15
// #define __BUTTON_4_PIN__ 16
#define __LED_1_PIN__ 17
#define __LED_2_PIN__ 18
#define __LED_3_PIN__ 19
#define __LED_4_PIN__ 20
#define GPIO ((NRF_GPIO_REGS*)__GPIO_BASE_ADDRESS__)

typedef struct {
	volatile uint32_t RESERVED0[__RESERVED0_SIZE__];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[__RESERVED1_SIZE__];
	volatile uint32_t PIN_CNF[__PIN_CNF_SIZE__];
} NRF_GPIO_REGS;


void ledMatrixOn() {
	for(int pin_index = __LED_1_PIN__; pin_index <= (__LED_4_PIN__); pin_index++)
		GPIO->OUTCLR = (1<<pin_index);
};

void ledMatrixOff() {
	for(int pin_index = __LED_1_PIN__; pin_index <= (__LED_4_PIN__); pin_index++)
		GPIO->OUTSET = (1<<pin_index);
}


int main(){
	GPIO->PIN_CNF[__BUTTON_1_PIN__] = 0xC;
	GPIO->PIN_CNF[__BUTTON_2_PIN__] = 0xC;
	for(int pin_index = __LED_1_PIN__; pin_index <= (__LED_4_PIN__); pin_index++)
		GPIO->PIN_CNF[pin_index] = OUTPUT;



	int sleep = 0;
	// volatile int mask;
	// volatile int value;
	// volatile int flag;
	#define BUTTON_1_MASK (1<<__BUTTON_1_PIN__)
	#define BUTTON_2_MASK (1<<__BUTTON_2_PIN__)
	while(1) {
		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		// mask  = 1<<__BUTTON_1_PIN__;
		// value = GPIO->IN;
		// flag = value & mask;
		if(!(GPIO->IN & BUTTON_1_MASK))
			ledMatrixOn();


		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		// mask  = 1<<__BUTTON_2_PIN__;
		// value = GPIO->IN;
		// flag = value & mask;
		if(!(GPIO->IN & BUTTON_2_MASK))
			ledMatrixOff();

		sleep = 10000;
		while(--sleep); // Delay

		// Manual sleep
		// ledMatrixOn() ;
		// sleep = 10000*1000;
		// while(--sleep); // Delay
		// ledMatrixOff();
		// sleep = 10000*1000;
		// while(--sleep); // Delay
	}
	return 0;
}
