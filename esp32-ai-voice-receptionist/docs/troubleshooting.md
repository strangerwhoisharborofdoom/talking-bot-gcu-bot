# Troubleshooting

## No OLED Output

- Verify I2C pins (SDA 21, SCL 19).
- Confirm display address is `0x3C`.
- Check power and ground continuity.

## Distorted Audio

- Confirm both I2S channels are set to 16 kHz.
- Ensure correct bit depth (16-bit samples).
- Keep microphone wiring short and stable.

## No Motion Detection

- PIR requires warm-up time (typically 30-60 seconds).
- Validate `GPIO 27` with serial prints.
- Check PIR sensitivity/delay trim potentiometers.

## Build Errors (Arduino)

- Install ESP32 board package.
- Add `Adafruit GFX` and `Adafruit SH110X`.
- Use modern ESP32 Arduino core supporting `driver/i2s.h`.

## I2S Conflicts

- Confirm MCLK is disabled in both I2S configurations.
- Avoid using pins that overlap with SPI flash or strapping behavior.
