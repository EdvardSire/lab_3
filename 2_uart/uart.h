#ifndef UART_H
#define UART_H 
#include <stdint.h>

#define __UART_RTS__ 5
#define __UART_TX__ 6
#define __UART_CTS__ 7
#define __UART_RX__ 8

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct  
{
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND;
    uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    uint32_t RESERVER3;
    volatile uint32_t EVENTS_ERROR;
    uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO;
    uint32_t RESERVED5[46];
    volatile uint32_t SHORTS;
    uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    uint32_t RESERVED9;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    uint32_t RESERVED10;
    volatile uint32_t BAUDRATE;
    uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init();
void uart_send(char letter);
char uart_read();

#endif