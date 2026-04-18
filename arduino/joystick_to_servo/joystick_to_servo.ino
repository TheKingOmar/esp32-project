#include <ESP32Servo.h>
const int xasPin = 4;
const int butPin = 7;
const int servoPin = 6;
bool autoRotation = false;
int angle = 0;
bool angleDecrease = false;
int lastbutval = HIGH;
Servo myservo;
void setup() {
  Serial.begin(115200);
  myservo.attach(servoPin);
  pinMode(butPin, INPUT_PULLUP);
  delay(1000);

}

void loop() {
  int butval = digitalRead(butPin);
  if (butval != lastbutval){
  if (lastbutval == HIGH && butval == LOW){
    autoRotation = !autoRotation;
  }
  lastbutval = butval;
  }
  if (!autoRotation){
  int xval = analogRead(xasPin);
  angle = map(xval, 0, 4095, 0, 180);
  myservo.write(angle);
  Serial.print("angle = ");
  Serial.println(angle);
  
  }else{
    angle = constrain(angle, 0, 180);
    myservo.write(angle);
    if (angle >= 180){
      angleDecrease = true;
    } else if (angle <= 0){
      angleDecrease = false;
    }
    if (angleDecrease){
      angle = angle - 5;
    } else {
      angle = angle + 5;
    }

  }
 delay(50);

}
