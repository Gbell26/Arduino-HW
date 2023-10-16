/*
3 buttons
Both leds should blink (5hz) for 3 seconds right after reboot/reset
Button UB1 is a toggle switch: if pressed once green LED should turn off, if pressed again it will be turned off
Button UB2 is a press switch: if pressed and hold red led will be turned on otherwise it will be turned off
button eb3 is a delay switch: if pressed both leds will be turned on for 5 sec then turned off
*/

#define greenLed  12
#define redLed 13
#define eb3 8
#define ub1 3
#define ub2 5

#define eb3ButtonRead digitalRead(8)
#define ub1ButtonRead digitalRead(3)
#define ub2ButtonRead digitalRead(5)

#define greenLedOn digitalWrite(12, HIGH)
#define greenLedOff digitalWrite(12, LOW)

#define redLedOn digitalWrite(13, HIGH)
#define redLedOff digitalWrite(13, LOW)

bool ub1On = false;

void blink(){
    for(int i=0; i<15; i++){
    greenLedOn;
    redLedOn;
    delay(100);
    greenLedOff; 
    redLedOff;
    delay(100);
  }

}

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(eb3, INPUT_PULLUP);
  pinMode(ub1, INPUT_PULLUP);
  pinMode(ub2, INPUT_PULLUP);

  //when turned on blink at 5hz for 3 seconds
  blink();
}

void loop() {
  //turn on green led when press ub1, turn off again after pressing again
  //when ub1 is pressed
  
  toggleGreenLed();
  delay(200);
  toggleRedLed();
  delay(200);
  toggleBothFiveSec();
  delay(200);
  


}

void toggleGreenLed(){
  //if the light is off turn it on
  if(!ub1ButtonRead){
    if(!ub1On){
      greenLedOn;
      ub1On = true;
    }
    //if it is on turn it off
    else{
      greenLedOff;
      ub1On = false;
    }
  }
}

void toggleRedLed(){
    //press and hold ub2 to turn on red led
    //turn on red led while it is pressed
  while(!ub2ButtonRead){
     redLedOn;
  }
  //turn off led when released
  redLedOff;
}

void toggleBothFiveSec(){
  //if eb3 pressed turn both lights on for 5 seconds then turn off
  if(!eb3ButtonRead){
    greenLedOn;
    redLedOn;
    delay(5000);
    greenLedOff;
    redLedOff;
  }
}
