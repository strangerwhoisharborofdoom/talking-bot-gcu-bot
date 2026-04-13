from simulator.virtual_pir import VirtualPIR
from simulator.virtual_display import VirtualDisplay


if __name__ == "__main__":
    pir = VirtualPIR()
    oled = VirtualDisplay()

    pir.set_motion(True)
    oled.draw("Human detected", "Microphone active")

    pir.set_motion(False)
    oled.draw("Standby", "No motion")
