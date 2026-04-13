# esp32-ai-voice-receptionist

A research-style ESP32 robotics prototype for an AI voice receptionist with both **real hardware firmware** and a **software simulation environment**.

## Overview

This project enables two development paths:

1. **Hardware mode** on ESP32 NodeMCU + peripherals.
2. **Simulation mode** on a desktop/laptop without electronics.

Core behavior:
- Detect human presence using PIR.
- Show live status on SH1106 OLED.
- Capture audio from INMP441 via I2S.
- Play audio to MAX98357A + speaker via I2S.
- Run mic-to-speaker loopback at 16 kHz.
- Execute boot self-test with serial diagnostics.

## Hardware Bill of Materials

- ESP32 NodeMCU (CP2102)
- INMP441 I2S microphone
- MAX98357A I2S amplifier + speaker
- PIR motion sensor
- 1.3 inch OLED display (SH1106, I2C)
- Extension board / breadboard + jumpers

## Wiring Table

### Microphone (INMP441)

| INMP441 | ESP32 GPIO |
|---|---|
| VDD | 3.3V |
| GND | GND |
| L/R | GND |
| WS | GPIO 33 |
| SCK | GPIO 32 |
| SD | GPIO 35 |

### Speaker Amplifier (MAX98357A)

| MAX98357A | ESP32 GPIO |
|---|---|
| VIN | 5V |
| GND | GND |
| LRC | GPIO 25 |
| BCLK | GPIO 26 |
| DIN | GPIO 22 |

### PIR Sensor

| PIR | ESP32 GPIO |
|---|---|
| VCC | 5V |
| GND | GND |
| OUT | GPIO 27 |

### OLED Display (SH1106 I2C)

| OLED | ESP32 GPIO |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 19 |

## System Architecture

- `src/main.ino` contains runtime firmware state machine.
- `examples/*` has isolated component tests.
- `simulation/` provides a Python virtual hardware harness.
- `simulator/` provides modular component-level simulation utilities.

See `docs/architecture.md` and `assets/architecture.png`.

## Firmware Setup (Hardware Mode)

1. Install Arduino IDE 2.x.
2. Install ESP32 board package (Espressif).
3. Install libraries:
   - `Adafruit GFX Library`
   - `Adafruit SH110X`
4. Open `src/main.ino`.
5. Select board: **ESP32 Dev Module**.
6. Set upload speed (recommended 921600 or 460800).
7. Flash and monitor serial at **115200 baud**.

## Simulation Setup (No Hardware)

### Option A: Python simulation

```bash
cd esp32-ai-voice-receptionist
python3 simulation/simulator.py --help
python3 simulation/simulator.py --simulate-motion --inject-tone
```

### Option B: Modular simulator components

```bash
cd esp32-ai-voice-receptionist
python3 simulator/examples/simulate_motion.py
python3 simulator/examples/simulate_audio_input.py
```

### Option C: Wokwi

Use `simulation/wokwi_project.json` and `simulator/esp32_simulation.json` as starting templates.

## Documentation

- Hardware assembly: `docs/hardware_setup.md`
- Architecture: `docs/architecture.md`
- Troubleshooting: `docs/troubleshooting.md`
- Simulation walkthrough: `docs/simulation_guide.md`

## Troubleshooting

Quick checks:
- Verify all grounds are common.
- Confirm I2S pins are not shared with conflicting peripherals.
- Keep microphone power at 3.3V.
- Ensure MCLK is disabled in software configs.
- For OLED issues, verify I2C address (`0x3C`) and cable orientation.

Full details: `docs/troubleshooting.md`

## Contributing

1. Fork and create a feature branch.
2. Include tests or simulation logs.
3. Update docs for behavior changes.
4. Submit PR with reproduction steps.

## License

MIT License (see `LICENSE`).
