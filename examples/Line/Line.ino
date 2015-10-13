/*
==============================================
Controlling Sumorobts servos and light sensors
==============================================
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
	/* the setup function */
}

/*
===================================================
try to avoid driving out of the sumoring
HINT: the LINE FRONT sensor can also be used
EXAMPLE: if ( sumorobot.isLine(FRONT) ) backward();
===================================================
*/
void loop()
{
	if (sumorobot.isLine(RIGHT)) sumorobot.left();      /* when the line is on the right, we drive left */
	else if (sumorobot.isLine(LEFT)) sumorobot.right(); /* when the line is on the left, we drive right */
	else sumorobot.forward();                           /* otherwise we go forward */
}
