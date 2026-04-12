const int buttonPin = 4;
const int ledPin = 2;
const unsigned long intervalButton = 30;
const unsigned long intervalStatusPrint = 500;
unsigned long lastTimeButton = 0;
unsigned long lastTimeStatusPrint = 0;
int lastButtonStatus = HIGH;
bool ledState = false;
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastTimeButton >= intervalButton){
  int buttonStatus = digitalRead(buttonPin);
  if (buttonStatus != lastButtonStatus){
    if (lastButtonStatus == HIGH && buttonStatus == LOW){
    ledState = !ledState;
    if (ledState){
    digitalWrite(ledPin, HIGH);
  } else{
    digitalWrite(ledPin, LOW);
  }
    if (ledState){
      Serial.println("LED turned ON");
    } else {
      Serial.println("LED turned OFF");
    }
    }
    lastButtonStatus = buttonStatus;
  }
  lastTimeButton = currentTime;
  }
  if(currentTime - lastTimeStatusPrint >= intervalStatusPrint){
    if (ledState){
      Serial.println("LED is ON");
    } else {
      Serial.println("LED is OFF");
    }
    lastTimeStatusPrint = currentTime;
  }

}