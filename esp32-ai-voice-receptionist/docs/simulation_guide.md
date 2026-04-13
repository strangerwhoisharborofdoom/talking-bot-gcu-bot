# Simulation Guide

## Purpose

Run and validate receptionist behavior without physical electronics.

## Quick Start

```bash
cd esp32-ai-voice-receptionist
python3 simulation/simulator.py --simulate-motion --inject-tone --steps 10
```

## Triggering PIR Events

- CLI: `--simulate-motion`
- API: call `VirtualPIRSensor.trigger(True)`.

## Injecting Audio Data

- CLI: `--inject-tone` to generate a synthetic tone.
- API: `VirtualMicrophone.inject_samples([...])` with PCM-like integer frames.

## Visualizing OLED Output

- Console renderer prints a framed text display.
- See latest lines logged by `VirtualDisplay.render()`.

## Running Modular Examples

```bash
python3 simulator/examples/simulate_motion.py
python3 simulator/examples/simulate_audio_input.py
```

## Expected Behavior

When motion is simulated:
1. OLED displays `Human detected`.
2. Microphone activates.
3. Speaker receives and logs output frames.
4. System logs state transition and processing stats.
