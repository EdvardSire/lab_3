#include "uart.h"
#include "gpio.h"

void uart_init(){
    GPIO->DIRCLR = (1<<__UART_RX__);
    GPIO->DIRSET = (1<<__UART_TX__);

    UART->PSELRXD = __UART_RX__;
    UART->PSELTXD = __UART_TX__;
    UART->PSELCTS = 0xFFFFFFFF; //NC
    UART->PSELRTS = 0xFFFFFFFF; //NC
    UART->CONFIG = 0; //Disabled
    UART->BAUDRATE = 0x00275000; //9600
    UART->ENABLE = 4; //Enabled
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while(!UART->EVENTS_TXDRDY);
    UART->TASKS_STOPTX = 1;
    UART->EVENTS_TXDRDY = 0;
}

char uart_read(){
    UART->TASKS_STARTRX = 1;
    if(!UART->EVENTS_RXDRDY)
        return '\0';
    UART->EVENTS_RXDRDY = 0;
    return UART->RXD;
}