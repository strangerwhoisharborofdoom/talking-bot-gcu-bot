# Hardware Setup

## Electrical Notes

- ESP32 logic is 3.3V.
- PIR and amplifier can be powered from 5V, but signal lines to ESP32 GPIOs must remain 3.3V-safe.
- Use common ground among all modules.

## Pin Map

### INMP441
- WS: GPIO 33
- SCK: GPIO 32
- SD: GPIO 35

### MAX98357A
- LRC: GPIO 25
- BCLK: GPIO 26
- DIN: GPIO 22

### PIR
- OUT: GPIO 27

### SH1106 OLED
- SDA: GPIO 21
- SCL: GPIO 19

## Bring-up Procedure

1. Flash `src/main.ino`.
2. Open serial monitor at 115200.
3. Wait for boot self-test results.
4. Trigger PIR by motion in front of sensor.
5. Verify OLED status transitions.
6. Confirm loopback audio when motion is detected.
