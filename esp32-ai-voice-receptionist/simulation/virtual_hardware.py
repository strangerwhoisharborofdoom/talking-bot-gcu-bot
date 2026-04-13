from dataclasses import dataclass, field
from typing import List


@dataclass
class VirtualPIRSensor:
    motion: bool = False

    def trigger(self, state: bool) -> None:
        self.motion = state


@dataclass
class VirtualMicrophone:
    active: bool = False
    buffer: List[int] = field(default_factory=list)

    def inject_samples(self, samples: List[int]) -> None:
        self.buffer.extend(samples)

    def read_frame(self, n: int = 64) -> List[int]:
        if not self.active or not self.buffer:
            return []
        frame = self.buffer[:n]
        self.buffer = self.buffer[n:]
        return frame


@dataclass
class VirtualSpeaker:
    played_frames: int = 0

    def write(self, frame: List[int]) -> None:
        if frame:
            self.played_frames += 1
            print(f"[SIM][SPK] frame={self.played_frames}, samples={len(frame)}")


@dataclass
class VirtualDisplay:
    line1: str = ""
    line2: str = ""

    def show(self, line1: str, line2: str = "") -> None:
        self.line1 = line1
        self.line2 = line2
        self.render()

    def render(self) -> None:
        print("+---------------- OLED ----------------+")
        print(f"| {self.line1[:34]:34s} |")
        print(f"| {self.line2[:34]:34s} |")
        print("+--------------------------------------+")
