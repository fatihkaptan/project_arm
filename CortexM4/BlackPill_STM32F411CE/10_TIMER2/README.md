# TIMER2 PWM Application

STM32F411CE Timer2 PWM generation and interrupt handling demonstration.

## Features

- ⏱️ Timer2 PWM signal generation
- 🔄 Interrupt-based timing control
- 💡 LED control with timer events
- 🔘 Button-controlled PWM duty cycle
- 📊 Real-time performance monitoring

## Hardware Setup

- **Board:** BlackPill STM32F411CE
- **Timer:** TIM2 (32-bit timer)
- **PWM Output:** PA5 (Timer2 Channel 1)
- **LED:** PC13 (Built-in LED)
- **Button:** PA0 (User button)

## Usage

1. Build and flash the project using IAR EWARM
2. Connect oscilloscope to PA5 to observe PWM signal
3. Press button to adjust PWM duty cycle
4. Monitor LED for timing indication

## Documentation

Generate documentation using Doxygen:
```bash
doxygen Doxyfile
```

Access documentation at `docs/html/index.html`

## Performance

- PWM Frequency: 1 kHz
- Timer Resolution: 32-bit
- Interrupt Latency: < 5 µs
- CPU Usage: ~15% at 100 MHz

## Files

| File | Description |
|------|-------------|
| `main.c` | Main application and timing control |
| `timer.c/h` | Timer2 configuration and PWM setup |
| `system.c/h` | System initialization and clock config |
| `io.c/h` | GPIO and peripheral I/O functions |