/*
==============================================
Sumoroboti servode ja kaugusandurite juhtimine
==============================================
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
=======================================================================================
Proovime vastasele otsa liikuda, et ta ringilt lahkuma sundida
VIHJE: proovi vastane leida, kui andurid teda hetkel olevas positsioonis ei suuda leida
PROOVI: paremMootor(EDASI, AEGLANE) and vasakMootor(TAGASI, AEGLANE) keerlemiseks
AEGLANE asemel saab kasutada, MAX_KIIRUS ning 0 kuni 100
=======================================================================================
*/
void loop()
{
	if (VASTANE_EES) edasi();           /* kui vastane on otse ees, liigume edasi */
	else if (VASTANE_VASAK) vasakule(); /* kui vastane on vasakul, liigume vasakule */
	else if (VASTANE_PAREM) paremale(); /* kui vastane on paremal, liigume paremale */
	else stopp();                       /* kui vastane pole anduritele leitav */
}
