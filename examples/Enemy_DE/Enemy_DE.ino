/*
=====================================
Die Servo Motoren und die Abstands
Sensoren von den Sumoroboter ansetzen
=====================================
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
===============================================================================
Wenn der Gegner zusehen ist, dann ihm vom Ring schieben
TIP: wenn die Sensoren in der aktuellen Position, versuche den Gegner zu finden
VERSUCHE: recherMotor(VORWAERTS, LANGSAM) und linkerMotor(RUECKWAERTS, LANGSAM)
stattdessem LANGSAM kann man auch, MAX_SPEED oder 0 bis 100 Prozent benutzen)
===============================================================================
*/
void loop()
{
	if (GEGNER_VORNE) vorwaerts();    /* wenn der Gegner vorne steht, gehe vorwaerts */
	else if (GEGNER_LINKS) links();   /* wenn der Gegner links steht, gehe links */
	else if (GEGNER_RECHTS) rechts(); /* wenn der Gegner rechts steht, gehe rechts */
	else stop();                      /* wenn kein Gegner in der zusehen ist, stoppen */
}
