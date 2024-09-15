#ifndef __IO_H
#define __IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"  
  
  
// I/O MODLARI
typedef enum {  
  IO_MODE_INPUT,
  IO_MODE_OUTPUT,
  IO_MODE_ALTERNATE,
  IO_MODE_ANALOG,
  
  IO_MODE_INPUT_PD,
  IO_MODE_INPUT_PU,
  IO_MODE_OUTPUT_OD,
  IO_MODE_ALTERNATE_OD,
} IO_MODE;

typedef enum {
  IO_PORT_A,
  IO_PORT_B,
  IO_PORT_C,
  IO_PORT_D,
  IO_PORT_E,
  IO_PORT_F,
  IO_PORT_G,
} IO_PORTS;

typedef struct {
  int port;
  int pin;
} IO_PIN;


typedef enum {
  //LED
  IOP_LED,
  //Alfanümerik LCD modül
  IOP_LCD_RS,
  IOP_LCD_E,
  IOP_LCD_DB4,
  IOP_LCD_DB5,
  IOP_LCD_DB6,
  IOP_LCD_DB7,
} IO_IDX;

// UYGULAMA I/O PIN LÝSTESÝ
#ifdef _IOS_
IO_PIN _ios[] = {
  // LED
  { IO_PORT_C, 13 },    /*LED*/
  { IO_PORT_A,  3 },    /*LCD_RS*/ 
  { IO_PORT_A,  5 },    /*LCD_E*/
  { IO_PORT_A,  7 },    /*LCD_DB4*/
  { IO_PORT_B,  0 },    /*LCD_DB5*/
  { IO_PORT_B,  1 },    /*LCD_DB6*/
  { IO_PORT_B,  2 },    /*LCD_DB7*/
  
};


GPIO_TypeDef  *GPIO_Ports[] = {
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  GPIOE,
  GPIOF,
  GPIOG,
};
#else
extern IO_PIN   _ios[];
extern GPIO_TypeDef *GPIO_Ports[];
#endif

void IO_Init(IO_IDX idx, IO_MODE mode);
void IO_Write(IO_IDX idx, int val);
int IO_Read(IO_IDX idx);

#ifdef __cplusplus
}
#endif


#endif
