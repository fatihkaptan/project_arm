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

int PWM_Init(uint32_t period, uint32_t duty)
{
  // 1) Çýkýþ kanalýnýn I/O ayarlarý
  IO_Init(IOP_PWM, IO_MODE_ALTERNATE);
  GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_PWM].port], _ios[IOP_PWM].pin, GPIO_AF_TIM2);

  // 2) Timer ayarlarý (PWM frekansýný belirler)
  Timer_Init(TIMER_2, SystemCoreClock/10000 /*10kHZ->10KHz her 1 period 100us*/, period, 1);
  // 3) PWM ayarlarý (OC ayarlarý)
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
  
  // 4) Timer'ý çalýþtýrýyoruz (PWM çalýþmaya baþlýyor)
  Timer_Start(TIMER_2, 1);
  return period;
}


void Capture_Init(void)
{
    TIM_ICInitTypeDef icInit;
    
    //1) I/O ayari
//    IO_Init(IOP_CAPTURE1,IO_MODE_ALTERNATE_PU);
    IO_Init(IOP_CAPTURE1, IO_MODE_ALTERNATE_PU);/*TIM3_CH2 PB5 IOP_CapturePeriod*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
    IO_Init(IOP_CAPTURE2, IO_MODE_ALTERNATE_PU);/*TIM3_CH1 PA6 IOP_CaptureOntime*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
    //2) Timer baslangic
    Timer_Init(TIMER_3, 1000, 0,1);// 100mhz clock/1000-> 100khz hassasiyet -> 10us
    
    //3.1)Input Capture(period) structure init
    icInit.TIM_Channel = TIM_Channel_2;
    icInit.TIM_ICFilter=0;
    icInit.TIM_ICPolarity=TIM_ICPolarity_Falling; //her dusen kenarda olcum al.
    icInit.TIM_ICPrescaler=TIM_ICPSC_DIV1; 
    icInit.TIM_ICSelection=TIM_ICSelection_DirectTI;
    
    TIM_ICInit(TIM3,&icInit);
    
    //3.2)Input Capture(ontime) structure init
    icInit.TIM_Channel = TIM_Channel_1;
    icInit.TIM_ICFilter=0;
    icInit.TIM_ICPolarity=TIM_ICPolarity_BothEdge; //both edge on time icin
    icInit.TIM_ICPrescaler=TIM_ICPSC_DIV1;
    icInit.TIM_ICSelection=TIM_ICSelection_DirectTI;
    
    TIM_ICInit(TIM3,&icInit);
    
    //4) Interrupt config 
    
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); 
    TIM_ITConfig(TIM3, TIM_IT_CC2 , ENABLE); 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); 
    TIM_ITConfig(TIM3, TIM_IT_CC1 , ENABLE);
    NVIC_SetPriority(TIM3_IRQn , 2);
    NVIC_EnableIRQ(TIM3_IRQn);
    
  //5)Timer Start
    Timer_Start(TIMER_3,ENABLE);
}

void PWM_Duty(uint32_t duty){
    TIM_SetCompare3(TIM2,duty);
}


//////////////TIM1 interrupt routine
volatile unsigned long g_T1Count = 0;
void TIM1_UP_TIM10_IRQHandler(void)
{
  //ortak bir irq handler oldugu icin handler ici kontrol ekliyoruz. 
    if(TIM_GetITStatus(TimerTable[TIMER_1],TIM_IT_Update) == SET){
        SEGGER_SYSVIEW_RecordEnterTimer(1);
        g_T1Count++;
        SEGGER_SYSVIEW_RecordExitTimer();
        TIM_ClearITPendingBit(TimerTable[TIMER_1],TIM_IT_Update);//update flag clear
    }
  
    
}

//////////////TIM2 interrupt routine
volatile unsigned long g_T2Count = 0;
void TIM2_IRQHandler(void)
{

    if(TIM_GetITStatus(TimerTable[TIMER_2],TIM_IT_Update) == SET){
        SEGGER_SYSVIEW_RecordEnterTimer(2);
        g_T2Count++;
        SEGGER_SYSVIEW_RecordExitTimer();
        TIM_ClearITPendingBit(TimerTable[TIMER_2],TIM_IT_Update);//update flag clear
    }

    
}

//////////////TIM3 interrupt routine
volatile unsigned long g_T3Count = 0;
volatile uint16_t g_T3CaptureCount= 0;
volatile uint16_t g_T3CaptureCountOntime= 0;
void TIM3_IRQHandler(void)
{
    static uint16_t c0, c1, c2, c3;
    static uint8_t edge_flag = 0; // 0 = Yükselen, 1 = Düsen
    // Overflow Interrupt (Timer tasmasi)
    if (TIM_GetITStatus(TimerTable[TIMER_3], TIM_IT_Update) == SET){
        SEGGER_SYSVIEW_RecordEnterTimer(3);
        g_T3Count++;
        SEGGER_SYSVIEW_RecordExitTimer();
        TIM_ClearITPendingBit(TimerTable[TIMER_3], TIM_IT_Update);
    }
    // Kanal 2 - Periyot Ölçümü (Düsen Kenar)
    else if (TIM_GetITStatus(TimerTable[TIMER_3], TIM_IT_CC2) == SET){
        c1 = TIM_GetCapture2(TIM3);
        // Overflow durumunda düzeltme yap
        if (c1 >= c0)
            g_T3CaptureCount = c1 - c0;
        else
            g_T3CaptureCount = (0xFFFF - c0) + c1;

        c0 = c1;  // Son degeri güncelle
        TIM_ClearITPendingBit(TimerTable[TIMER_3], TIM_IT_CC2);
    }
    // Kanal 1 - Ontime Ölçümü (Both Edge)
    else if (TIM_GetITStatus(TimerTable[TIMER_3], TIM_IT_CC1) == SET){
        c3 = TIM_GetCapture1(TIM3);
        if (edge_flag == 1)  // Eger gelen kenar dusen ise
        {
            c2 = c3;  // Baslangiç zamanini kaydet
            edge_flag = 0;  // Siradaki kenar yukselen olacak
        }
        else  // Gelen kenar düsen ise
        {
            // Overflow durumunda düzeltme yap
            if (c3 >= c2)
                g_T3CaptureCountOntime = c3 - c2;
            else
                g_T3CaptureCountOntime = (0xFFFF - c2) + c3;

            edge_flag = 1;  // Sonraki kenar tekrar dusen olacak
        }
        TIM_ClearITPendingBit(TimerTable[TIMER_3], TIM_IT_CC1);
    }
}

//////////////TIM4 interrupt routine
volatile unsigned long g_T4Count = 0;
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TimerTable[TIMER_4],TIM_IT_Update) == SET){
        SEGGER_SYSVIEW_RecordEnterTimer(4);
        g_T4Count++;
        SEGGER_SYSVIEW_RecordExitTimer();
        TIM_ClearITPendingBit(TimerTable[TIMER_4],TIM_IT_Update);//update flag clear
    }
}

//////////////TIM5 interrupt routine
volatile unsigned long g_T5Count = 0;
unsigned long debug_int=0;
void TIM5_IRQHandler(void)
{
    if(TIM_GetITStatus(TimerTable[TIMER_5],TIM_IT_Update) == SET){
        SEGGER_SYSVIEW_RecordEnterTimer(5);
        g_T5Count++;
        SEGGER_SYSVIEW_Print("1s tick");
        SEGGER_SYSVIEW_RecordExitTimer();
    }
    TIM_ClearITPendingBit(TimerTable[TIMER_5],TIM_IT_Update);//update flag clear
    
#if TIMER_DEBUG
    if((g_T5Count%10)==0)
    {        
        debug_int++;
    }    
#endif
}


