
const int gasPin = 34; // A0 -> GPIO34 (ADC1_CH6)

void setup() {
  Serial.begin(115200);
  delay(200);
  analogReadResolution(12);                  
  analogSetPinAttenuation(gasPin, ADC_11db); // ~0..3.3V input range
}

uint16_t readAvg(int pin, int n = 32) {
  uint32_t sum = 0;
  for (int i = 0; i < n; i++) {
    sum += analogRead(pin);
    delayMicroseconds(200);
  }
  return sum / n;
}

void loop() {
  uint16_t raw = readAvg(gasPin);
  uint32_t mv = analogReadMilliVolts(gasPin);

  Serial.print("RAW: "); Serial.print(raw);
  Serial.print("  |  ");
  Serial.print("Voltage: "); Serial.print(mv); Serial.println(" mV");

 
  if (raw > 7) {
    Serial.println("Gas Detected!");
  } 
  else if (raw > 3) {
    Serial.println("Slight Gas Presence!");
  } 
  else {
    Serial.println("Air is Clean");
  }

  delay(1000);
}
