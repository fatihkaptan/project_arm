#include "stm32f4xx.h"


/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void initClock();
void initIO();
void delay_ms(uint32_t ms);

/*bunlari simdilik elle kullaniyom*/
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


#define LED_PIN 13