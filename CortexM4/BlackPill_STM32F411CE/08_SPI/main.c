//******************
// Project: 08_SPI
//
// DESCRIPTION:
//  SPI Comm. with OLED example
//
// CREATED: 01.02.2025, by Fatih Kaptan
//
// FILE: main.c
// EWDIR: C:\iar\ewarm-8.50.9
//
//******************


#include "system.h"
#include "io.h"
#include "oled.h"


static unsigned long sys_sec =0;


void init(void)
{
    Sys_IoInit();
    Sys_TickInit();
    Sys_ConsoleInit();
    IO_Write(IOP_LED, 1);
    IO_Init(IOP_LED, IO_MODE_OUTPUT);
}

void Task_LED(void)
{
  static enum {
    I_LED_ON,
    S_LED_ON,
    
    I_LED_OFF,
    S_LED_OFF
  } state = I_LED_ON;
  
  static clock_t t0, t1;
  
  t1 = clock();
  
  switch (state) {
  case I_LED_ON:
      IO_Write(IOP_LED, 0);     // LED on

      t0 = t1;     
      state = S_LED_ON;
      //break;
    
  case S_LED_ON:
    if (t1 - t0 >= CLOCKS_PER_SEC / 10) /*100ms ON*/
      state = I_LED_OFF;
    break;
    
  case I_LED_OFF:
      IO_Write(IOP_LED, 1);     // LED off

      t0 = t1;    
      state = S_LED_OFF;
      //break;

  case S_LED_OFF:
    if (t1 - t0 >= 9 * CLOCKS_PER_SEC / 10) /*900ms OFF*/
      state = I_LED_ON;
    break;
  }
}

void Task_Print(void)
{
  static unsigned long count;
  FNT_t font;
  int row, col;
  
  unsigned long ms = _TmTick; 
  unsigned long seconds = ms / 1000; 
  unsigned long minutes = seconds / 60; 
  unsigned long hours = minutes / 60; 
  seconds = seconds % 60; 
  minutes = minutes % 60; 
  unsigned long milliseconds = (ms %1000)/10; 
  OLED_GetCursor(&row, &col);
  font = OLED_GetFont();

  OLED_SetFont(FNT_BIG);
  OLED_SetCursor(0, 0);
  printf("Time:");
  
  OLED_SetCursor(1, 0);
  if(hours==0)
    printf("%02lu:%02lu:%02lu", minutes, seconds, milliseconds); 
  else
    printf("%02lu:%02lu:%02lu", hours, minutes, seconds); 
  OLED_SetFont(font);
  OLED_SetCursor(row, col);  
}

int main()
{
  int c;
// Working time configurations
  init();
  init_OLED();
  while (1) {
        Task_LED();   
        Task_Print();
      }
} 

void init_OLED(void){
  OLED_Rotate(0);
  printf("ABCÇDEFGÐHIÝJKLMNOÖPRSÞTUÜVYZ");
  DelayMs(2500);
  OLED_ClearDisplay();
    
  OLED_SetFont(FNT_LARGE);
  OLED_SetCursor(0, 0);
  printf("CIGERIMSIN");
  DelayMs(2500);
  OLED_ClearDisplay();  
  
  OLED_Line(0, 0, 127, 63, SET_PIXEL);DelayMs(500);
  OLED_Line(0, 63, 127, 0, SET_PIXEL);DelayMs(500);
  OLED_Line(0, 23, 127, 23, SET_PIXEL);DelayMs(500);
  OLED_Line(57, 0, 57, 63, SET_PIXEL);DelayMs(500);
  OLED_Line(9, 11, 103, 47, SET_PIXEL);DelayMs(500);
  OLED_Circle(60, 25, 19, SET_PIXEL);DelayMs(1000);
  OLED_Circle(60, 55, 12, SET_PIXEL);DelayMs(1000);
  OLED_Circle(30, 25, 19, SET_PIXEL);DelayMs(1000);
  OLED_ClearDisplay();  
}


  
  
  
  