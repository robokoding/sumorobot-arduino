/*
===========================================
Processing websocket commands for Sumorobot
===========================================
*/

/* including necessary libraries */
#include <Servo.h>
#include <EEPROM.h>
#include <NewPing.h>
#include <Sumorobot.h>

/* the sumorobot object */
Sumorobot sumorobot;

void setup()
{
    Serial.begin(57600);
    sumorobot.setup(Serial);
}

void loop()
{
    sumorobot.process();
}
