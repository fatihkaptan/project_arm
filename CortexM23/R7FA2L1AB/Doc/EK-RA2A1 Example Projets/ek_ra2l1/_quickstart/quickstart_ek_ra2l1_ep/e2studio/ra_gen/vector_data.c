/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [3] = r_icu_isr, /* ICU IRQ3 (External pin interrupt 3) */
            [4] = gpt_counter_overflow_isr, /* GPT1 COUNTER OVERFLOW (Overflow) */
            [7] = r_icu_isr, /* ICU IRQ7 (External pin interrupt 7) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_OVERFLOW,GROUP0), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ3,GROUP3), /* ICU IRQ3 (External pin interrupt 3) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_GPT1_COUNTER_OVERFLOW,GROUP4), /* GPT1 COUNTER OVERFLOW (Overflow) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ7,GROUP7), /* ICU IRQ7 (External pin interrupt 7) */
        };
        #endif
        #endif
