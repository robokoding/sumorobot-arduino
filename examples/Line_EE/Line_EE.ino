/*
==============================================
Sumoroboti servode ja valgusandurite juhtimine
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
======================================================
proovime soita nii, et sumorobt ei lahkuks sumoringist
VIHJE: saab ka kasutada ALL_KESKMINE andurit
PROOVI: if ( ALL_KESKMINE ) tagasi();
======================================================
*/
void loop()
{
	if (JOON_PAREM) vasakule();      // kui joon on paremal, mine vasakule
	else if (JOON_VASAK) paremale(); // kui joon on vasakul, mine paremale
	else edasi();                    // muuljuhul mine otse
}
