#define PWM1 35
#define AIN1 9
#define AIN2 10

void setup() {
  // set up the pins
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  setMotorDirection(LOW,LOW);
  setMotorSpeed(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  testDirectional();
  */
  testPWM();   
}

void setMotorDirection(int in1, int in2){
  digitalWrite(AIN1, in1);
  digitalWrite(AIN2, in2);
  Serial.print("Direction of the motor changed: ");
  Serial.print(in1);
  Serial.print(" ");
  Serial.println(in2); 
}

void setMotorSpeed(int sp){
  analogWrite(PWM1, sp);
  Serial.print("Speed of the motor changed: ");
  Serial.println(sp);
}

void testDirectional(){
  setMotorSpeed(125);
  setMotorDirection(LOW,HIGH);
  delay(2000);
  setMotorSpeed(125);
  setMotorDirection(HIGH,LOW);
  delay(2000);
  setMotorSpeed(255);
  setMotorDirection(LOW,HIGH);
  delay(2000);
}

void testPWM(){
  setMotorDirection(LOW,HIGH);
  for (int i=0;i<=250;i=i+10){
    setMotorSpeed(i);
    delay(500);
  }
}

