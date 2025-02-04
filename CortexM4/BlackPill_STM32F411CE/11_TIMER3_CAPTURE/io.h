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
  IO_MODE_ALTERNATE_PU
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
  //Capture Input
  IOP_CAPTURE1,
  IOP_CAPTURE2,
  // SPI
  IOP_SPI1_SCK,
  IOP_SPI1_MISO,
  IOP_SPI1_MOSI,
  
  IOP_SPI2_SCK,
  IOP_SPI2_MISO,
  IOP_SPI2_MOSI,
  
  IOP_SPI_SCK,
  IOP_SPI_MISO,
  IOP_SPI_MOSI,
  //OLED
#ifdef IO_OLED_VDD
  IOP_OLED_VDD,
#endif
#ifdef IO_OLED_GND
  IOP_OLED_GND,
#endif
#ifdef IO_OLED_RES
  IOP_OLED_RES,
#endif
  IOP_OLED_DC, //hepsinde var
#ifdef IO_OLED_CS
  IOP_OLED_CS,
#endif
  
} IO_IDX;

// UYGULAMA I/O PIN LIST
#ifdef _IOS_
IO_PIN _ios[] = {
  // LED
  { IO_PORT_C, 13 },    /*LED*/
  //PWM OUT
  { IO_PORT_A, 2 },     /*TIM2_CH3 IOP_PWM*/
  //Input Capture
  { IO_PORT_B, 5 },     /*TIM3_CH2 PB5 IOP_CapturePeriod*/
  { IO_PORT_A, 6 },     /*TIM3_CH1 PA6 IOP_CaptureOntime*/

  //SPI
  { IO_PORT_A, 5 },    /*SCK*/
  { IO_PORT_A, 6 },    /*MISO oledde kullanilmiyo*/
  { IO_PORT_A, 7 },    /*MOSI*/
  
  { IO_PORT_B, 13 },
  { IO_PORT_B, 14 },
  { IO_PORT_B, 15 },
  
  { IO_PORT_B, 13 },
  { IO_PORT_B, 14 },
  { IO_PORT_B, 15 },
  //OLED
#ifdef IO_OLED_VDD
#endif
#ifdef IO_OLED_GND
#endif
#ifdef IO_OLED_RES
  { IO_PORT_B, 0 },    /*RES*/
#endif
  { IO_PORT_B, 1 },    /*DC*/
#ifdef IO_OLED_CS
  { IO_PORT_A, 4 },    /*CS*/
#endif
  
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
