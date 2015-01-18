/*
==================================
Controlling Sumorobts servo motors
==================================
*/

/* including necessary libraries */
#include <Servo.h>
#include <Sumorobot.h>

void setup()
{
	/* starting the servo motors */
	start();
}

/*
===========================================================================================================
Make the robot go 1 second forward and backward xD
HINT: sometimes you want to control the wheels separately, use leftMotor(dir, speed) rightMotor(dir, speed)
TRY: leftMotor(FORWARD, 55) or rightMotor(BACKWARD, MAX_SPEED) or leftMotor(FORWARD, SLOW), instead of
SLOW and MAX_SPEED, 0 to 100 can be used
===========================================================================================================
*/
void loop()
{
	forward();     /* give command to drive forward */
	delay(SECOND); /* go forward for 1 second */
	backward();    /* give command to drive backward */
	delay(SECOND); /* go backward for 1 second */
}
