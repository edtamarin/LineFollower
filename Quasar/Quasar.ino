#include <TeensyThreads.h>

// Teensy Bluetooth test

String data = "";
int calThreadID = 0;

void calThread();
String HC_Command(String cmd="");

void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial.println("Configuring HC-06 chip...");
  Serial.println(HC_Command("AT"));
  Serial.println(HC_Command("AT+VERSION"));
  Serial.println(HC_Command("AT+NAMEquasar"));
  Serial.println(HC_Command("AT+PIN1567"));
  Serial.println("Setup complete!");
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
      Serial.println(threads.id());
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

void calThread(){
  Serial.println("Calibration thread started");
  for (int count = 0; count<10; count++){
    Serial.print("Doing work, batch ");
    Serial.print(count);
    Serial.println();
    delay(1000);
  }
}

