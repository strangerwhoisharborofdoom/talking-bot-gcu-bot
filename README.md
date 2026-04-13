# talking-bot-gcu-bot
ESP32-based AI voice receptionist prototype integrating an INMP441 I2S microphone, MAX98357A speaker amplifier, PIR motion sensor, and SH1106 OLED display. Includes real-time audio loopback, motion detection, visual feedback, debugging tools, and a simulation environment to test the system without physical hardware. 🤖

# esp32-ai-voice-receptionist

A research-grade ESP32 robotics prototype for an AI voice receptionist system with both **real hardware firmware** and a **software simulation environment**.

The project is designed for engineering labs, robotics portfolios, and embedded systems experimentation. It allows developers to:

- Run the system on real ESP32 hardware
- Simulate the system without physical electronics
- Validate motion detection, OLED state transitions, microphone input, speaker output, and system logs
- Extend the architecture into a larger HRI (Human-Robot Interaction) platform

## Overview

This project implements a robotic receptionist prototype capable of:

- Detecting human presence with a PIR sensor
- Displaying system state on a 1.3 inch SH1106 OLED
- Capturing audio using an INMP441 I2S microphone
- Sending audio to a MAX98357A I2S amplifier and speaker
- Performing real-time microphone to speaker loopback
- Running boot-time self-tests and serial diagnostics
- Simulating full system behavior without hardware

## Core Hardware

- ESP32 NodeMCU (CP2102)
- INMP441 I2S microphone
- MAX98357A I2S amplifier + speaker
- PIR motion sensor
- 1.3 inch SH1106 OLED display
- Extension board / breadboard power routing

## Wiring

### Microphone (INMP441)

| INMP441 Pin | ESP32 Pin |
|---|---|
| VDD | 3.3V |
| GND | GND |
| L/R | GND |
| WS | GPIO 33 |
| SCK | GPIO 32 |
| SD | GPIO 35 |

### Speaker (MAX98357A)

| MAX98357A Pin | ESP32 Pin |
|---|---|
| VIN | 5V |
| GND | GND |
| LRC | GPIO 25 |
| BCLK | GPIO 26 |
| DIN | GPIO 22 |

### PIR Sensor

| PIR Pin | ESP32 Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| OUT | GPIO 27 |

### OLED Display (SH1106)

| OLED Pin | ESP32 Pin |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 19 |

## Features

- PIR-based human presence detection
- OLED status display
- I2S microphone input at 16 kHz
- I2S speaker output
- Real-time microphone to speaker loopback
- Serial debugging and diagnostics
- Hardware self-test during boot
- Software simulation mode for development without hardware

## Software Stack

### Firmware
- Arduino C++
- `driver/i2s.h`
- `Wire.h`
- `Adafruit_GFX`
- `Adafruit_SH110X`

### Simulation
- Python-based virtual hardware environment
- Event-driven PIR/audio/display emulation
- Console-based behavior testing and logs
- Optional Wokwi-ready configuration support

## Repository Structure

```text
esp32-ai-voice-receptionist/
├── README.md
├── LICENSE
├── docs/
│   ├── hardware_setup.md
│   ├── architecture.md
│   ├── troubleshooting.md
│   └── simulation_guide.md
├── src/
│   └── main.ino
├── examples/
│   ├── mic_test/
│   ├── speaker_test/
│   ├── pir_test/
│   └── display_test/
├── simulation/
│   ├── wokwi_project.json
│   ├── simulator.py
│   ├── virtual_hardware.py
│   └── examples/
│       ├── simulate_motion.py
│       └── simulate_audio_input.py
└── assets/
    ├── wiring_diagram.png
    ├── architecture.png
    └── simulation_diagram.png
```

## Firmware Behavior

At boot, the ESP32 performs self-tests for:

- Serial communication
- PIR sensor input
- OLED availability
- Microphone I2S initialization
- Speaker I2S initialization

Runtime state flow:

```text
BOOT -> IDLE -> HUMAN_DETECTED -> LISTENING -> AUDIO_LOOPBACK -> IDLE
```

When motion is detected:

1. OLED displays `Human detected`
2. System activates microphone processing
3. Speaker outputs loopback or response audio
4. Serial logs show event activity

## Simulation Mode

The `simulation/` environment allows testing without electronics.

Simulated components:

- Virtual PIR sensor
- Virtual microphone
- Virtual speaker
- Virtual OLED display

Example events:

- Trigger motion detection
- Inject synthetic microphone samples
- Emulate speech waveform input
- Render OLED text output
- Log speaker playback activity

## Getting Started

### 1. Hardware Firmware

1. Open `src/main.ino` in Arduino IDE or PlatformIO
2. Install required libraries:
   - Adafruit GFX Library
   - Adafruit SH110X
3. Select your ESP32 board
4. Flash the firmware
5. Open Serial Monitor at the configured baud rate

### 2. Simulation

1. Go to the `simulation/` folder
2. Run the simulator:
   ```bash
   python simulator.py
   ```
3. Run examples:
   ```bash
   python examples/simulate_motion.py
   python examples/simulate_audio_input.py
   ```

## Documentation

Detailed engineering documentation is provided in:

- `docs/hardware_setup.md`
- `docs/architecture.md`
- `docs/troubleshooting.md`
- `docs/simulation_guide.md`

## Roadmap

- [ ] Complete production firmware
- [ ] Add isolated hardware test sketches
- [ ] Implement Python simulation framework
- [ ] Add Wokwi simulation profile
- [ ] Create architecture and wiring diagrams
- [ ] Expand troubleshooting and validation workflows

## Contributing

Contributions are welcome for:

- Embedded firmware improvements
- Audio pipeline improvements
- Simulation enhancements
- Documentation quality
- Hardware validation notes
- Lab testing workflows

Please open an issue or pull request with a clear description of the proposed improvement.

## License

This project is licensed under the repository's `LICENSE` file.
