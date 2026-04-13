class VirtualPIR:
    def __init__(self):
        self.motion = False

    def set_motion(self, active: bool):
        self.motion = active
        print(f"[V-PIR] motion={self.motion}")
