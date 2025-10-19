#ifndef LED_TASK_CPP_H
#define LED_TASK_CPP_H

#ifdef __cplusplus
extern "C" {
#endif

    
// Simple C++ LED Task Library - 
void led_task_init(unsigned int pin_number, unsigned int on_time_ms, unsigned int off_time_ms);

// Main task function - call in main loop
void led_task_run(void);

// Optional: Change timing at runtime
void led_task_set_timing(unsigned int on_time_ms, unsigned int off_time_ms);

// Optional: Cleanup (turns LED off)
void led_task_cleanup(void);


#ifdef __cplusplus
}
#endif

#endif // LED_TASK_CPP_H