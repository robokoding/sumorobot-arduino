/*
=================================================
Controlling Sumorobts servos and distance sensors
=================================================
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
===========================================================================
Try to push out the enemy without attention to the sumoring 
HINT: try to search for the enemy, when he is not visible to the sensors
TRY: rightMotor(FORWARD, SLOW) and leftMotor(BACKWARD, SLOW) to spin,
instead of SLOW, MAX_SPEED or 0 to 100 percent can be used
===========================================================================
*/
void loop()
{
	if (ENEMY_FRONT) forward();    /* when enemy is in front of us, we go forward */
	else if (ENEMY_LEFT) left();   /* when the enemy is on the left side, we go left */
	else if (ENEMY_RIGHT) right(); /* when the enemy is on the right side, we go right */
	else stop();                   /* when there is no enemy */
}
