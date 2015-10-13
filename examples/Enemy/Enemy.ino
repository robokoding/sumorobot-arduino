/*
=================================================
Controlling Sumorobts servos and distance sensors
=================================================
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
=========================================================================
Try to push out the enemy without attention to the sumoring 
HINT: try to search for the enemy, when he is not visible to the sensors
TRY: rightMotor(FORWARD, SLOW) and leftMotor(BACKWARD, SLOW) to spin,
instead of SLOW, MAX_SPEED or 0 to 100 percent can be used
=========================================================================
*/
void loop()
{
	if (sumorobot.isOpponent(FRONT)) sumorobot.forward();    /* when enemy is in front of us, we go forward */
	else if (sumorobot.isOpponent(LEFT)) sumorobot.left();   /* when the enemy is on the left side, we go left */
	else if (sumorobot.isOpponent(RIGHT)) sumorobot.right(); /* when the enemy is on the right side, we go right */
	else sumorobot.stop();                                   /* when there is no enemy */
}
