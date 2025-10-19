# STM32 External C++ Library Integration Project

## Overview

This project demonstrates **external C++ library integration** in STM32 embedded development. The main goal is to show how to create and use a **C++ Task/Func. Library** as an external library in a C-based STM32 project.

## Key Features

- **External C++ Library**: Modular LED task implementation in C++
- **Clean C Interface**: Seamless integration between C and C++ code

## Project Structure

```
16_Sensor_ADC_wTIM/
├── main.c                    # Main C application
├── main.h                    # Header with C++ library integration
├── Cpp_Library_Project/      # External C++ LED Library
│   ├── led_task_cpp.h        # C interface header
│   └── led_task_cpp.cpp      # C++ implementation
```

## C++ Library Usage

### Simple Usage
```c
#include "led_task_cpp.h"

// Initialize LED task 
led_task_init(IOP_LED,ontime,offtime);

// In main loop
while(1) {
    led_task_run();  // Execute LED state machine
}

// Change timing at runtime
led_task_set_timing(500, 2000);
```

## Build Configuration

- **IDE**: IAR Embedded Workbench 8.50.9
- **Target**: STM32F411CEUx (100MHz)
- **Libraries**: STM32F4xx HAL

## Hardware Requirements

- STM32F411CE BlackPill board
- LED connected to PC13 (onboard LED)
- ST-Link v2 debugger

## Key Learning Points

1. **C++ Library Creation** for embedded systems
2. **extern "C"** linkage for C/C++ integration  
3. **Modular design** with clean interfaces
4. **State machine implementation** in C++
---
