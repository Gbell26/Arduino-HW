#define PWM_A 4 // left motor
#define PWM_B 5 // Right Motor
#define AIN1 32
#define AIN2 34
#define BIN1 30
#define BIN2 36
#define ENCODERA 2 //left encoder
#define ENCODERB 3 //right encoder
#define buttonReadOne digitalRead(6)
#define buttonReadTwo digitalRead(7)

float rpm = 0; //average between the two motors
float rpmA = 0; //rpm for motors
float rpmB = 0; //rpm for motors
static volatile int16_t countA = 0;
static volatile int16_t countB = 0;
int PWM = 180; //range 0-255

//PID variables
float rpmDesired = 0;
float error = 0;

//critical gain (2.3) is the kp threshold starts to oscillate unstable 

//KP = critical gain * 0.6
float KP = 1.38;

//KI = 2 * KP / Period
float KI = 0.25;

//KD= 0.125 * KP * Period
float KD = 0.05;


float previous_error = 0;
float integralError = 0;

double timer = 0.0;

void setup() {

  Serial.begin(9600);
  pinMode(ENCODERA, INPUT_PULLUP);
  pinMode(ENCODERB, INPUT_PULLUP);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  //When pin 2 and 3 fall from high to low trigger interrupt routine ISRA and ISRB
  attachInterrupt(digitalPinToInterrupt(ENCODERA), ISRA, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODERB), ISRB, FALLING);

  forward();
  delay(1000);
  rpmCalc();
  rpmDesired = rpm;

}

void loop() {

  
  /*//When button one pressed increase speed
  if(buttonReadOne == LOW){
    rpmDesired = min(rpmDesired * 1.05, 200);
  }

  //when button two pressed decrease speed
  if(buttonReadTwo == LOW){
    rpmDesired = max(rpmDesired * 0.95, 0);
  }*/

  while(timer <= 1000){
    forward();
    rpmCalc();
    PID();
    timer = millis();
  }
  
  while(timer <=1500){
    leftTurn();
    timer = millis();
  }

  while(timer <=3000){
    forward();
    timer = millis();
  }
  /*
  while(timer <=3500){
    rightTurn();
    rpmCalc();
    PID();
    timer = millis();
  }

  while(timer <=5000){
    forward();
    rpmCalc();
    PID();
    timer = millis();
  }*/
  

  stopRobot();
  while(1){}

  

}

void rpmCalc(){
  countA = 0;
  countB = 0;
  delay(100);
  rpmA = 3.125 * countA;
  rpmB = 3.125 * countB;
  rpm = (rpmA + rpmB) / 2;
}

void ISRA(){
  countA++;
}

void ISRB(){
  countB++;
}

void PID(){
  previous_error = error;
  error = rpmDesired - rpm;
  integralError = integralError + error;

  PWM = PWM + KP + error + KI + integralError * 0.1 + KD * (error-previous_error) / 0.1;
  
}

void forward(){
  //Set speed
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, PWM * .9);

  digitalWrite(AIN1, HIGH); //Spin motor A
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH); //Spin motor B
  digitalWrite(BIN2, LOW);
}

void reverse(){
  //Set speed
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, PWM);

  digitalWrite(AIN2, HIGH); //Spin motor A
  digitalWrite(AIN1, LOW);

  digitalWrite(BIN2, HIGH); //Spin motor B
  digitalWrite(BIN1, LOW);
}

void rightTurn(){
  //Set speed
  analogWrite(PWM_A, (PWM * .5));
  analogWrite(PWM_B, PWM);

  digitalWrite(AIN1, HIGH); //Spin motor A
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH); //Spin motor B
  digitalWrite(BIN2, LOW);
}

void leftTurn(){
  //Set speed
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, (PWM * .75));

  digitalWrite(AIN1, HIGH); //Spin motor A
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN2, HIGH); //Spin motor B
  digitalWrite(BIN1, LOW);
}

void stopRobot(){
  //stop motors
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN2, LOW); 
  digitalWrite(BIN1, LOW);
}
