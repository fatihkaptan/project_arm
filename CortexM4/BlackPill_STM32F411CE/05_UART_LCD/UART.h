#ifndef __UART_H
#define __UART_H
#include "stm32f4xx.h"  

typedef enum {
  UART_1,
  UART_2,
  UART_6,
} UART_PERIPH;



void UART_Send(int idx, unsigned char val);
void UART_Init(int idx, int baud);
void UART_putch(unsigned char c);

#endif /*__UART_H*/