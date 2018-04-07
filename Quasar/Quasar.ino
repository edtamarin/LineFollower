#include <TeensyThreads.h>

// DEFINES
#define PWM1 35
#define AIN1 9
#define AIN2 10

String data = "";
int calThreadID = 0;

// function definitions
void setMotorDirection(int in1, int in2);
void setMotorSpeed(int sp);
void calThread();
void testThread();
String HC_Command(String cmd="");

void setup() {
  //set up bluetooth comms
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial.println("Configuring HC-06 chip...");
  Serial.println(HC_Command("AT"));
  Serial.println(HC_Command("AT+VERSION"));
  Serial.println(HC_Command("AT+NAMEquasar"));
  Serial.println(HC_Command("AT+PIN1567"));
  Serial.println("Setup complete!");
  // set up motor control
  pinMode(PWM1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  setMotorDirection(HIGH,HIGH);
  setMotorSpeed(0);
}

void loop() {
  // check for command from control module
  data = HC_Command();
  if (data != ""){
    Serial.println("Data: " + data);
  }
  if (data.equals("CLBR")){
    Serial.println("Command received: CALIBRATE");
    threads.addThread(calThread);
  }else if (data.equals("TEST")){
    Serial.println("Command received: TEST");
    threads.addThread(testThread);
  }
  data = "";
}

String HC_Command(String cmd){
  String command = "";
  if (cmd != ""){
  Serial4.print(cmd);
  delay(1000);
  }
  while (Serial4.available()>=4){ // While there is more to be read, keep reading.
    for(int i=0;i<4;i++){
      command += (char)Serial4.read();
    }
  }
  return command;
}

void setMotorDirection(int in1, int in2){
  digitalWrite(AIN1, in1);
  digitalWrite(AIN2, in2);
  Serial.print("Direction of the motor set to: ");
  Serial.print(in1);
  Serial.print(" ");
  Serial.println(in2); 
}

void setMotorSpeed(int sp){
  analogWrite(PWM1, sp);
  Serial.print("Speed of the motor set to: ");
  Serial.println(sp);
}
// THREADS
void calThread(){
  Serial.println("Calibration thread started");
  for (int count = 0; count<10; count++){
    Serial.print("Doing work, batch ");
    Serial.print(count);
    Serial.println();
    delay(1000);
  }
}

void testThread(){
  Serial.println("Testing thread started");
  setMotorDirection(HIGH,LOW);
  setMotorSpeed(255);
  Serial.println("Going forwards at max speed");
  delay(3000);
  setMotorDirection(LOW,HIGH);
  setMotorSpeed(255);
  Serial.println("Going backwards at max speed");
  delay(3000);
  setMotorDirection(HIGH,HIGH);
  setMotorSpeed(0);
  Serial.println("Motor test complete.");
}

