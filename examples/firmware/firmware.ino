#include <Servo.h>
#include <EEPROM.h>
#include <Sumorobot.h>

Sumorobot sumorobot;

void setup(){
  Serial.begin(115200);
  sumorobot.setup(Serial);
}

void loop(){
  sumorobot.process();
}
