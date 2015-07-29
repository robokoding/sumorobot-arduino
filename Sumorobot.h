#ifndef SUMOROBOT_H_
#define SUMOROBOT_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Servo.h"

/* configuration */
/* movement */
#define SLOW 10         // 10% of speed
#define FORWARD 0       // forward direction
#define BACKWARD 1      // backward direction
#define SECOND 1000     // one second
#define MIDPOINT 94     // servo midpoint, brake
#define MAX_SPEED 100   // 100% of speed
#define MAX_BACKWARD 0  // max backward speed
#define MAX_FORWARD 180 // max forward speed
/* pins */
#define LEFT_MOTOR 5
#define RIGHT_MOTOR 6
#define LINE_SENSOR_LEFT A4
#define LINE_SENSOR_FRONT A3
#define LINE_SENSOR_RIGHT A2
#define ENEMY_SENSOR_LEFT A1
#define ENEMY_SENSOR_RIGHT A0
/* version info */
#define SUMOROBOT_VERSION "0.1"
/* calibration */
#define ENEMY_DISTANCE 200
#define LINE_INTENSITY 600

typedef enum {LEFT, RIGHT, FRONT} dir_t;

class Sumorobot {
    public:
        void reset();
        /* English version */
        void stop();
        void left();
        void right();
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
        int onJoon(dir_t dir) { return isLine(dir); }
        int onPiir(dir_t dir) { return isLine(dir); }
        int onVastane(dir_t dir) { return isEnemy(dir); }
        int onVaenlane(dir_t dir) { return isEnemy(dir); }
        /* German version */
        void links() { left(); }
        void rechts() { right(); }
        void vorwaerts() { forward(); }
        void rueckwaerts() { backward(); }
        int istLinie(dir_t dir) { return isLine(dir); }
        int istGrenze(dir_t dir) { return isLine(dir); }
        int istFeind(dir_t dir) { return isEnemy(dir); }
        int istGegner(dir_t dir) { return isEnemy(dir); }
    private:
        void start();
        /* sumorobot object instance */
        Sumorobot& self() { return *this; }
        int getSpeed(uint8_t, uint8_t, uint8_t);
        /* motors */
        Servo leftServo;
        Servo rightServo;
};

#endif /* SUMOROBOT_H_ */