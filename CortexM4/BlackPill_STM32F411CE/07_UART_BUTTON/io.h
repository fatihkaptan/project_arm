#ifndef __IO_H
#define __IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"  
  
  
// I/O MODS
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
  //Alfanumeric LCD module
  IOP_LCD_RS,
  IOP_LCD_E,
  IOP_LCD_DB4,
  IOP_LCD_DB5,
  IOP_LCD_DB6,
  IOP_LCD_DB7,
  //UART1-6 TX RX
  IOP_U1TX,
  IOP_U1RX,
  IOP_U2TX,
  IOP_U2RX,
  IOP_U3TX,
  IOP_U3RX,
  IOP_U4TX,
  IOP_U4RX,
  IOP_U5TX,
  IOP_U5RX,
  IOP_U6TX,
  IOP_U6RX,
  
  //Buttons;
  IOP_BTN_ONBOARD,
  IOP_BTN_SET,
  IOP_BTN_DOWN,
  IOP_BTN_UP,
  
} IO_IDX;

// UYGULAMA I/O PIN LIST
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
  // UART 1-6 TX/RX port definitons
  { IO_PORT_A,  9 },
  { IO_PORT_A, 10 },
  { IO_PORT_A,  2 },
  { IO_PORT_A,  3 },
  { IO_PORT_B, 10 },
  { IO_PORT_B, 11 },
  { IO_PORT_A,  0 },
  { IO_PORT_A,  1 },
  { IO_PORT_C, 12 },
  { IO_PORT_D,  2 },
  { IO_PORT_C,  6 },
  { IO_PORT_C,  7 },
  
  //Buttons;
  { IO_PORT_A,  0 },    //IOP_BTN_ONBOARD-> connected internal PU [SW --=----GND]
  { IO_PORT_C,  14 },   //IOP_BTN_SET,C14
  { IO_PORT_C,  15 },   //IOP_BTN_DOWN,C15
  { IO_PORT_A,  1 },    //IOP_BTN_UP,A1
  
  
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



#endif
