from simulator.virtual_mic import VirtualMic
from simulator.audio_emulator import AudioEmulator


if __name__ == "__main__":
    mic = VirtualMic()
    spk = AudioEmulator()

    mic.active = True
    mic.feed([100, -100, 150, -150] * 32)

    for _ in range(3):
        frame = mic.read(64)
        spk.play(frame)
