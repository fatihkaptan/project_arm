#ifndef __UART_H
#define __UART_H
#include "stm32f4xx.h"  

typedef enum {
  UART_1,
  UART_2,
  UART_3,
  UART_4,
  UART_5,
  UART_6,
} UART_PERIPH;

enum {
  UART_ERR_NOISE = -1,
  UART_ERR_OVERRUN = -2,
  UART_ERR_FRAMING = -3,
  UART_ERR_PARITY = -4,
};

void UART_Send(UART_PERIPH idx, unsigned char val);
void UART_Send2(UART_PERIPH idx, unsigned char val);
void UART_Init(int idx, int baud);
void UART_putch(UART_PERIPH idx, unsigned char c);

int UART_puts(UART_PERIPH idx, const char *str);
int UART_printf(UART_PERIPH idx, const char *fmt, ...);

int UART_DataReady(UART_PERIPH idx);
int UART_Recv(UART_PERIPH idx);

#endif /*__UART_H*/