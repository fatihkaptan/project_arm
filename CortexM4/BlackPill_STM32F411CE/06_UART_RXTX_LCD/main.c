#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "system.h"
#include "io.h"
#include "UART.h"

UART_PERIPH curr_UART = UART_1;
void init(void)
{
    Sys_IoInit();
    Sys_TickInit();
    Sys_ConsoleInit();
    
    UART_Init(curr_UART, 115200);
    
    IO_Write(IOP_LED, 1);
    IO_Init(IOP_LED, IO_MODE_OUTPUT);
    //LCD_Clear();DelayMs(4);
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

      t0 = t1;     // Son ON olma baþlangýç zamaný
      state = S_LED_ON;
      //break;
    
  case S_LED_ON:
    if (t1 - t0 >= CLOCKS_PER_SEC / 10) /*100ms ON*/
      state = I_LED_OFF;
    break;
    
  case I_LED_OFF:
      IO_Write(IOP_LED, 1);     // LED off

      t0 = t1;     // Son OFF olma baþlangýç zamaný
      state = S_LED_OFF;
      //break;

  case S_LED_OFF:
    if (t1 - t0 >= 9 * CLOCKS_PER_SEC / 10) /*900ms OFF*/
      state = I_LED_ON;
    break;
  }
}
extern clock_t _TmTick;
static unsigned long sys_sec =0;

void Task_Print(void)
{
  static unsigned long count;
  sys_sec = _TmTick/1000;
  if(sys_sec==1)
    LCD_Clear();
  if(sys_sec>1)
    //printf("Saniye: %d\r", sys_sec);
    printf("Tick: %10lu\r", _TmTick);

UART_printf(curr_UART, "_TmTick: %10lu\r", _TmTick);
}  

int main()
{
  int c;
  // Çalýþma zamaný yapýlandýrmalarý
  init();
  printf("Hello, world!");
  
  UART_puts(curr_UART, "\n\nMerhaba dunya!\n");
  
  printf("\fsayi=%d, ch=%c", 159, curr_UART);
  UART_printf(curr_UART, "Hello, val=%d\n", 2983);
  
  while (1) {
        Task_LED(); 
        Task_Print();
        //blokeli bir TX ornegi
        if (UART_DataReady(curr_UART)) {
          c = UART_Recv(curr_UART);
          if (c < 0)
            UART_printf(curr_UART,"\rHATA: %d\n", c);//printf("\rHATA: %d\n", c);
          else
            UART_printf(curr_UART,"\r%c\n", c);//printf("\r%c\n", c);
        }
      }
}

  
  
  
  