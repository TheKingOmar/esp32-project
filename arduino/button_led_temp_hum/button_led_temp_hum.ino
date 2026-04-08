#include <DHT.h>

const int buttonPin = 4;
const int ledPin = 21;

#define DHTPIN 18
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float lastHumidity = NAN;
float lastTemperature = NAN;

unsigned long lastButtonTime = 0;
unsigned long lastDhtTime = 0;

const unsigned long buttonInterval = 100;
const unsigned long dhtInterval = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  dht.begin();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastButtonTime >= buttonInterval) {
    lastButtonTime = currentTime;

    int buttonStatus = digitalRead(buttonPin);

    if (buttonStatus == LOW) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    Serial.print("button=");
    if (buttonStatus == LOW) {
      Serial.print(1);
    } else {
      Serial.print(0);
    }

    Serial.print(",led=");
    if (buttonStatus == LOW) {
      Serial.print(1);
    } else {
      Serial.print(0);
    }

    Serial.print(",temp=");
    if (isnan(lastTemperature)) {
      Serial.print("?");
    } else {
      Serial.print(lastTemperature);
    }

    Serial.print(",hum=");
    if (isnan(lastHumidity)) {
      Serial.println("?");
    } else {
      Serial.println(lastHumidity);
    }
  }

  if (currentTime - lastDhtTime >= dhtInterval) {
    lastDhtTime = currentTime;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (!isnan(humidity) && !isnan(temperature)) {
      lastHumidity = humidity;
      lastTemperature = temperature;
    }
  }
}