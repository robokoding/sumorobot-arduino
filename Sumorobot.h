#ifndef SUMOROBOT_H_
#define SUMOROBOT_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Servo.h"

/* version info */
#define SUMOROBOT_VERSION "0.1"

/* movement definitions */
#define FORWARD 0       // forward direction
#define BACKWARD 1      // backward direction
#define SECOND 1000     // one second
#define MIDPOINT 94     // servo midpoint, brake
#define MAX_SPEED 100   // 100% of speed
#define MAX_BACKWARD 0  // max backward speed
#define MAX_FORWARD 180 // max forward speed

/* sensor calibration */
#define ENEMY_DISTANCE 200
#define LINE_INTENSITY 600

/* pin configuration */
#define LEFT_MOTOR 5
#define RIGHT_MOTOR 6
#define LINE_SENSOR_LEFT A4
#define LINE_SENSOR_FRONT A3
#define LINE_SENSOR_RIGHT A2
#define ENEMY_SENSOR_LEFT A1
#define ENEMY_SENSOR_RIGHT A0

/* sensor directions */
typedef enum {LEFT, RIGHT, FRONT} dir_t;

class Sumorobot {
    public:
        /* constructor function */
        Sumorobot();
        /* function to stop moving */
        void stop();
        /* function to move left */
        void left();
        /* function to move right */
        void right();
        /* function to move forward */
        void forward();
        /* function to move backward */
        void backward();
        /*
            function to detect the line in the specified direction
            @param dir ( LEFT, RIGHT, FRONT )
        */
        bool isLine(dir_t);
        /*
            function to detect the enemy in the specified direction
            @param dir ( LEFT, RIGHT, FRONT )
        */
        bool isEnemy(dir_t);
        /*
            function to leave the sumorobot moving into the last specified direction
            @param millis ( milliseconds 0 to 2147483647 )
        */
        void delay(long millis) { delay(millis); }
        /* see delay above */
        void wait(long millis) { this->delay(millis); }
        /* see isLine above */
        bool isBorder(dir_t dir) { return isLine(dir); }
        /* see isEnemy above */
        bool isOpponent(dir_t dir) { return isEnemy(dir); }
    private:
        /* function to start servo motors */
        void start();
        /* sumorobot object instance */
        Sumorobot& self() { return *this; }
        /*
            function to calculate the the motor speed given the motor, directory and speed in precentage
            @param motor ( RIGHT_MOTOR or LEFT_MOTOR )
            @param dir ( BACKWARD or FORWARD )
            @param speed_percentage ( 0 to 100 )
            @return int ( 0 for success and 1 dir error, 2 motor error, 3 speed error )
        */
        int getSpeed(uint8_t, uint8_t, uint8_t);
        /* the servo motor objects */
        Servo leftServo;
        Servo rightServo;
};

#endif /* SUMOROBOT_H_ */