# Architecture

## Runtime State Machine

- **BOOT**: Initialize serial, GPIO, OLED, I2S mic, I2S speaker.
- **SELF_TEST**: Verify each subsystem and publish status.
- **IDLE**: Wait for PIR motion while displaying standby.
- **ACTIVE_LISTEN**: On motion, capture mic samples.
- **ACTIVE_SPEAK**: Stream samples to speaker (loopback).

## Firmware Components

- `initDisplay()` configures SH1106 over I2C.
- `initMicI2S()` configures I2S_NUM_0 RX at 16 kHz.
- `initSpeakerI2S()` configures I2S_NUM_1 TX at 16 kHz.
- `runSelfTest()` validates PIR read, display draw, I2S readiness.
- `audioLoopbackStep()` reads mic DMA buffers and writes to speaker.

## Simulation Components

Two layers are provided:

1. `simulation/virtual_hardware.py` + `simulation/simulator.py`
   - Full behavioral simulation runner.
2. `simulator/*.py`
   - Fine-grained modular emulators for PIR, mic, display, and audio.

## Data Flow

PIR event -> state transition to ACTIVE -> mic frame capture -> speaker output -> OLED update -> log.
