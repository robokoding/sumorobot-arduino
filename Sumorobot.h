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

/* directions */
typedef enum {LEFT, RIGHT, FRONT} dir_t;

class Sumorobot {
    public:
        
        void stop();
        void left();
        void right();
        void reset();
        void forward();
        void backward();
        bool isLine(dir_t);
        bool isEnemy(dir_t);
        void delay(long millis) { delay(millis); }
        void wait(long millis) { this->delay(millis); }
        bool isBorder(dir_t dir) { return isLine(dir); }
        bool isOpponent(dir_t dir) { return isEnemy(dir); }
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