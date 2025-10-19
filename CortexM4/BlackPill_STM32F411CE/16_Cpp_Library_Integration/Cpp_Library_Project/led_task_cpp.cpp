// Simple C++ LED Task Library  

#include "led_task_cpp.h"

#define EXT_LIB
// Super minimal dependencies!
extern "C" {
    #include <stdint.h>
    #include <stdarg.h>  // For variadic functions
    
    // Simple type definitions - avoiding system.h dependencies
    typedef uint32_t clock_t;
    
    // External functions - will be linked from main project
    clock_t clock(void);
    void IO_Write(int pin_idx, int val);
}

#ifdef __cplusplus

// LED Task Class - Clean and Debuggable Implementation
class LedTask {
private:
    // State machine states
    enum LedState {
        STATE_OFF = 0,     // LED is currently OFF
        STATE_ON  = 1      // LED is currently ON  
    };
    
    // === Core State Variables ===
    LedState current_state;        // Current LED state (ON/OFF)
    bool     is_initialized;       // Task initialization flag
    
    // === Timing Configuration ===
    uint32_t on_duration_ms;       // How long LED stays ON (milliseconds)
    uint32_t off_duration_ms;      // How long LED stays OFF (milliseconds)
    
    // === Hardware Configuration ===
    int      led_pin_number;       // Pin number for the LED (0=IOP_LED, 1=IOP_PWM, etc.)
    
    // === Timing Control ===
    clock_t  state_start_time;     // When current state started
    clock_t  current_time;         // Current system time
    uint32_t elapsed_time_ms;      // Time elapsed in current state
    
    // === Helper Methods ===
    void turnLedOn() {
        IO_Write(led_pin_number, 0);  // Active low - 0 turns LED ON
        current_state = STATE_ON;
        state_start_time = current_time;
    }
    
    void turnLedOff() {
        IO_Write(led_pin_number, 1);  // Active low - 1 turns LED OFF  
        current_state = STATE_OFF;
        state_start_time = current_time;
    }
    
    void updateTiming() {
        current_time = clock();
        elapsed_time_ms = current_time - state_start_time;
    }
    
public:
    // Constructor - set safe defaults
    LedTask() : 
        current_state(STATE_OFF),
        is_initialized(false),
        on_duration_ms(1000),          // Default: 1000ms ON (1 second)
        off_duration_ms(5000),         // Default: 5000ms OFF (5 seconds)  
        led_pin_number(0),             // Default: pin 0 (IOP_LED)
        state_start_time(0),
        current_time(0),
        elapsed_time_ms(0)
    {
        // Constructor complete
    }
    
    // Initialize the LED task
    void initialize(int pin_number, uint32_t on_time_ms, uint32_t off_time_ms) {
        led_pin_number = pin_number;
        on_duration_ms = on_time_ms;
        off_duration_ms = off_time_ms;
        
        current_state = STATE_OFF;
        state_start_time = clock();
        is_initialized = true;
        
        // Start with LED OFF
        turnLedOff();
    }
    
    // Main state machine - call repeatedly in main loop
    void executeStateMachine() {
        if (!is_initialized) {
            return;  // Not ready yet
        }
        
        updateTiming();
        
        switch (current_state) {
            case STATE_OFF:
                // LED is OFF - check if it's time to turn ON
                if (elapsed_time_ms >= off_duration_ms) {
                    turnLedOn();
                }
                break;
                
            case STATE_ON:
                // LED is ON - check if it's time to turn OFF
                if (elapsed_time_ms >= on_duration_ms) {
                    turnLedOff();
                }
                break;
                
            default:
                // Invalid state - reset to OFF
                current_state = STATE_OFF;
                turnLedOff();
                break;
        }
    }
    
    // Change timing parameters at runtime
    void updateTimingParameters(uint32_t new_on_ms, uint32_t new_off_ms) {
        on_duration_ms = new_on_ms;
        off_duration_ms = new_off_ms;
    }
    
    // Cleanup - turn LED off and deinitialize
    void shutdown() {
        if (is_initialized) {
            turnLedOff();
            is_initialized = false;
        }
    }
    
    // === Debug/Status Methods ===
    LedState getCurrentState() const { return current_state; }
    uint32_t getElapsedTime() const { return elapsed_time_ms; }
    uint32_t getOnDuration() const { return on_duration_ms; }
    uint32_t getOffDuration() const { return off_duration_ms; }
    int getPinNumber() const { return led_pin_number; }
    bool isInitialized() const { return is_initialized; }
};

// Global instance
static LedTask g_ledTask;

#endif // __cplusplus

// C interface 
extern "C" {

    
    // 3 parameters: pin + on_time + off_time
    void led_task_init(unsigned int pin_idx, unsigned int on_time_ms, unsigned int off_time_ms) {
        #ifdef __cplusplus
        g_ledTask.initialize(pin_idx, on_time_ms, off_time_ms);
        #endif
    }
    
    void led_task_run(void) {
        #ifdef __cplusplus
        g_ledTask.executeStateMachine();
        #endif
    }
    
    void led_task_set_timing(unsigned int on_time_ms, unsigned int off_time_ms) {
        #ifdef __cplusplus
        g_ledTask.updateTimingParameters(on_time_ms, off_time_ms);
        #endif
    }
    
    void led_task_cleanup(void) {
        #ifdef __cplusplus
        g_ledTask.shutdown();
        #endif
    }
    
}