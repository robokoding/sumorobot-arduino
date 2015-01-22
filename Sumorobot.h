#ifndef SUMOROBOT_H_
#define SUMOROBOT_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Servo.h"
#include <EEPROM.h>
#include "NewPing.h"
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
#define LINE_SENSOR_LEFT A1
#define LINE_SENSOR_RIGHT A2
#define ENEMY_SENSOR_LEFT 9000
#define ENEMY_SENSOR_RIGHT 2
/* version info */
#define MAGIC_BYTE_1 0xF0
#define MAGIC_BYTE_2 0x0D
#define SUMOROBOT_VERSION "0.1"
/* calibration */
#define ENEMY_DISTANCE 50
#define LINE_INTENSITY 600
/* for advanced calibration */
#define ENEMY_DISTANCE_LEFT ENEMY_DISTANCE
#define ENEMY_DISTANCE_RIGHT ENEMY_DISTANCE
#define LINE_INTENSITY_LEFT LINE_INTENSITY
#define LINE_INTENSITY_RIGHT LINE_INTENSITY

typedef enum {LEFT, RIGHT, FRONT} dir_t;
typedef enum {POWERED_UP, CONNECTED} mainState_t;

struct HwVersion {
    byte major;
    byte minor;
};

class Sumorobot {
    public:
        Sumorobot();
        void setup();
        void reset();
        void process();
        void setup(Stream &s);
        void setHwVersion(char&);
        HwVersion hwVersion;
        /* English version */
        void stop();
        void left();
        void right();
        void beep(int);
        void forward();
        void backward();
        int isLine(dir_t);
        int isEnemy(dir_t);
        int isBorder(dir_t dir) { return isLine(dir); }
        int isOpponent(dir_t dir) { return isEnemy(dir); }
        /* Estonian version */
        void stopp() { stop(); }
        void edasi() { forward(); }
        void vasakule() { left(); }
        void paremale() { right(); }
        void tagasi() { backward(); }
        void piiks(int dur) { beep(dur); }
        int onJoon(dir_t dir) { return isLine(dir); }
        int onPiir(dir_t dir) { return isLine(dir); }
        int onVastane(dir_t dir) { return isEnemy(dir); }
        int onVaenlane(dir_t dir) { return isEnemy(dir); }
        /* German version */
        void links() { left(); }
        void rechts() { right(); }
        void vorwaerts() { forward(); }
        void ton(int dur) { beep(dur); }
        void rueckwaerts() { backward(); }
        int istLinie(dir_t dir) { return isLine(dir); }
        int istGrenze(dir_t dir) { return isLine(dir); }
        int istFeind(dir_t dir) { return isEnemy(dir); }
        int istGegner(dir_t dir) { return isEnemy(dir); }
    private:
        void start();
        void checkState();
        void ledHandler();
        void initHwVersion();
        /* sumorobot object instance */
        Sumorobot& self() { return *this; }
        int getSpeed(uint8_t, uint8_t, uint8_t);
        /* motors */
        Servo leftServo;
        Servo rightServo;
        /* wifi state */
        mainState_t mainState;
        unsigned long lastLedChange;
};

#endif /* SUMOROBOT_H_ */