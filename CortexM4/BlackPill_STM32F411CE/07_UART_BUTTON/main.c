//******************
// Project: 07_UART_BUTTON
//
// DESCRIPTION:
//  Simple button exercise with counting semaphore /additionaly edge control
//
// CREATED: 23.09.2024, by Fatih Kaptan
//
// FILE: main.c
// EWDIR: C:\iar\ewarm-9.60.2
//******************

#include "system.h"
#include "io.h"
#include "UART.h"
#include "button.h"

UART_PERIPH curr_UART = UART_1;
static unsigned long sys_sec =0;


void init(void)
{
    Sys_IoInit();
    Sys_TickInit();
    Sys_ConsoleInit();
    
    UART_Init(curr_UART, 115200);
    
    IO_Write(IOP_LED, 1);
    IO_Init(IOP_LED, IO_MODE_OUTPUT);
    BTN_InitButtons();
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



void Task_Print(void)
{
  static unsigned long count;
  sys_sec = _TmTick/1000;
  if(sys_sec==1)
    LCD_Clear();
  if(sys_sec>1)
    //printf("Saniye: %d\r", sys_sec);
    printf("Tick: %10lu\r", _TmTick);

//UART_printf(curr_UART, "_TmTick: %10lu\r", (unsigned long)_TmTick);
}  


void Task_Button()
{
  static int count = 0;
  int i;
  
  /*
  BTN_ONBOARD,
  BTN_SET,
  BTN_DOWN,
  BTN_UP,
  */
  
#ifdef BTN_LONG_PRESS
  // Long press handling 
  for (i = 0; i < N_BUTTONS; i++) {
    if (g_ButtonsL[i]) { // Long press semaphore check
      switch (i) {
      case BTN_SET:
        UART_printf(curr_UART, "\n*BTN_SET_LONG cnt* = %d\n", ++count);
        break;
        // other Long press buttons can be added 
      default:
        break;
      }
      g_ButtonsL[i] = 0;  // release long press semaphore
    }
  }
#endif
  
  // Short press handling 
  for (i = 0; i < N_BUTTONS; i++) {
    if (g_Buttons[i] > 0) { // short press sempahore check
        switch (i) {
        case BTN_ONBOARD:
          UART_printf(curr_UART, "\n*BTN_ONBOARD cnt* = %d\n", ++count);
          break;
        case BTN_SET:
          UART_printf(curr_UART, "\n*BTN_SET cnt* = %d\n", ++count);
          break;
        case BTN_DOWN:
          UART_printf(curr_UART, "\n*BTN_DOWN cnt* = %d\n", ++count);
          break;
        case BTN_UP:
          UART_printf(curr_UART, "\n*BTN_UP cnt* = %d\n", ++count);
          break;
        default:
          break;
        }
        --g_Buttons[i]; // short press semaphore release
    }
  }
}






int main()
{
  int c;
  // Çalýþma zamaný yapýlandýrmalarý
  init();
  printf("Hello, world!");
  
  UART_puts(curr_UART, "\n\nMerhaba dunya!\n");
  
  printf("\fsayi=%d, ch=%c", 159, UART_1);
  UART_printf(curr_UART, "Hello, val=%d\n", 2983);
  //Binary semaphore not succesfull for waitings, apply counting semaphore
  UART_puts(curr_UART, "\n\nWaiting..");
  //DelayMs(10000);
  UART_puts(curr_UART, "Finished.\n");
  
  while (1) {
        Task_LED(); 
        Task_Print();
        Task_Button();
        
      }
}

  
  
  
  