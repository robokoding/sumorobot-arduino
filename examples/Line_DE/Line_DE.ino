/*
==============================================
Die Lichtsensoren von dem Sumoroboter ansetzen
==============================================
*/

/* die noetigen Bibliotheken hinzufuegen */
#include <Servo.h>
#include <Sumorobot.h>

void setup()
{
	/* die Servo Motore starten */
	start();
}

/*
=================================================================
versuche so zu fahren das der Sumoroboter den Ring nicht verlässt
TIP: man kann auch den Sensor UNTEN_MITTE benutzen
VERSUCHE: if ( UNTEN_MITTE ) rueckwaerts();
=================================================================
*/
void loop()
{
	if (LINIE_RECHTS) links();      /* wenn die Linie rechts liegt, gehe nach links */
	else if (LINIE_LINKS) rechts(); /* wenn die Linie links liegt, gehe nach rechts */
	else vorwaerts();               /* ansonsten gehe vorwaerts */
}
