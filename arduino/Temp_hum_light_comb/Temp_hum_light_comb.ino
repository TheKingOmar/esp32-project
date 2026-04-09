#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int lightPin = 32;
void setup() {
  Serial.begin(115200);
  dht.begin();

}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int lightValue = analogRead(lightPin);
  if (isnan(humidity) || isnan(temperature)){
    Serial.print("temp=?,hum=?,light=");
    Serial.println(lightValue);
  }
  else{
  Serial.print("temp=");
  Serial.print(temperature , 1);
  Serial.print(",hum=");
  Serial.print(humidity, 1);
  Serial.print(",light=");
  Serial.println(lightValue);
}
  delay(1000);

}
