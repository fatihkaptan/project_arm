#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "system.h"
#include "io.h"
#include "UART.h"
#include "stm32f4xx_usart.h"


struct UART_CFG{
  int ioRx;
  int ioTx;
  uint32_t ckUART;
  USART_TypeDef *pUSART;
};

static struct UART_CFG uCfg[]={
  {IOP_U1RX,IOP_U1TX,RCC_APB2Periph_USART1,USART1},
  {IOP_U2RX,IOP_U2TX,RCC_APB1Periph_USART2,USART2},
  {IOP_U6RX,IOP_U6TX,RCC_APB2Periph_USART6,USART6},
};


void UART_Init(int idx, int baud){
  USART_InitTypeDef uInit;
  
  // UART kurarken;
  // 1. IO uclari yapilandirilir. 
  IO_Init(uCfg[idx].ioTx , IO_MODE_ALTERNATE); //tx ucu cfg- alternate mod olmali
  IO_Init(uCfg[idx].ioRx , IO_MODE_INPUT);//rx ucu input olmali. 
  
  // 2. UART cevresel için clock sagliyoruz. 
  if(idx==UART_1 || idx == UART_6)
    RCC_APB2PeriphClockCmd(uCfg[idx].ckUART, ENABLE);
  else
    RCC_APB1PeriphClockCmd(uCfg[idx].ckUART, ENABLE);
  
  // 3.  Init yapisi baslatilir. 
  uInit.USART_BaudRate = baud;
  uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  uInit.USART_Parity = USART_Parity_No;
  uInit.USART_StopBits = USART_StopBits_1;
  uInit.USART_WordLength = USART_WordLength_8b;
  USART_Init(uCfg[idx].pUSART  , &uInit); //yapiyi BSP'ye gonderme
  
  //4. Cevresel aktif edilir.
  USART_Cmd(uCfg[idx].pUSART , ENABLE);
}
  
void UART_Send(int idx, unsigned char val){
  //TSR(Transmit Shift Register) yukleme icin uygun mu?
  //USART_FLAG_TXE:  Transmit data register empty flag
  while((!USART_GetFlagStatus(uCfg[idx].pUSART , USART_FLAG_TXE)) | 1){
    
    //datayi yukle
    USART_SendData(uCfg[idx].pUSART ,val);
  }  
}

void UART_putch(unsigned char c){
  if(c=='\n')
    UART_Send(0, '\r');
  
  UART_Send(0,c);
}
  
  
  
  
  
  
  