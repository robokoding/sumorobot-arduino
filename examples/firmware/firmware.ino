#include <Servo.h>
#include <EEPROM.h>
#include <NewPing.h>
#include <Sumorobot.h>

Sumorobot sumorobot;

void setup(){
    Serial.begin(57600);
    sumorobot.setup(Serial);
}

void loop(){
    sumorobot.process();
}
