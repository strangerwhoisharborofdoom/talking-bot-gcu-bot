class VirtualDisplay:
    def draw(self, line1, line2=""):
        print("[V-OLED] ------------------------------")
        print(f"[V-OLED] {line1}")
        if line2:
            print(f"[V-OLED] {line2}")
