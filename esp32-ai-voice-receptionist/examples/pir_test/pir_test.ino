#include <Arduino.h>

static constexpr int PIR_PIN = 27;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  Serial.println(digitalRead(PIR_PIN) ? "MOTION" : "NO_MOTION");
  delay(250);
}
