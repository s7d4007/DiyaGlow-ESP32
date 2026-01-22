// ESP32 - 6 LED Sequential Test (No WiFi)

int leds[] = {21, 22, 23, 19, 18, 5};  // GPIO pins for LEDs

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);   // Ensure all LEDs are OFF initially
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], HIGH);  // Turn ON LED
    delay(500);                   // 0.5 second delay
  }

  delay(1000);  // Wait 1 second after full sequence

  // Turn OFF all LEDs
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], LOW);
  }

  delay(1000);
}
