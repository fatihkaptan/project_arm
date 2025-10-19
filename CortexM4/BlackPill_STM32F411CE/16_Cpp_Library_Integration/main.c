/**
 * @file main.c
 * @brief STM32F411CE External C++ Library Integration Project
 * 
 * @details This project demonstrates how to integrate external C++ libraries
 *          into STM32 embedded projects. The main focus is on creating a 
 *          modular LED task library in C++ and using it from C code.
 *
 * Key Features:
 * - External C++ LED Task Library integration
 * - ADC sensor reading with real-time display
 * - SEGGER SystemView profiling support
 * - Clean C/C++ interface design

 * 
 * @author Fatih Kaptan
 * @date 19.03.2025
 * @version 1.0
 * -Project: 16_External_Cpp_Lib
 * Hardware: STM32F411CE BlackPill, OLED Display, Analog Sensor
 * IDE: IAR Embedded Workbench 8.50.9
 */

//******************
// Project: 16_External_Cpp_Lib
//
// DESCRIPTION:
//  ADC Sampling Application - 4.  periodic adc sampling with PWM Edge & interrupts. without DMA
//
// CREATED: 19.03.2025, by Fatih Kaptan
//
// FILE: main.c
// EWDIR: C:\iar\ewarm-8.50.9
//
//******************

#include "main.h"

/**
 * @brief Main application entry point
 * 
 * Demonstrates external C++ library integration in STM32 embedded project.
 * Uses cooperative multitasking approach with SEGGER SystemView profiling.
 * 
 * Main tasks:
 * - Task_LED_CPP: External C++ LED library demonstration (200ms ON, 800ms OFF)
 * - Task_Sensor: ADC sensor reading with OLED visualization
 * 
 * @return Never returns (infinite loop)
 * 
 * @note System clock: 100MHz, SysTick: 1ms resolution
 * @note C++ library provides modular LED control with clean C interface
 */
int main()
{       
    int Cnt=0;
    init();// Working time configurations
    while (1) {   
        Cnt = 1000;
        EXEC_TASK(Task_LED_CPP);//Task_LED();   
//        EXEC_TASK(Task_Print);
        EXEC_TASK(Task_Sensor);
        while(--Cnt);  // Delay
    }
} 

/**
 * @brief System initialization function
 * 
 * Initializes all hardware peripherals and software modules including
 * external C++ LED task library integration. Demonstrates proper
 * initialization sequence for mixed C/C++ embedded projects.
 * 
 * Initialization sequence:
 * 1. SEGGER SystemView profiling system
 * 2. GPIO clocks and I/O configuration  
 * 3. SysTick timer (1ms resolution)
 * 4. Console and OLED display
 * 5. Timer peripherals for PWM and capture
 * 6. External C++ LED task library (200ms ON, 800ms OFF)
 * 
 * @note C++ library integration shows clean interface design
 * @note LED timing demonstrates configurable external library usage
 */
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
    // Initialize C++ LED task 
    led_task_init(IOP_LED, 200, 800);  // 200ms ON, 800ms OFF
}



void init_SeggerModules(void)
{
    SEGGER_SYSVIEW_Conf();
    SYSVIEW_AddTask((void *)Task_LED_CPP, "Task_LED_CPP", 10);  // Updated to use C++ version
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



/**
 * @brief C++ LED Task wrapper function
 * 
 * Demonstrates external C++ library integration in embedded systems.
 * This function serves as a C wrapper for the C++ LED task library,
 * showing how to seamlessly integrate C++ code into C-based projects.
 * 
 * Key integration aspects:
 * - Clean C interface hiding C++ complexity
 * - State machine implementation in C++
 * - Configurable timing (initialized with 200ms ON, 800ms OFF)
 * - Professional library design patterns
 * 
 * @note This replaces the original C-based Task_LED implementation
 * @note Demonstrates modular design with external C++ library
 * @note SystemView profiling compatible via EXEC_TASK macro
 */
void Task_LED_CPP(void){
    // C++ LED task wrapper - execute external library
    led_task_run();
}


/*
// Original Task_LED function - now replaced by C++ version
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
        if (t1 - t0 >= CLOCKS_PER_SEC / 10) 
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
        if (t1 - t0 >= 9 * CLOCKS_PER_SEC / 10) 
            state = I_LED_ON;
        SEGGER_SYSVIEW_RecordEndCall(50 + S_LED_OFF);
        break;        
    }
}
*/



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
    printf("ABC�DEFG�HI�JKLMNO�PRS�TU�VYZ");
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
    //OLED_SetFont(FNT_SMALL);
}




