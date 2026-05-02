#include <ESP32Servo.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
const int trigPin = 15;
const int echoPin = 16;
const int SDA_Pin = 17;
const int SCL_Pin = 8;
const int xasPin = 4;
const int butPin = 7;
const int buzzPin = 19;
const int servoPin = 6;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const unsigned long intervalBut = 100;
const unsigned long intervalDis = 500;
const unsigned long intervalRotation = 25;
const unsigned long intervalPrint = 500;
const unsigned long intervalBuzz = 500;
unsigned long lastbut = 0;
unsigned long lastrotation = 0;
unsigned long lastDis = 0;
unsigned long lastPrint = 0;
unsigned long lastBuzz = 0;
float distance = 0;
bool distValid = false;
bool autoRotation = false;
int angle = 0;
int lastAngle = 0;
bool angleDecrease = false;
int lastbutval = HIGH;
Servo myservo;
void setup() {
  Serial.begin(115200);
  delay(1000);
  myservo.attach(servoPin);
  pinMode(butPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Wire.begin(SDA_Pin, SCL_Pin);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initiating");
  display.display();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastbut >= intervalBut){
  int butval = digitalRead(butPin);
  if (butval != lastbutval){
  if (lastbutval == HIGH && butval == LOW){
    autoRotation = !autoRotation;
  }
  lastbutval = butval;
  }
  lastbut = currentTime;
  }
  if (currentTime - lastrotation >= intervalRotation){
  if (!autoRotation){
  int xval = analogRead(xasPin);
  angle = map(xval, 0, 4095, 0, 180);
  if (angle >= 85 && angle <= 95){
    angle = 90;
  }
  if (abs(angle - lastAngle) <= 3){
    angle = lastAngle;
  }
  if (lastAngle != angle){
  myservo.write(angle);
  }
  lastAngle = angle;  
  }else{
    angle = constrain(lastAngle, 0, 180);
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
    lastAngle = angle;
  }
  lastrotation = currentTime;
  }
  if (currentTime - lastDis >= intervalDis){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long echoTime = pulseIn(echoPin, HIGH, 100000);
  if(echoTime >=25000 || echoTime <= 25){
    distValid = false;
  }else {
    distValid = true;
    distance = (echoTime * 0.0343) / 2.0;
  }
  lastDis = currentTime;
  }
  if (currentTime - lastPrint >= intervalPrint){
    display.clearDisplay();
    display.setCursor(0, 0);
    Serial.print("dist=");
    display.print("Dist= ");
    if(!distValid){
      Serial.print("?");
      display.println("?");
    }else{
      Serial.println(distance , 1);
      display.println(distance , 1);
    }
    Serial.print(",angle=");
    Serial.print(angle);
    display.print("Angle= ");
    display.println(angle);
    Serial.print(",mode=");
    display.print("Mode=");
    if(autoRotation){
      Serial.println("auto");
      display.println("Auto");
    }else {
      Serial.println("manual");
      display.println("Manual");
    }
    display.display();
    lastPrint = currentTime;
  
}
  if (currentTime - lastBuzz >= intervalBuzz){
    if(distValid && distance <= 7){
      digitalWrite(buzzPin, HIGH);
    } else if (distValid && distance >= 8){
      digitalWrite(buzzPin, LOW);
    }
    lastBuzz = currentTime;
  }
  
}
