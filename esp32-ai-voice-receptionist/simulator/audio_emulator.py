class AudioEmulator:
    def __init__(self):
        self.frames = 0

    def play(self, samples):
        if not samples:
            print("[V-SPK] silence")
            return
        self.frames += 1
        print(f"[V-SPK] frame={self.frames} samples={len(samples)}")
