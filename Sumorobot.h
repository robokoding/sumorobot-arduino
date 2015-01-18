#ifndef SUMOROBOT_H_
#define SUMOROBOT_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Servo.h"
#include <EEPROM.h>
#include "CmdProcessor.h"

/* configuration */
/* music */
#define NOTE_C4  262
/* movement */
#define SLOW 10         // 10% of speed
#define FORWARD 0       // forward direction
#define BACKWARD 1      // backward direction
#define SECOND 1000     // one second
#define MIDPOINT 90     // servo midpoint, brake
#define MAX_SPEED 100   // 100% of speed
#define MAX_BACKWARD 0  // max backward speed
#define MAX_FORWARD 180 // max forward speed
/* pins */
#define WIFI_READY 3
#define WIFI_POWER 12
#define LEFT_MOTOR 5
#define RIGHT_MOTOR 6
#define STATUS_LED 13
#define SPEAKER_PIN 9
#define FRONT_RIGHT_SENSOR 0
#define FRONT_LEFT_SENSOR 1
#define LINE_RIGHT_SENSOR 2
#define LINE_MIDDLE_SENSOR 3
#define LINE_LEFT_SENSOR 4
/* version info */
#define MAGIC_BYTE_1 0xF0
#define MAGIC_BYTE_2 0x0D
#define SUMOROBOT_VERSION "0.1"
/* calibration */
#define ENEMY_DISTANCE 150
#define LIGHT_INTENSITY 600
/* for advanced calibration */
#define ENEMY_DISTANCE_LEFT ENEMY_DISTANCE
#define ENEMY_DISTANCE_RIGHT ENEMY_DISTANCE
#define LIGHT_INTENSITY_LEFT LIGHT_INTENSITY
#define LIGHT_INTENSITY_RIGHT LIGHT_INTENSITY
#define LIGHT_INTENSITY_MIDDLE LIGHT_INTENSITY

typedef enum {LEFT, RIGHT, FRONT} dirState_t;
typedef enum {POWERED_UP, CONNECTED} mainState_t;

struct HwVersion {
  byte major;
  byte minor;
};

class Sumorobot {
    public:
        Sumorobot();
        void setup();
        void process();
        void setup(Stream &s);
        void setHwVersion(char&);
        HwVersion hwVersion;
        /* English version */
        void stop();
        void left();
        void right();
        void reset();
        void beep(int);
        void forward();
        void backward();
        /* Estonian version */
        void stopp() { stop(); }
        void edasi() { forward(); }
        void vasakule() { left(); }
        void paremale() { right(); }
        void tagasi() { backward(); }
        /* German version */
        void links() { left(); }
        void rechts() { right(); }
        void vorwaerts() { forward(); }
        void rueckwaerts() { backward(); }
    private:
        void checkState();
        void ledHandler();
        void initHwVersion();
        int getSpeed(uint8_t, uint8_t, uint8_t);
        /* motors */
        Servo leftServo;
        Servo rightServo;
        /* wifi state */
        mainState_t mainState;
        unsigned long lastLedChange;
        /* sumorobot object instance */
        Sumorobot& self() { return *this; }
};

#define READ_LINE(analog, distance) (analogRead(analog) > distance)
#define READ_ENEMY(analog, distance) (analogRead(analog) < distance)

#define ENEMY_LEFT READ_ENEMY(FRONT_LEFT_SENSOR, ENEMY_DISTANCE_LEFT)
#define ENEMY_RIGHT READ_ENEMY(FRONT_RIGHT_SENSOR, ENEMY_DISTANCE_RIGHT)
#define ENEMY_FRONT (ENEMY_LEFT && ENEMY_RIGHT)

#define ENEMY_MIDDLE ENEMY_FRONT
#define OPPONENT_LEFT ENEMY_LEFT
#define OPPONENT_RIGHT ENEMY_RIGHT
#define OPPONENT_FRONT ENEMY_FRONT
#define OPPONENT_MIDDLE ENEMY_FRONT

#define LINE_LEFT READ_LINE(LINE_LEFT_SENSOR, LIGHT_INTENSITY_RIGHT)
#define LINE_RIGHT READ_LINE(LINE_RIGHT_SENSOR, LIGHT_INTENSITY_RIGHT)
#define LINE_MIDDLE READ_LINE(LINE_MIDDLE_SENSOR, LIGHT_INTENSITY_MIDDLE)

#define BOTTOM_LEFT LINE_LEFT
#define LINE_FRONT LINE_MIDDLE
#define BOTTOM_RIGHT LINE_RIGHT
#define BOTTOM_FRONT LINE_MIDDLE
#define BOTTOM_MIDDLE LINE_MIDDLE

#define VASTANE_EES ENEMY_FRONT
#define VASTANE_VASAK ENEMY_LEFT
#define VASTANE_PAREM ENEMY_RIGHT

#define JOON_VASAK LINE_LEFT
#define JOON_PAREM LINE_RIGHT
#define JOON_KESKMINE LINE_MIDDLE

#define GEGNER_LINKS ENEMY_LEFT
#define GEGNER_VORNE ENEMY_FRONT
#define GEGNER_RECHTS ENEMY_RIGHT

#define LINIE_LINKS LINE_LEFT
#define LINIE_RECHTS LINE_RIGHT
#define LINIE_MITTE LINE_MIDDLE

#endif /* SUMOROBOT_H_ */