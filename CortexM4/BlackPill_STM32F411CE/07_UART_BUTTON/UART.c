#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include "system.h"
#include "io.h"
#include "UART.h"
#include "stm32f4xx_usart.h"

#define SZ_PRNBUF       256

static USART_TypeDef *_tUART[] = {
  USART1,
  USART2,
  USART3,
  UART4,
  UART5,
  USART6
};
#define N_UARTS         (sizeof(_tUART) / sizeof(USART_TypeDef *))
struct UART_CFG {
  int           ioTx;
  int           ioRx;
  uint8_t       afUART;
  uint32_t      ckUART;
};

static struct UART_CFG _uCfg[] = {
  IOP_U1TX, IOP_U1RX, GPIO_AF_USART1, RCC_APB2Periph_USART1,
  IOP_U2TX, IOP_U2RX, GPIO_AF_USART2, RCC_APB1Periph_USART2,
  IOP_U3TX, IOP_U3RX, GPIO_AF_USART3, RCC_APB1Periph_USART3,
  IOP_U4TX, IOP_U4RX, GPIO_AF_UART4, RCC_APB1Periph_UART4,
  IOP_U5TX, IOP_U5RX, GPIO_AF_UART5, RCC_APB1Periph_UART5,
  IOP_U6TX, IOP_U6RX, GPIO_AF_USART6, RCC_APB2Periph_USART6,  
};


void UART_Init(int idx, int baud)
{
  USART_InitTypeDef uInit;
  int i, port, pin;
  
  if (idx >= N_UARTS)
    return;
  
  i = _uCfg[idx].ioTx;
  port = _ios[i].port;
  pin = _ios[i].pin;
  
  // 1) ilgili pin Alternate mode'a geçirilir
  IO_Init(i, IO_MODE_ALTERNATE);
  // 2) ilgili pin için alternate function seçilir
  GPIO_PinAFConfig(GPIO_Ports[port], pin, _uCfg[idx].afUART);

  i = _uCfg[idx].ioRx;
  port = _ios[i].port;
  pin = _ios[i].pin;
  
  // 1) ilgili pin Alteranate mode'a geçirilir
  IO_Init(i, IO_MODE_ALTERNATE);
  // 2) ilgili pin için alternate function seçilir
  GPIO_PinAFConfig(GPIO_Ports[port], pin, _uCfg[idx].afUART);
  
  // 3) UART çevresel birim için clock saðla
  if (idx == UART_1 || idx == UART_6)
    RCC_APB2PeriphClockCmd(_uCfg[idx].ckUART, ENABLE);
  else
    RCC_APB1PeriphClockCmd(_uCfg[idx].ckUART, ENABLE);
  
  // 4) Seri haberleþme parametrelerini belirle
  uInit.USART_BaudRate = baud;
  uInit.USART_WordLength = USART_WordLength_8b;
  uInit.USART_StopBits = USART_StopBits_1;
  uInit.USART_Parity = USART_Parity_No;
  uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  
  USART_Init(_tUART[idx], &uInit);
  
  // 5) UART çevreselini aktive et
  USART_Cmd(_tUART[idx], ENABLE);
}
  
void UART_Send(UART_PERIPH idx, unsigned char val){
  //TSR(Transmit Shift Register) yukleme icin uygun mu?
  //USART_FLAG_TXE:  Transmit data register empty flag
  while((!USART_GetFlagStatus(_tUART[idx], USART_FLAG_TXE))){
    
    //datayi yukle
    USART_SendData(_tUART[idx] ,val);
  }  
}

//alternatif fonksiyon
void UART_Send2(UART_PERIPH idx, unsigned char val)
{
  // Not: Verinin gitmesini beklemiyoruz, sadece yükleme yapýp çýkýyoruz
  USART_SendData(_tUART[idx], val);

  // 1) Veri gidene kadar bekle
  while (!USART_GetFlagStatus(_tUART[idx], USART_FLAG_TC)) ;  
}

void UART_putch(UART_PERIPH idx, unsigned char c)
{
  if (c == '\n')
    UART_Send2(idx, '\r');
  
  UART_Send2(idx, c);
}
  
int UART_puts(UART_PERIPH idx, const char *str)
{
  int i = 0;
  
  while (str[i])
    UART_putch(idx, str[i++]);
  
  return i;
} 

int UART_printf(UART_PERIPH idx, const char *fmt, ...)
{
  va_list args;
  char str[SZ_PRNBUF];
  
  va_start(args, fmt);
  vsnprintf(str, SZ_PRNBUF, fmt, args);
  
  return UART_puts(idx, str);
}

// Belirtilen UART biriminin RDR'sinde veri var mý?
int UART_DataReady(UART_PERIPH idx)
{
    return USART_GetFlagStatus(_tUART[idx], USART_FLAG_RXNE);
}

int UART_Recv(UART_PERIPH idx)
{
  int ret;
  USART_TypeDef *pUART = _tUART[idx];
  
  while (!UART_DataReady(idx)) ;
  
  if (USART_GetFlagStatus(pUART, USART_FLAG_ORE | USART_FLAG_NE
                          | USART_FLAG_FE | USART_FLAG_PE))
  {
    if (USART_GetFlagStatus(pUART, USART_FLAG_NE))
      ret = UART_ERR_NOISE;
    else if (USART_GetFlagStatus(pUART, USART_FLAG_ORE))
      ret = UART_ERR_OVERRUN;
    if (USART_GetFlagStatus(pUART, USART_FLAG_FE))
      ret = UART_ERR_FRAMING;
    if (USART_GetFlagStatus(pUART, USART_FLAG_PE))
      ret = UART_ERR_PARITY;
    
    // Statü register'ýnda hata bitini sýfýrlamak amacýyla
    // boþ okuma yapýyoruz
    USART_ReceiveData(pUART);
  }
  else    
    ret = USART_ReceiveData(pUART);
  
  return ret;
}
  
  
  
  
  