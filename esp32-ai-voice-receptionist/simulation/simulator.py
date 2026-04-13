#!/usr/bin/env python3
import argparse
import math
from virtual_hardware import VirtualDisplay, VirtualMicrophone, VirtualPIRSensor, VirtualSpeaker


def generate_tone(samples=320, amp=2500, period=32):
    return [int(amp * math.sin(2 * math.pi * (i % period) / period)) for i in range(samples)]


def main() -> None:
    parser = argparse.ArgumentParser(description="ESP32 AI receptionist simulator")
    parser.add_argument("--simulate-motion", action="store_true", help="Trigger PIR motion at start")
    parser.add_argument("--inject-tone", action="store_true", help="Inject synthetic mic samples")
    parser.add_argument("--steps", type=int, default=8, help="Number of simulation loop steps")
    args = parser.parse_args()

    pir = VirtualPIRSensor()
    mic = VirtualMicrophone()
    spk = VirtualSpeaker()
    oled = VirtualDisplay()

    oled.show("Booting...", "Self-test OK")

    if args.simulate_motion:
        pir.trigger(True)
    if args.inject_tone:
        mic.inject_samples(generate_tone())

    for step in range(args.steps):
        print(f"[SIM] step={step}")
        if pir.motion:
            mic.active = True
            oled.show("Human detected", "Audio active")
            frame = mic.read_frame(64)
            spk.write(frame)
            if not frame:
                print("[SIM][MIC] no more injected samples")
        else:
            mic.active = False
            oled.show("Standby", "No motion")

    print(f"[SIM] done. speaker_frames={spk.played_frames}")


if __name__ == "__main__":
    main()
