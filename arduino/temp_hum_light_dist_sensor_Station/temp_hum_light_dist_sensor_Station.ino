#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int trigPin = 5;
const int echoPin = 7;
const int lightPin = 8;
const int SDA_Pin = 9;
const int SCL_Pin = 10;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const unsigned long intervalDHT = 1000;
const unsigned long intervalLight = 500;
const unsigned long intervalDis = 500;
const unsigned long intervalPrint = 500;
unsigned long lastDHT = 0;
unsigned long lastLight = 0;
unsigned long lastDis = 0;
unsigned long lastPrint = 0;
float distance = 0;
float humidity = 0;
float temperature = 0;
int lightValue = 0;
void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lightPin, INPUT);
  dht.begin();
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
  if (currentTime - lastDHT >= intervalDHT){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  lastDHT = currentTime;
  }
  if (currentTime - lastLight >= intervalLight){
  lightValue = analogRead(lightPin);
  lastLight = currentTime;
  }
  if (currentTime - lastDis >= intervalDis){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long echoTime = pulseIn(echoPin, HIGH, 100000);
  distance = (echoTime * 0.0343) / 2.0;
  lastDis = currentTime;
  }
  if (currentTime - lastPrint >= intervalPrint){
  display.clearDisplay();
  display.setCursor(0, 0);
  Serial.print("temp=");
  display.print("Temp=");
  if(isnan(temperature)){
  Serial.print("?");
  display.println("?");
  }else{
  Serial.print(temperature , 1);
  display.println(temperature , 1);
  }
  Serial.print(",hum=");
  display.print("Hum=");
  if(isnan(humidity)){
  Serial.print("?");
  display.println("?");
  }else{
  Serial.print(humidity , 1);
  display.println(humidity , 1);
  }
  Serial.print(",light=");
  display.print("Light=");
  Serial.print(lightValue);
  display.println(lightValue);
  Serial.print(",dist=");
  display.print("Dist=");
  if(isnan(distance) || distance == 0){
  Serial.println("?");
  display.println("?");
  }else{
  Serial.println(distance , 1);
  display.println(distance , 1);
  }
  display.display();
  lastPrint = currentTime;
  }

}
