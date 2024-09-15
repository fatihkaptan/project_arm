#include <stdio.h>
#include <stdint.h>
#include "main.h"


volatile int _Cnt;
int fatih=0;


void init(){
  
  initClock();
  initIO();

}

int main()
{
  init();
  
      while (1) {
        // Set PC13 (LED off - out 3.3v--- <|-  3.3v)
       ++fatih;
       _Cnt++;
       //SEGGER_RTT_printf(0, "%d Deneme\r\n", _Cnt);
        GPIOC_BSRR = (1 << LED_PIN);
        //delay(8000000);
        delay_ms(1000);
        // Reset PC13 (LED on - out 0v  --- <|-  3.3v)
        GPIOC_BSRR = (1 << (LED_PIN + 16));
        delay_ms(1000);
    }
  
  
  //return 0;
}

void initClock(){
  
}

void initIO(){
      // INITIALIZATION
    RCC_AHB1ENR |= (1 << 2);  // GPIOC clock enable (Bit 2: GPIOCEN)
    
    // Set PC13 as output
    GPIOC_MODER &= ~(3 << (LED_PIN * 2));  // Clear mode bits for PC13
    GPIOC_MODER |=  (1 << (LED_PIN * 2));  // Set mode to output (01) for PC13
    
    // Set PC13 as push-pull
    GPIOC_OTYPER &= ~(1 << LED_PIN);  // Select push-pull mode for PC13
    
    // Set PC13 speed to medium
    GPIOC_OSPEEDR &= ~(3 << (LED_PIN * 2));  // Clear speed bits for PC13
    GPIOC_OSPEEDR |=  (1 << (LED_PIN * 2));  // Set speed to medium (01) for PC13
    
    // Set PC13 as no pull
    GPIOC_PUPDR &= ~(3 << (LED_PIN * 2));  // Clear pull-up/pull-down bits for PC13
    
}

void delay_ms(uint32_t ms) {
    SYSTICK_LOAD = 48000 - 1; // 1 ms delay at 16 MHz
    SYSTICK_VAL = 0;
    SYSTICK_CTRL = 5; // Enable SysTick timer with processor clock

    for (uint32_t i = 0; i < ms; i++) {
        while (!(SYSTICK_CTRL & 0x10000)); // Wait for COUNTFLAG
    }
    SYSTICK_CTRL = 1; // Disable SysTick timer
}
  
  
  
  
  