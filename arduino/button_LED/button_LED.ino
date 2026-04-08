const int buttonPin = 4;
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int buttonStatus = digitalRead(buttonPin);
  if (buttonStatus == LOW){
    Serial.println("Pressed");
    digitalWrite(ledPin, HIGH);
  }else {
    Serial.println("released");
    digitalWrite(ledPin, LOW);
  }
  delay(100);
}