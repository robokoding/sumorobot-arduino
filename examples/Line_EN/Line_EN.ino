/*
==============================================
Controlling Sumorobts servos and light sensors
==============================================
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
===============================================
try to avoid driving out of the sumoring
HINT: the BOTTOM_MIDDLE sensor can also be used
EXAMPLE: if ( BOTTOM_MIDDLE ) backward();
===============================================
*/
void loop()
{
	if (LINE_RIGHT) left();      /* when the line is on the right, we drive left */
	else if (LINE_LEFT) right(); /* when the line is on the left, we drive right */
	else forward();              /* otherwise we go forward */
}
