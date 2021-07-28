int tempSensorPin = A0;
int ledPin = 9;

void setup()
{
  	pinMode(tempSensorPin, INPUT);
  	pinMode(ledPin, OUTPUT);
  
  	Serial.begin(9600);
}

void loop()
{
  	// Get reading from sensor and convert to voltage
  	int reading = analogRead(tempSensorPin);
  	float voltage = reading * 5.0;
  	voltage /= 1024.0;
  
  	// Convert voltage to temperature in Celsius
  	float tempC = (voltage - 0.5) * 100;

  	Serial.println("Temp C:");
  	Serial.println(tempC);
  
  	delay(1000);
  
  	// Turn on LED if temperature is high enough
    if (tempC > 5.0) {
  		digitalWrite(ledPin, HIGH);
    } else {
  		digitalWrite(ledPin, LOW);
    }
}