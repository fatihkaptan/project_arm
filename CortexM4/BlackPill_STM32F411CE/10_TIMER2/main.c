/**
 * @file main.c
 * @brief Timer2 PWM Application for STM32F411CE
 * @author Fatih Kaptan
 * @date 04.02.2025
 * @version 1.0
 * 
 * @details This application demonstrates Timer2 PWM generation and interrupt handling
 *          on STM32F411CE BlackPill board. Features include:
 *          - PWM signal generation
 *          - Timer interrupt handling  
 *          - Real-time performance monitoring
 *          - LED control with timer events
 * 
 * @note Compiled with IAR EWARM 8.50.9
 * @warning Ensure proper clock configuration before use
 */

#include "main.h"

/**
 * @brief Main application entry point
 * @return int Return status (never reached in embedded application)
 * 
 * @details Initializes the system and enters the main application loop.
 *          The main loop handles:
 *          - LED task execution
 *          - Button state monitoring  
 *          - PWM duty cycle adjustment
 *          - System timing coordination
 * 
 * @see init() for system initialization details
 * @see Task_LED() for LED control implementation
 * @see Task_Button() for button handling
 */
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
    init_Timers();
    //pwm(period,duty) her 1 birim 100us oalcak sekilde ayarlandi. osimin bant genisligi dar :(
    PWM_Init(100,50); //100*100us = 10ms period, 5ms OnTime
    IO_Write(IOP_LED, 1);
    IO_Init(IOP_LED, IO_MODE_OUTPUT);
}

void init_Timers(void)
{
    //Timer_Init(tmNo,prescale,period,repeat) (100Mhz/2000 -> 50k, 2k period -> 100M tick-> 1sec, 1 no repet.)
    //dikkat 2^16 asmamali prescaler sonucu
    Timer_Init(TIMER_1, SYS_CLOCK_FREQ/2000, 2000, 60);//1dk
    //Timer_Init(TIMER_2, SYS_CLOCK_FREQ/2000, 20000, 1);//10sn
    Timer_Init(TIMER_3, SYS_CLOCK_FREQ/2000, 2000, 1);//1sn
    Timer_Init(TIMER_4, SYS_CLOCK_FREQ/10000, 10, 1);//1ms
    Timer_Init(TIMER_5, SYS_CLOCK_FREQ/5000, 20, 1);//1ms
    TimerIntConfig(TIMER_1, 3);
    //TimerIntConfig(TIMER_2, 3);
    TimerIntConfig(TIMER_3, 3);
    TimerIntConfig(TIMER_4, 3);
    TimerIntConfig(TIMER_5, 3);
    Timer_Start(TIMER_1,1);
    //Timer_Start(TIMER_2,1);
    Timer_Start(TIMER_3,1);
    Timer_Start(TIMER_4,1);
    Timer_Start(TIMER_5,1);
}


void Task_Print(void){

#if TIMER_DEBUG
//    printf("1min Count: %5u\n", g_T1Count%60);
//    printf("10sec Count: %5u\n", g_T2Count%6);
//    printf("1sec Count: %5u\n", g_T3Count%60);
//    printf("1ms Count: %5u\n", g_T4Count%1000);
//    printf("1ms Count: %5u\n", g_T5Count%1000);
#else

#endif
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





