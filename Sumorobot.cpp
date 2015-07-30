#include "Sumorobot.h"

/* function to calculate the the motor speed given the motor, directory and speed in precentage
 @param motor ( RIGHT_MOTOR or LEFT_MOTOR )
 @param dir ( BACKWARD or FORWARD )
 @param speed_percentage ( 0 to 100 )
 @return int ( 0 for success and 1-3 for error )
 */
int Sumorobot::getSpeed(uint8_t motor, uint8_t dir, uint8_t speed_percentage) {
    /* if precentage out of rage, return error */
    if (speed_percentage < 0 || speed_percentage > 100) return 3;
    /* if the motor is unknown, return error */
    if (motor != RIGHT_MOTOR && motor != LEFT_MOTOR) return 2;
    /* if the we operate with the right wheen, we need to turn the direction, because the motor is flipped */
    if (motor == RIGHT_MOTOR) dir = !dir;
    /* when going forward */
    if (dir == FORWARD) {
        /* the forward speed is MIDPOINT - MAX_FORWARD, for speed calculation we need to move the 0 point */
        return ((speed_percentage / 100.0) * (MAX_FORWARD - MIDPOINT)) + MIDPOINT;
    /* when going backward */
    } else if (dir == BACKWARD) {
        /* the backward speed is MIDPOINT - MAX_BACKWARD, for speed calculation we need to revert the result */
        return abs(((speed_percentage / 100.0) * MIDPOINT) - MIDPOINT);
    /* otherwise */
    } else {
        /* if the direction was not valid, return error */
        return 1;
    }
}

void Sumorobot::start() {
    /* attach the motors when not attached */
    if (this->leftServo.attached() == false) this->leftServo.attach(LEFT_MOTOR);
    if (this->rightServo.attached() == false) this->rightServo.attach(RIGHT_MOTOR);
}

/* to stop */
void Sumorobot::stop() {
    /* stop the motors */
    this->leftServo.write(MIDPOINT);
    this->rightServo.write(MIDPOINT);
    this->delay(200);
    /* detach the motors when attached */
    if (this->leftServo.attached()) this->leftServo.detach();
    if (this->rightServo.attached()) this->rightServo.detach();
}

/* to go forward */
void Sumorobot::forward() {
    /* check if motors are attached */
    this->start();
    this->leftServo.write(getSpeed(LEFT_MOTOR, FORWARD, MAX_SPEED));
    this->rightServo.write(getSpeed(RIGHT_MOTOR, FORWARD, MAX_SPEED));
}

/* to go backward */
void Sumorobot::backward() {
    /* check if motors are attached */
    this->start();
    this->leftServo.write(getSpeed(LEFT_MOTOR, BACKWARD, MAX_SPEED));
    this->rightServo.write(getSpeed(RIGHT_MOTOR, BACKWARD, MAX_SPEED));
}

/* to go right while driving forward */
void Sumorobot::right() {
    /* check if motors are attached */
    this->start();
    this->leftServo.write(getSpeed(LEFT_MOTOR, FORWARD, MAX_SPEED));
    this->rightServo.write(getSpeed(RIGHT_MOTOR, BACKWARD, MAX_SPEED));
}

/* to go left while driving forward */
void Sumorobot::left() {
    /* check if motors are attached */
    this->start();
    this->rightServo.write(getSpeed(RIGHT_MOTOR, FORWARD, MAX_SPEED));
    this->leftServo.write(getSpeed(LEFT_MOTOR, BACKWARD, MAX_SPEED));
}

bool Sumorobot::isEnemy(dir_t direction) {
    switch (direction) {
        case LEFT:
            return analogRead(ENEMY_SENSOR_LEFT) > ENEMY_DISTANCE;
        case RIGHT:
            return analogRead(ENEMY_SENSOR_RIGHT) > ENEMY_DISTANCE;
        case FRONT:
            return (analogRead(ENEMY_SENSOR_LEFT) > ENEMY_DISTANCE) && 
                (analogRead(ENEMY_SENSOR_RIGHT) > ENEMY_DISTANCE);
    }
}

bool Sumorobot::isLine(dir_t direction) {
    switch (direction) {
        case LEFT:
            return analogRead(LINE_SENSOR_LEFT) < LINE_INTENSITY;
        case RIGHT:
            return analogRead(LINE_SENSOR_RIGHT) < LINE_INTENSITY;
        case FRONT:
            return (analogRead(LINE_SENSOR_LEFT) < LINE_INTENSITY) && 
                (analogRead(LINE_SENSOR_RIGHT) < LINE_INTENSITY);
    }
}