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
  // I) Core tick timer'ý çalýþtýrýr ve
  // II) Core tick timer kesmesini aktive eder
  SysTick_Config(SystemCoreClock / CLOCKS_PER_SEC);
}

void Sys_ClockTick(void)
{
  static int count;
  
  ++_TmTick;
  
}

clock_t clock(void)
{
  return _TmTick;
}









