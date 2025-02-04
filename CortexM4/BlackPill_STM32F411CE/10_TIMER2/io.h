#ifndef __IO_H
#define __IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"  

//SPI pin definitions
//#define IO_OLED_VDD  
//#define IO_OLED_GND
#define IO_OLED_RES
#define IO_OLED_CS

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
  //PWM OUT
  IOP_PWM, /*TIM2_CH3*/
  
} IO_IDX;

// UYGULAMA I/O PIN LIST
#ifdef _IOS_
IO_PIN _ios[] = {
  // LED
  { IO_PORT_C, 13 },    /*LED*/
  //PWM OUT
  { IO_PORT_A, 2 },     /*TIM2_CH3 IOP_PWM*/
  
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
