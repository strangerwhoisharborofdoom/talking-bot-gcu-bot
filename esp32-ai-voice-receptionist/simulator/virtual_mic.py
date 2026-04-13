class VirtualMic:
    def __init__(self):
        self.active = False
        self.samples = []

    def feed(self, samples):
        self.samples.extend(samples)
        print(f"[V-MIC] injected={len(samples)}")

    def read(self, n=64):
        if not self.active:
            return []
        out = self.samples[:n]
        self.samples = self.samples[n:]
        return out
