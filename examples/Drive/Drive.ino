/*
==================================
Controlling Sumorobts servo motors
==================================
*/

/* including necessary libraries */
#include <Servo.h>
#include <Sumorobot.h>

/* the sumorobot object */
Sumorobot sumorobot;

void setup()
{
	/* the setup function */
}

/*
===========================================================================================================
Make the robot go 1 second forward and backward xD
HINT: the delay is in milliseconds 1000 milliseconds = 1 second
TRY: different timings as delay 100 to 2000
===========================================================================================================
*/
void loop()
{
	sumorobot.forward();     /* give command to drive forward */
	sumorobot.delay(SECOND); /* go forward for 1 second */
	sumorobot.backward();    /* give command to drive backward */
	sumorobot.delay(SECOND); /* go backward for 1 second */
}
