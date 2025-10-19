# ARM Embedded Systems Project Collection

A comprehensive collection of ARM Cortex-M microcontroller projects featuring STM32 and Renesas RA series development examples.

## 🔧 Hardware Platforms

| Platform | MCU | Description |
|----------|-----|-------------|
| **BlackPill** | STM32F411CE | ARM Cortex-M4 development board |
| **BluePill** | STM32F103C8T6 | ARM Cortex-M3 development board |
| **EK-RA2A1** | R7FA2L1AB | ARM Cortex-M23 Renesas evoboard |

## 📁 Project Structure

```
project_arm/
├── CortexM23/   # Renesas RA2A1 
├── CortexM3/    # STM32F103 projects
├── CortexM4/    # STM32F411 projects
└── Simulator/   # IAR EWARM Sim projects
```

## 🛠️ Development Environment

- **IDE:** IAR Embedded Workbench for ARM 8.50.9
- **Debugger:** Integrated IAR C-SPY debugger
- **Documentation:** Doxygen for code documentation

## 📖 Quick Start

1. **Clone the repository:**
   ```bash
   git clone https://gitlab.com/fatihkaptan/project_arm.git
   cd project_arm
   ```

2. **Open in IAR EWARM:**
   - Navigate to desired project folder
   - Open the `.eww` workspace file
   - Build and debug

3. **Hardware Setup:**
   - Connect your development board
   - Configure debugger settings
   - Flash and run

## 🔍 Project Features

- ✅ Peripheral drivers (GPIO, UART, SPI, ADC, Timers)
- ✅ Real-time performance optimization
- ✅ System analysis with SystemView
- ✅ Mixed C/C++ programming examples
- ✅ Comprehensive documentation
- ✅ Multiple ARM Cortex-M platforms

## 📚 Learning Path

1. **Basics:** Start with `01_Base` and `00_IO`
2. **Communication:** Progress to `05_UART_LCD`
3. **Timing,:** Explore timer projects (`09_TIMER1`, `10_TIMER2`)
4. **Segger Sysview Tools and Advanced:** Try `15_Sensor_ADC_wTIM` and `12_SYSTEMVIEW_APP`
5. **Mixed Programming C/C++:** Study `Simulator/00_MixingC_C++`

## � Project Documentation

### 📋 Available Project READMEs

| Project | Description | Location |
|---------|-------------|----------|
| **[C/C++ Mixed Programming](./Simulator/00_MixingC_C++/README.md)** | Examples for using C and C++ languages together | `Simulator/00_MixingC_C++/` |
| **[STM32 External C++ Library Integration](./CortexM4/BlackPill_STM32F411CE/16_Cpp_Library_Integration/README.md)** | C++ library integration in STM32 embedded development | `CortexM4/BlackPill_STM32F411CE/16_Cpp_Library_Integration/` |
| **[SystemView Application](./CortexM4/BlackPill_STM32F411CE/12_SYSTEMWIEW_APP/README.md)** | Real-time task analysis using SEGGER SystemView | `CortexM4/BlackPill_STM32F411CE/12_SYSTEMWIEW_APP/` |
| **[TIMER2 PWM Application](./CortexM4/BlackPill_STM32F411CE/10_TIMER2/README.md)** | PWM generation and interrupt handling | `CortexM4/BlackPill_STM32F411CE/10_TIMER2/` |

## �📄 License

This project is available for educational and development purposes.

---
*Last updated: October 2025*