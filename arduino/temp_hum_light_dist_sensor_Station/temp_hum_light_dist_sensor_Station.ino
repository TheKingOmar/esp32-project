#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int trigPin = 5;
const int echoPin = 7;
const int lightPin = 8;
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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lightPin, INPUT);
  dht.begin();
  delay(1000);

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
  Serial.print("temp=");
  if(isnan(temperature)){
  Serial.print("?");
  }else{
  Serial.print(temperature , 1);
  }
  Serial.print(",hum=");
  if(isnan(humidity)){
  Serial.print("?");
  }else{
  Serial.print(humidity , 1);
  }
  Serial.print(",light=");
  Serial.print(lightValue);
  Serial.print(",dist=");
  if(isnan(distance) || distance == 0){
  Serial.println("?");
  }else{
  Serial.println(distance , 1);
  }
  lastPrint = currentTime;
  }

}
