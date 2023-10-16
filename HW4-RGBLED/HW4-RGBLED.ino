/*
Upon reboot/reset, RGB will be turned on in half brightness separately in red green and blue each
for one second then RGB stays white color in half brightness for 1 second

Use the potentionmeter to control the brightness of RGB

Use the 3 buttons to contorl the colors
  Button UB1 to increase the intensity of the chosen color
  Button UB2 to decrease the intensity of the chosen color
  Button EB3 to toggle the chosen color red green blue
*/

#include <Adafruit_NeoPixel.h>

#define eb3 3
#define ub1 4
#define ub2 2

#define eb3ButtonRead digitalRead(3)
#define ub1ButtonRead digitalRead(4)
#define ub2ButtonRead digitalRead(2)
#define potRead analogRead(A1)

Adafruit_NeoPixel RGB(1, 38, NEO_GRB + NEO_KHZ800);

#define rgbRed RGB.setPixelColor(0, RGB.Color(255, 0, 0))
#define rgbGreen RGB.setPixelColor(0, RGB.Color(0, 255, 0))
#define rgbBlue RGB.setPixelColor(0, RGB.Color(0, 0, 255))
#define rgbWhite RGB.setPixelColor(0, RGB.Color(128, 128, 128))



short brightness = 128;
short redIntensity = 128;
short blueIntensity = 128;
short greenIntensity = 128;

short chosenColor = 0; 
//0=red 1=green 2=blue 3=white


void setup() {
  Serial.begin(9600);

  pinMode(eb3, INPUT_PULLUP);
  pinMode(ub1, INPUT_PULLUP);
  pinMode(ub2, INPUT_PULLUP);

  RGB.begin();
  RGB.setBrightness(brightness);

  rgbRed;
  RGB.show();
  delay(1000);
  rgbGreen;
  RGB.show();
  delay(1000);
  rgbBlue;
  RGB.show();
  delay(1000);
  rgbWhite;
  RGB.show();
  delay(1000);

}

void loop() {

  potBrightness();
  delay(200);
  cycleColor();
  delay(200);
  
}

void increaseBrightness(){
  if(!ub1ButtonRead){
    brightness += 10;
    RGB.setBrightness(brightness);
    RGB.show();
  }
}

void decreaseBrightness(){
  if(!ub2ButtonRead){
    brightness -= 10;
    RGB.setBrightness(brightness);
    RGB.show();
  }
}

void potBrightness(){
  brightness = map(potRead, 0, 1023, 0, 200);
  RGB.setBrightness(brightness);
  RGB.setPixelColor(0, RGB.Color(redIntensity, greenIntensity, blueIntensity));
  RGB.show();
}

void cycleColor(){
  if(!eb3ButtonRead){
    delay(200);
    chosenColor = (chosenColor + 1) % 3;
    Serial.println(chosenColor);
  }
  switch(chosenColor){
      case 0:
        if(!ub1ButtonRead){
            delay(200); 
            redIntensity = min(redIntensity *= 1.1, 255);
            Serial.println("RED: ");
            Serial.println(redIntensity);}
        if(!ub2ButtonRead){ 
            delay(200); 
            redIntensity = max(redIntensity *= .9, 255);
            Serial.println("RED: ");
            Serial.println(redIntensity);
            }
        break;
      case 1:
        if(!ub1ButtonRead){
            delay(200); 
            greenIntensity = min(greenIntensity *= 1.1, 255);
            Serial.println("GREEN: ");
            Serial.println(greenIntensity);
          }
        if(!ub2ButtonRead){
          delay(200); 
          greenIntensity = max(greenIntensity *= .9, 255);
          Serial.println("GREEN: ");
          Serial.println(greenIntensity);
          }
        break;
      case 2:
        if(!ub1ButtonRead){
          delay(200); 
          blueIntensity = min(blueIntensity *= 1.1, 255);
          Serial.println("BLUE: ");
          Serial.println(blueIntensity);}
        if(!ub2ButtonRead){
          delay(200); 
          blueIntensity = max(blueIntensity *= .9, 255);
          Serial.println("BLUE: ");
          Serial.println(blueIntensity);
          }
        break;
      default:
        break;
    }
}