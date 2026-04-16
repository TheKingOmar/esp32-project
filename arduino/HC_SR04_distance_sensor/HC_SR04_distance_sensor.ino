const int trigPin = 4;
const int echoPin = 5;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(1000);
  Serial.println("Initiating");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long echoTime = pulseIn(echoPin, HIGH, 100000);

  if (echoTime == 0) {
    Serial.println("No echo");
  } else {
    float distance = (echoTime * 0.0343) / 2.0;
    Serial.print("Distance is: ");
    Serial.print(distance);
    Serial.println("cm");
  }

  delay(1000);
}