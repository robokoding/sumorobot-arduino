#include "Sumorobot.h"

/* command processor */
CmdProcessor cmdProcessor;

/* Pointer to the bootloader memory location */
void* bl = (void *) 0x3c00;

Sumorobot::Sumorobot() {
    this->mainState = POWERED_UP;
    this->lastLedChange = millis();
}

/* init motors function */
void Sumorobot::setup() {
    /* set up the status LED */
    pinMode(STATUS_LED, OUTPUT);

    /* initialize the motors */
    this->leftServo.attach(LEFT_MOTOR);
    this->rightServo.attach(RIGHT_MOTOR);

    /* set up the proximity sensor pins */
    pinMode(FRONT_LEFT_SENSOR, INPUT_PULLUP);
    pinMode(FRONT_RIGHT_SENSOR, INPUT_PULLUP);
}

void Sumorobot::setup(Stream &s) {
    this->setup();
    /* set up the command processor */
    cmdProcessor.setup(s, self());
    /* set up the ready pin to communicate with the WiFi module */
    pinMode(WIFI_READY, INPUT); //nReady
    this->initHwVersion();
}

void Sumorobot::initHwVersion(){
    if (EEPROM.read(0) == MAGIC_BYTE_1 && EEPROM.read(1) == MAGIC_BYTE_2) {
        // We've previously written something valid to the EEPROM
        this->hwVersion.major = EEPROM.read(2);
        this->hwVersion.minor = EEPROM.read(3);
    } else {
        this->hwVersion.major = 0;
        this->hwVersion.minor = 0;
    }
}

void Sumorobot::setHwVersion(char &version) {
    char v[4];
    char i;
    char v_ptr = 0;
    char *ptr = &version;
    for(i = 0; i < 9; i++){
        if(ptr[i] >= 0x30 && ptr[i] <= 0x39){
            v[v_ptr++] = ptr[i];
        }
        if(ptr[i] == '.'){
              v[v_ptr++] = '\0';
              break;
        }
    }
    this->hwVersion.major = atoi(v);
    v_ptr = 0;
    for(i = i; i < 9; i++){
        if(ptr[i] >= 0x30 && ptr[i] <= 0x39){
            v[v_ptr++] = ptr[i];
        }
        if(ptr[i] == '\0'){
            v[v_ptr++] = '\0';
            break;
        }
    }
    v[v_ptr] = '\0';
    this->hwVersion.minor = atoi(v);
    EEPROM.write(0, MAGIC_BYTE_1);
    EEPROM.write(1, MAGIC_BYTE_2);
    EEPROM.write(2, this->hwVersion.major);
    EEPROM.write(3, this->hwVersion.minor);
}

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

/* to stop */
void Sumorobot::stop() {
    this->leftServo.write(MIDPOINT);
    this->rightServo.write(MIDPOINT);
}

/* to go forward */
void Sumorobot::forward() {
    this->leftServo.write(getSpeed(LEFT_MOTOR, FORWARD, MAX_SPEED));
    this->rightServo.write(getSpeed(RIGHT_MOTOR, FORWARD, MAX_SPEED));
}

/* to go backward */
void Sumorobot::backward() {
    this->leftServo.write(getSpeed(LEFT_MOTOR, BACKWARD, MAX_SPEED));
    this->rightServo.write(getSpeed(RIGHT_MOTOR, BACKWARD, MAX_SPEED));
}

/* to go right while driving forward */
void Sumorobot::right() {
    this->leftServo.write(getSpeed(LEFT_MOTOR, FORWARD, MAX_SPEED));
    this->rightServo.write(getSpeed(RIGHT_MOTOR, BACKWARD, MAX_SPEED));
}

/* to go left while driving forward */
void Sumorobot::left() {
    this->rightServo.write(getSpeed(RIGHT_MOTOR, FORWARD, MAX_SPEED));
    this->leftServo.write(getSpeed(LEFT_MOTOR, BACKWARD, MAX_SPEED));
}

void Sumorobot::reset() {
    /* give the response message time to get out */
    delay(100);
    goto *bl;
}

void Sumorobot::beep(int duration) {
  tone(SPEAKER_PIN, NOTE_C4, duration);
}

void Sumorobot::checkState() {
    if (!digitalRead(WIFI_READY)) {
        this->mainState = CONNECTED;
    } else {
        this->mainState = POWERED_UP;
    }
}

void Sumorobot::ledHandler() {
    this->checkState();
    switch (this->mainState) {
        case POWERED_UP:
            if(millis() - this->lastLedChange > 250) {
                this->lastLedChange = millis();
                digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
            }
            break;
        case CONNECTED:
            digitalWrite(STATUS_LED, HIGH);
            break;
    }
}

void Sumorobot::process() {
    this->ledHandler();
    cmdProcessor.process();
}