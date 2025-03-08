#include "io.h"
#include "system.h"
#define _STDIN  0
#define _STDOUT 1
#define _STDERR 2

static const int GPIO_Clocks[] = {
  RCC_AHB1Periph_GPIOA,
  RCC_AHB1Periph_GPIOB,
  RCC_AHB1Periph_GPIOC,
  RCC_AHB1Periph_GPIOD,
  RCC_AHB1Periph_GPIOE,
  RCC_AHB1Periph_GPIOF,
  RCC_AHB1Periph_GPIOG,
};

#define N_PORTS (sizeof(GPIO_Clocks) / sizeof(int))


volatile clock_t _TmTick = 0;

void Sys_IoInit(void)
{
  int i;
  
  for (i = 0; i < N_PORTS; ++i)
    RCC_AHB1PeriphClockCmd(GPIO_Clocks[i], ENABLE);
}

void Sys_TickInit(void)
{
  // I) Core tick timer'� �al��t�r�r ve
  // II) Core tick timer kesmesini aktive eder
  SysTick_Config(SystemCoreClock / CLOCKS_PER_SEC);
}

void Sys_ClockTick(void)
{
    SEGGER_SYSVIEW_RecordEnterISR();
    static int count;
    ++_TmTick;
    SEGGER_SYSVIEW_RecordExitISR();
}

clock_t clock(void)
{
  return _TmTick;
}

void Sys_ConsoleInit(void)
{
  OLED_Start(1);
  
#ifndef __IAR_SYSTEMS_ICC__
  setvbuf(stdout, NULL, _IONBF, 0);
#endif  
}

void _putch(unsigned char c)
{
  OLED_putch(c);
}


#ifdef __IAR_SYSTEMS_ICC__
size_t __write(int handle, unsigned char *buffer, size_t size)
#else
size_t _write(int handle, unsigned char *buffer, size_t size)
#endif
{
  size_t nChars = 0;
  
  if (buffer == NULL)
    return 0;
  
  if (handle != _STDOUT && handle != _STDERR) 
    return 0;
  
  while (size--) {
    _putch(*buffer++);
    ++nChars;
  }
  
  return nChars;
}








