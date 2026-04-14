const int transPin = 4;
int brightness = 0;
const int pwmFreq = 5000;
const int pwmRes = 8;
bool fadingDown = false;
const unsigned long interval = 100;
unsigned long lastTime = 0;
void setup() {
  ledcAttach(transPin, pwmFreq, pwmRes);

}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= interval){
  if(!fadingDown){
  brightness = brightness + 5;
     if (brightness >= 255){
     fadingDown = true;
     brightness = brightness - 5;
  } 
   }
   else {
    brightness = brightness - 5;
    if (brightness <= 0){
    fadingDown = false;
    brightness = brightness + 5;
  } 
   }
  
  ledcWrite(transPin, brightness);
  lastTime = currentTime;
  }
}
