//******************
// Project: 11_TIMER3_CAPTURE
//
// DESCRIPTION:
//  Timer applications - Input Capture Unit(10 us precise)
//
// CREATED: 04.02.2025, by Fatih Kaptan
//
// FILE: main.c
// EWDIR: C:\iar\ewarm-8.50.9
//
//******************

#include "main.h"


int main()
{
    
    init();// Working time configurations
    
    while (1) {       
        Task_LED();   
        Task_Print();
    }
} 

void init(void)
{
    Sys_IoInit();
    Sys_TickInit();
    Sys_ConsoleInit();    
    init_Timers();
    PWM_Init(100,50); //100*100us = 10ms period, 5ms OnTime capture denemek icin
    Capture_Init();
    init_OLED();
    IO_Write(IOP_LED, 1);
    IO_Init(IOP_LED, IO_MODE_OUTPUT);
}

void init_Timers(void)
{
    //Timer_Init(tmNo,prescale,period,repeat) (100Mhz/2000 -> 50k, 2k period -> 100M tick-> 1sec, 1 no repet.)
    //dikkat 2^16 asmamali prescaler sonucu
    Timer_Init(TIMER_1, SYS_CLOCK_FREQ/2000, 2000, 60);//1dk
    //Timer_Init(TIMER_2, SYS_CLOCK_FREQ/2000, 20000, 1);//10sn
    //Timer_Init(TIMER_3, SYS_CLOCK_FREQ/2000, 20000, 10);//10sn
    Timer_Init(TIMER_4, SYS_CLOCK_FREQ/10000, 10, 1);//1ms
    Timer_Init(TIMER_5, SYS_CLOCK_FREQ/2000, 2000, 1);//1s
    TimerIntConfig(TIMER_1, 3);
    //TimerIntConfig(TIMER_2, 3);
    //TimerIntConfig(TIMER_3, 3);
    TimerIntConfig(TIMER_4, 3);
    TimerIntConfig(TIMER_5, 3);
    Timer_Start(TIMER_1,1);
    //Timer_Start(TIMER_2,1);
    //Timer_Start(TIMER_3,1);
    Timer_Start(TIMER_4,1);
    Timer_Start(TIMER_5,1);
}


void Task_Print(void){
    static unsigned long count;
    FNT_t font;
    int row, col;
#if TIMER_DEBUG
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
    OLED_SetFont(font);
    OLED_SetCursor(row, col);
#else
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
#endif
}

void init_OLED(void){
    OLED_Rotate(0);
    printf("ABCÇDEFGÐHIÝJKLMNOÖPRSÞTUÜVYZ");
    DelayMs(500);
    OLED_ClearDisplay();
    
    OLED_SetFont(FNT_LARGE);
    OLED_SetCursor(0, 0);
    printf("CIGERIMSIN");
    DelayMs(500);
    OLED_ClearDisplay();  
    
    OLED_Line(0, 0, 127, 63, SET_PIXEL);DelayMs(250);
    OLED_Line(0, 63, 127, 0, SET_PIXEL);DelayMs(250);
    OLED_Line(0, 23, 127, 23, SET_PIXEL);DelayMs(250);
    OLED_Line(57, 0, 57, 63, SET_PIXEL);DelayMs(250);
    OLED_Line(9, 11, 103, 47, SET_PIXEL);DelayMs(250);
    OLED_Circle(60, 25, 19, SET_PIXEL);DelayMs(250);
    OLED_Circle(60, 55, 12, SET_PIXEL);DelayMs(250);
    OLED_Circle(30, 25, 19, SET_PIXEL);DelayMs(250);
    OLED_ClearDisplay();  
}

void Task_LED(void){
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





