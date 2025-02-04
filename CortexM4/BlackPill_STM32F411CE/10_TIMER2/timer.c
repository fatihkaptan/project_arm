#include "io.h"
#include "system.h"
#include "timer.h"

TIM_TypeDef *TimerTable[] = {
  TIM1,TIM2,TIM3,TIM4,TIM5
};


uint32_t TimRccTab[] = {
  RCC_APB2Periph_TIM1,
  RCC_APB1Periph_TIM2,
  RCC_APB1Periph_TIM3,
  RCC_APB1Periph_TIM4,
  RCC_APB1Periph_TIM5,
  };

IRQn_Type TimIrqTab[] = {
  TIM1_UP_TIM10_IRQn,
  TIM2_IRQn,
  TIM3_IRQn,
  TIM4_IRQn,
  TIM5_IRQn,
};

void Timer_Init(int tmNo, unsigned prescale, unsigned period, unsigned repeat)
{
  TIM_TimeBaseInitTypeDef tmInit;
  //1) cevresele base clock(CNT) tanimlanir. 
  if(tmNo ==TIMER_1)
    RCC_APB2PeriphClockCmd(TimRccTab[tmNo],ENABLE);
  else
    RCC_APB1PeriphClockCmd(TimRccTab[tmNo],ENABLE);
  
  //2) timer parametreleri ayarlanir. 
  tmInit.TIM_ClockDivision = TIM_CKD_DIV1;
  tmInit.TIM_CounterMode = TIM_CounterMode_Up;
  tmInit.TIM_Period = period - 1;
  if(period==1)
      tmInit.TIM_Period = 1;
  tmInit.TIM_Prescaler = prescale - 1; 
  tmInit.TIM_RepetitionCounter =repeat-1 ;
  
  //3)ilgili timer modudlu icin ayarlar yuklenir. 
  TIM_TimeBaseInit(TimerTable[tmNo], &tmInit);
  Timer_Reset(tmNo);
}

void Timer_Start(int tmNo, int bStart)
{
  TIM_Cmd(TimerTable[tmNo], bStart? ENABLE : DISABLE);
}

void Timer_Reset(int tmNo)
{
  TIM_SetCounter(TimerTable[tmNo] , 0);
  
}

void TimerIntConfig(int tmNo, int priority)//timer kesme konfigurasyon yonetimi
{
  //1) Cevresel birim ayarlari
    //1.a) False interrupt onlemi alinir.(cevresel kesmelerinde int kesilir.) 
  TIM_ClearITPendingBit(TimerTable[tmNo], TIM_IT_Update); //tasma event flag'i temizlenir. 
    //1.b) Cevreselin kesme kaynagi aktif edilir. 
  TIM_ITConfig(TimerTable[tmNo], TIM_IT_Update , ENABLE); 
  
  //2) NVIC (core ayarlari)
    //2.a) Oncelik ayari,
  NVIC_SetPriority(TimIrqTab[tmNo] , priority);
    //2.b)nvic interrupt enable
  NVIC_EnableIRQ(TimIrqTab[tmNo]);    
}

void PWM_Init(uint32_t period, uint32_t duty)
{
  // 1) ��k�� kanal�n�n I/O ayarlar�
  IO_Init(IOP_PWM, IO_MODE_ALTERNATE);
  GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_PWM].port], _ios[IOP_PWM].pin, GPIO_AF_TIM2);

  // 2) Timer ayarlar� (PWM frekans�n� belirler)
  Timer_Init(TIMER_2, SystemCoreClock/10000 /*10kHZ->10KHz her 1 period 100us*/, period, 1);
  // 3) PWM ayarlar� (OC ayarlar�)
  TIM_OCInitTypeDef ocInit;
  
  ocInit.TIM_OCIdleState = TIM_OCIdleState_Reset;
  ocInit.TIM_OCMode = TIM_OCMode_PWM1;
  ocInit.TIM_OCPolarity = TIM_OCPolarity_High;
  ocInit.TIM_OutputState = TIM_OutputState_Enable;
  ocInit.TIM_Pulse = duty;
  
  TIM_OC3Init(TIM2, &ocInit);
  
  // Compare Reg double buf.
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
  // 4) Timer'� �al��t�r�yoruz (PWM �al��maya ba�l�yor)
  Timer_Start(TIMER_2, 1);
}


//////////////TIM1 interrupt routine
volatile unsigned long g_T1Count = 0;
void TIM1_UP_TIM10_IRQHandler(void)
{
  //ortak bir irq handler oldugu icin handler ici kontrol ekliyoruz. 
  if(TIM_GetITStatus(TimerTable[TIMER_1],TIM_IT_Update) == SET)
     g_T1Count++;
  
  TIM_ClearITPendingBit(TimerTable[TIMER_1],TIM_IT_Update);//update flag clear
    
}

//////////////TIM2 interrupt routine
volatile unsigned long g_T2Count = 0;
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TimerTable[TIMER_2],TIM_IT_Update) == SET)
        g_T2Count++;
    
    TIM_ClearITPendingBit(TimerTable[TIMER_2],TIM_IT_Update);//update flag clear
}

//////////////TIM3 interrupt routine
volatile unsigned long g_T3Count = 0;
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TimerTable[TIMER_3],TIM_IT_Update) == SET)
        g_T3Count++;
    
    TIM_ClearITPendingBit(TimerTable[TIMER_3],TIM_IT_Update);//update flag clear
}

//////////////TIM4 interrupt routine
volatile unsigned long g_T4Count = 0;
void TIM4_IRQHandler(void)
{
        if(TIM_GetITStatus(TimerTable[TIMER_4],TIM_IT_Update) == SET)
        g_T4Count++;
    
    TIM_ClearITPendingBit(TimerTable[TIMER_4],TIM_IT_Update);//update flag clear
}

//////////////TIM5 interrupt routine
volatile unsigned long g_T5Count = 0;
unsigned long debug_int=0;
void TIM5_IRQHandler(void)
{
        if(TIM_GetITStatus(TimerTable[TIMER_5],TIM_IT_Update) == SET)
        g_T5Count++;
    
    TIM_ClearITPendingBit(TimerTable[TIMER_5],TIM_IT_Update);//update flag clear
    
#if TIMER_DEBUG
    if((g_T5Count%10)==0)
    {        
        debug_int++;
    }    
#endif
}


