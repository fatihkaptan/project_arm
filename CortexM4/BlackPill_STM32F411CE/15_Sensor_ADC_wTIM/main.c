//******************
// Project: 15_Sensor_ADC_wTIM
//
// DESCRIPTION:
//  ADC Sampling Application - 4.  periodic adc sampling with PWM Edge & interrupts. without DMA
//
// CREATED: 17.03.2025, by Fatih Kaptan
//
// FILE: main.c
// EWDIR: C:\iar\ewarm-8.50.9
//
//******************

#include "main.h"



int main()
{       
    int Cnt=0;
    init();// Working time configurations
    while (1) {   
        Cnt = 1000;
        EXEC_TASK(Task_LED);//Task_LED();   
//        EXEC_TASK(Task_Print);//Task_Print();
        EXEC_TASK(Task_Sensor);
        while(--Cnt);  // Delay
    }
} 

void init(void)
{
    init_SeggerModules();
    Sys_IoInit();
    Sys_TickInit();    
    Sys_ConsoleInit();    
    init_Timers();
    //period_pwm = PWM_Init(100,50); //100*100us = 10ms period, 5ms OnTime capture denemek icin
    Capture_Init();
    init_OLED();   
    IO_Init(IOP_LED, IO_MODE_OUTPUT);
}

#define N_SAMPLES 25
int sensor_adc_mean;
int sensor_adc_mean_raw;
int sensor_adc; //measuremnt result raw
static unsigned long count_sample;
void Task_Sensor(void)
{
    static enum{
        S_INIT,
        S_WAIT,
        S_WORK
    }state = S_INIT;
    
    static int y0; //table array of y
    static int x,y;
    static int  ns;
    static long total=0;
    
    switch(state){
    case S_INIT:
        SEGGER_SYSVIEW_RecordVoid(60 + S_INIT);
        PWM_Init(20,5); //(period,ontime) as 100us/per -> 
        IADC_IoInit(IOP_AIN1);
        IADC_Init(1,DISABLE,DISABLE);// nConv=1, contMode=DIS, scanMode=DIS) 
        IADC_Channel(1,1);
        IADC_IntConfig();
        IADC_Start();
        OLED_SetFont(FNT_SMALL);
        state= S_WAIT;
        SEGGER_SYSVIEW_Print("Sensor read initialized with read every 100ms rising edge external trigger(T2_CC3)");
        SEGGER_SYSVIEW_RecordEndCall(60 + S_INIT);
        break;
        
    case S_WAIT:
        SEGGER_SYSVIEW_RecordVoid(60 + S_WAIT);
        if(g_bEOC)
            state =S_WORK;
        SEGGER_SYSVIEW_RecordEndCall(60 + S_WAIT);
        break;
        
    case S_WORK:
        SEGGER_SYSVIEW_RecordVoid(60 + S_WORK);
        sensor_adc = IADC_Result();
        //        count_sample++;
        
        
        total += sensor_adc;
        if(++ns>=N_SAMPLES){
            ns=0;
            y=total/N_SAMPLES/64;
            sensor_adc_mean_raw=total/N_SAMPLES;
            sensor_adc_mean=y;
            total=0;
            
            OLED_SetCursor(0, 0);
            printf("V_in: %.2fV\n", ((float)sensor_adc_mean_raw/4095.0)*3.3);
            
            if(x==0)
                OLED_ClearDisplay();  
            else
                OLED_Line(x-1 , 63-y0, x, 63-y, SET_PIXEL);
            
            if(++x == 128)
                x=0;
            
            y0 = y;
        }
        g_bEOC=0;
        state=S_WAIT;
        SEGGER_SYSVIEW_RecordEndCall(60 + S_WORK);
        break;
        
    }    
}


void init_SeggerModules(void)
{
    SEGGER_SYSVIEW_Conf();
    SYSVIEW_AddTask((void *)Task_LED, "Task_LED", 10);
//    SYSVIEW_AddTask((void *)Task_Print, "Task_Print", 10);
    SYSVIEW_AddTask((void *)Task_Sensor, "Task_Sensor", 10);
}


void init_Timers(void)
{
    //Timer_Init(tmNo,prescale,period,repeat) (100Mhz/2000 -> 50k, 2k period -> 100M tick-> 1sec, 1 no repet.)
    //dikkat 2^16 asmamali prescaler sonucu
    Timer_Init(TIMER_5, SYS_CLOCK_FREQ/2000, 2000, 1);//1s
    TimerIntConfig(TIMER_5, 3);
    Timer_Start(TIMER_5,1);
}


void Task_Print(void){
#ifndef OLD
    //OLED_SetFont(FNT_LARGE);
    OLED_SetCursor(0, 0);
    printf("sensor_adc:%4u\n", sensor_adc);
#else
    static unsigned long count;
    FNT_t font;
    int row, col;
    OLED_GetCursor(&row, &col);
    font = OLED_GetFont(); 
    OLED_SetFont(FNT_SMALL);
    OLED_SetCursor(0, 0);
    printf("Ontime: %.2f ms\n", g_T3CaptureCountOntime/100.0);
    OLED_SetCursor(1, 0);
    printf("Freq: %.2f Hz\n", 1/(g_T3CaptureCount/100000.0));
    OLED_SetCursor(2, 0);
    printf("Period: %.2f ms\n", g_T3CaptureCount/100.0);
    OLED_SetCursor(3, 0);
    printf("Duty: %%%.1f\n",((float)g_T3CaptureCountOntime / g_T3CaptureCount) * 100.0f);
    OLED_SetCursor(4, 0);
    printf("1s Count: %5u\n", g_T5Count%1000);
    OLED_SetCursor(5, 0);
    printf("sensor_adc: %5u\n", sensor_adc);
    OLED_SetCursor(6, 0);
    printf("counter_s: %5u\n", count_sample);
    OLED_SetFont(font);
    OLED_SetCursor(row, col);
#endif
}

void init_OLED(void){
    OLED_Rotate(0);
    printf("ABCÇDEFGÐHIÝJKLMNOÖPRSÞTUÜVYZ");
    SEGGER_SYSVIEW_Print("basladi");
    SEGGER_SYSVIEW_MarkStart(0x01);
    DelayMs(500);
    SEGGER_SYSVIEW_MarkStop(0x01);
    SEGGER_SYSVIEW_Print("bitti");
    OLED_ClearDisplay();
    
    OLED_SetFont(FNT_LARGE);
    OLED_SetCursor(0, 0);
    printf("CIGERIMSIN");
    DelayMs(500);
    OLED_ClearDisplay();  

    OLED_Line(0, 0, 127, 63, SET_PIXEL);DelayMs(250);
    OLED_Line(0, 63, 127, 0, SET_PIXEL);DelayMs(250);

    OLED_ClearDisplay();  
}

void Task_LED(void){
    static enum {
        I_LED_ON=0,
        S_LED_ON,        
        I_LED_OFF,
        S_LED_OFF
    } state = I_LED_ON;
    
    static clock_t t0, t1;
    
    t1 = clock();
    
    switch (state) {
    case I_LED_ON:
        SEGGER_SYSVIEW_RecordVoid(50 + I_LED_ON);
        SEGGER_SYSVIEW_MarkStart(0x02);
        IO_Write(IOP_LED, 0);     // LED on
        SEGGER_SYSVIEW_MarkStop(0x02);
        t0 = t1;     
        state = S_LED_ON;
        SEGGER_SYSVIEW_RecordEndCall(50 + I_LED_ON);  
    case S_LED_ON:
        SEGGER_SYSVIEW_RecordVoid(50 + S_LED_ON);
        if (t1 - t0 >= CLOCKS_PER_SEC / 10) /*100ms ON*/
            state = I_LED_OFF;
        SEGGER_SYSVIEW_RecordEndCall(50 + S_LED_ON);
        break;        
    case I_LED_OFF:
        SEGGER_SYSVIEW_RecordVoid(50 + I_LED_OFF);
        SEGGER_SYSVIEW_MarkStart(0x03);
        IO_Write(IOP_LED, 1);     // LED off
        SEGGER_SYSVIEW_MarkStop(0x03);
        t0 = t1;    
        state = S_LED_OFF;
        SEGGER_SYSVIEW_RecordEndCall(50 + I_LED_OFF);      
    case S_LED_OFF:
        SEGGER_SYSVIEW_RecordVoid(50 + S_LED_OFF);
        if (t1 - t0 >= 9 * CLOCKS_PER_SEC / 10) /*900ms OFF*/
            state = I_LED_ON;
        SEGGER_SYSVIEW_RecordEndCall(50 + S_LED_OFF);
        break;        
    }
}





