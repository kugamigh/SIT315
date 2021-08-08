// Pins
// PIR sensors
const int L_PIR_PIN = 4;
const int M_PIR_PIN = 3;
const int R_PIR_PIN = 2;

// LED pins
const int R_LED_PIN = 13;
const int G_LED_PIN = 12;
const int B_LED_PIN = 11;

// States
uint8_t R_STATE = LOW;
uint8_t G_STATE = LOW;
uint8_t B_STATE = LOW;

void setup() {
  pinMode(R_LED_PIN, OUTPUT);
  pinMode(G_LED_PIN, OUTPUT);
  pinMode(B_LED_PIN, OUTPUT);
  
  pinMode(L_PIR_PIN, INPUT);
  pinMode(M_PIR_PIN, INPUT);
  pinMode(R_PIR_PIN, INPUT);
  
  Serial.begin(9600);
  
  // Attach interrupts to each PIR sensor to be triggered on change
  attachInterrupt(digitalPinToInterrupt(L_PIR_PIN), l_motion, CHANGE);
  attachInterrupt(digitalPinToInterrupt(M_PIR_PIN), m_motion, CHANGE);
  attachInterrupt(digitalPinToInterrupt(R_PIR_PIN), r_motion, CHANGE);
}

void loop(){
  delay(1000);
}

void l_motion(){
  R_STATE = !R_STATE;
  Serial.println("Left - Toggle Red");
  digitalWrite(R_LED_PIN, R_STATE);
}

void m_motion(){
  G_STATE = !G_STATE;
  Serial.println("Middle - Toggle Green");
  digitalWrite(G_LED_PIN, G_STATE);
}

void r_motion(){
  B_STATE = !B_STATE;
  Serial.println("Right - Toggle Blue");
  digitalWrite(B_LED_PIN, B_STATE);
}
