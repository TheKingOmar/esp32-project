#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();


}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)){
    Serial.println("Failed to read");
    delay(2000);
    return;
  }
  Serial.print("temp=");
  Serial.print(temperature);
  Serial.print(",hum=");
  Serial.println(humidity);
  delay(2000);
}
