/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (4)
#endif
/* ISR prototypes */
void gpt_counter_overflow_isr(void);
void r_icu_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 0) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 0) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_ICU_IRQ3 ((IRQn_Type) 3) /* ICU IRQ3 (External pin interrupt 3) */
#define ICU_IRQ3_IRQn          ((IRQn_Type) 3) /* ICU IRQ3 (External pin interrupt 3) */
#define VECTOR_NUMBER_GPT1_COUNTER_OVERFLOW ((IRQn_Type) 4) /* GPT1 COUNTER OVERFLOW (Overflow) */
#define GPT1_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 4) /* GPT1 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_ICU_IRQ7 ((IRQn_Type) 7) /* ICU IRQ7 (External pin interrupt 7) */
#define ICU_IRQ7_IRQn          ((IRQn_Type) 7) /* ICU IRQ7 (External pin interrupt 7) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
