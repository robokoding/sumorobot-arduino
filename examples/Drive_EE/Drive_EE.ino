/*
====================================
Sumoroboti servo mootorite juhtimine
====================================
*/

/* vajalike teekide lisamine */
#include <Servo.h>
#include <Sumorobot.h>

void setup()
{
	/* servo mootorite kaivitamine */
	start();
}

/*
==========================================================================================
Laseme robotil liikuda sekund edasi ja sekund tagasi xD
VIHJE: vahel tekib vajadus mootoreid juhtida eraldi, selleks kasuta
vasakMootor(suund, kiirus) paremMootor(suund, speed)
kus suund on EDASI voi TAGASI ja kiirus 0 kuni 100
PROOVI: vasakMootor(EDASI, 55) paremMootor(TAGASI, MAX_KIIRUS) vasakMootor(EDASI, AEGLANE)
==========================================================================================
*/
void loop()
{
	edasi();          /* anname suuna, kuhu liikuda */
	viivitus(SEKUND); /* liigume 1 sekund edasi */
	tagasi();         /* anname suuna, kuhu liikuda */
	viivitus(SEKUND); /* liigume 1 sekund tagasi */
}
