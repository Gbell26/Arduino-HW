#define PWM_A 46 // left motor
#define PWM_B 44 // Right Motor
#define AIN1 32
#define AIN2 34
#define BIN1 30
#define BIN2 36
#define ENCODERA 2 //left encoder
#define ENCODERB 3 //right encoder

float rpm = 0; //average between the two motors
float rpmA = 0; //rpm for motors
float rpmB = 0; //rpm for motors
static volatile int16_t countA = 0;
static volatile int16_t countB = 0;
int PWM = 128; //range 0-255

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

}

void loop() {

  PWM = 0;

  for(int i = 0; i <255; i+=5){
    PWM = i;
    forward();
    delay(1000);
    rpmCalc();
    Serial.print(PWM);
    Serial.print(", ");
    Serial.print(rpmA);
    Serial.print(", ");
    Serial.print(rpmB);
    Serial.print(", ");
    Serial.println(rpm);
    
  }

  stopRobot();
  while(1){};
  

}

void rpmCalc(){
  countA = 0;
  countB = 0;
  delay(100);
  rpmA = 18.75 * countA;
  rpmB = 18.75 * countB;
  rpm = (rpmA + rpmB) / 2;
}

void ISRA(){
  countA++;
}

void ISRB(){
  countB++;
}

void forward(){
  //Set speed
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, PWM);

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
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, PWM);

  digitalWrite(AIN2, HIGH); //Spin motor A
  digitalWrite(AIN1, LOW);

  digitalWrite(BIN1, HIGH); //Spin motor B
  digitalWrite(BIN2, LOW);
}

void leftTurn(){
  //Set speed
  analogWrite(PWM_A, PWM);
  analogWrite(PWM_B, PWM);

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