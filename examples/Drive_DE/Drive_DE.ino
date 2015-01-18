/*
============================================
Die Servo Motore von dem Sumoroboter steuern
============================================
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
==========================================================================================================
lassen wir den Roboter eine Sekunde vorwaerts und rueckwaerts fahren xD
TIP: manchmal will man die Motore separat ansteuern
linkerMotor(richtung, geschwindigkeit) rechterMotor(richtung, geschwindigkeit)
wo die richtung FORWAERTS oder RUECKWAERTS ist und die geschwindigkeit 0 bis 100 ist
VERSUCHE: linkerMotor(FORWAERTS, 55) rechterMotor(RUECKWAERTS, MAX_SPEED) vasakMootor(FORWAERTS, LANGSAM))
==========================================================================================================
*/
void loop()
{
	vorwaerts();    /* die Richtung bestimmen */
	warte(SEKUNDE); /* eine Sekunde ausfuehren */
	rueckwaerts();  /* die Richtung bestimmen */
	warte(SEKUNDE); /* eine Sekunde ausfuehren */
}
