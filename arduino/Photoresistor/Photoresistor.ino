const int ADCPin = 32;
void setup() {
  Serial.begin(115200);
  pinMode(ADCPin, INPUT);

}

void loop() {
  int LightValue = analogRead(ADCPin);
  Serial.print("light=");
  Serial.println(LightValue);
  delay(1000);

}
