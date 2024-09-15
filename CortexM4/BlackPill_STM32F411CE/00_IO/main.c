#include <stdint.h>

#define LED_PIN 13

#define _IO volatile // defines rw permissions
#define RCC_BASE 0x40023800
#define RCC_AHB1ENR   (*((_IO uint32_t *)(RCC_BASE + 0x30)))
#define GPIOC_BASE 0x40020800
#define GPIOC_MODER   (*((_IO uint32_t *)(GPIOC_BASE + 0x00)))
#define GPIOC_OTYPER  (*((_IO uint32_t *)(GPIOC_BASE + 0x04)))
#define GPIOC_OSPEEDR (*((_IO uint32_t *)(GPIOC_BASE + 0x08)))
#define GPIOC_PUPDR   (*((_IO uint32_t *)(GPIOC_BASE + 0x0C)))
#define GPIOC_BSRR    (*((_IO uint32_t *)(GPIOC_BASE + 0x18)))

/*systick egitim*/
#define SYSTICK_BASE  0xE000E010
#define SYSTICK_CTRL  (*((_IO uint32_t *)(SYSTICK_BASE + 0x00)))
#define SYSTICK_LOAD  (*((_IO uint32_t *)(SYSTICK_BASE + 0x04)))
#define SYSTICK_VAL   (*((_IO uint32_t *)(SYSTICK_BASE + 0x08)))


void delay(uint32_t count) { while(count--) { __asm("NOP"); }}
/*systick egitim*/
void delay_ms(uint32_t ms) {
    SYSTICK_LOAD = 16000 - 1; // 1 ms delay at 16 MHz
    SYSTICK_VAL = 0;
    SYSTICK_CTRL = 5; // Enable SysTick timer with processor clock

    for (uint32_t i = 0; i < ms; i++) {
        while (!(SYSTICK_CTRL & 0x10000)); // Wait for COUNTFLAG
    }
    SYSTICK_CTRL = 1; // Disable SysTick timer
}
int fatih=0;
int main() {
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
    
    while (1) {
        // Set PC13 (LED off - out 3.3v--- <|-  3.3v)
       ++fatih;
        GPIOC_BSRR = (1 << LED_PIN);
        //delay(8000000);
        delay_ms(1000);
        // Reset PC13 (LED on - out 0v  --- <|-  3.3v)
        GPIOC_BSRR = (1 << (LED_PIN + 16));
        delay_ms(10);
    }
    
    return 0;
}
