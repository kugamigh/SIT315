// Pins
const uint8_t BTN_PIN = 2;

// Global
int btn_presses = 0;

void setup() {
    pinMode(BTN_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(BTN_PIN), toggle, FALLING);
  
  	Serial.begin(9600);
}

void loop() {
    delay(500);
}

void toggle() {
  	btn_presses += 1;
    Serial.print("Button was pressed ");
  	Serial.print(btn_presses);
  if (btn_presses == 1) {
    Serial.println(" time.");
  } else {
    Serial.println(" times.");
  }
}
