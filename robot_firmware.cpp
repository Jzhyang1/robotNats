#define LEFT_MOTOR_HI 7
#define LEFT_MOTOR_LO 6

#define RIGHT_MOTOR_HI 4
#define RIGHT_MOTOR_LO 5

#define SPEED_CONTROL 9

#include "firmware.h"

void init_robot() {
    pinMode(LEFT_MOTOR_HI, OUTPUT);
    pinMode(LEFT_MOTOR_LO, OUTPUT);
    pinMode(RIGHT_MOTOR_HI, OUTPUT);
    pinMode(RIGHT_MOTOR_LO, OUTPUT);
}
void power_left_motor(int speed) {
    if(speed > 0) {digitalWrite(LEFT_MOTOR_HI, HIGH); digitalWrite(LEFT_MOTOR_LO, LOW);}
    else {digitalWrite(LEFT_MOTOR_HI, LOW); digitalWrite(LEFT_MOTOR_LO, HIGH);}
    analogWrite(SPEED_CONTROL, speed);
}
void power_right_motor(int speed) {
    if(speed > 0) {digitalWrite(RIGHT_MOTOR_HI, HIGH); digitalWrite(RIGHT_MOTOR_LO, LOW);}
    else {digitalWrite(RIGHT_MOTOR_HI, LOW); digitalWrite(RIGHT_MOTOR_LO, HIGH);}
    analogWrite(SPEED_CONTROL, speed);
}
void unpower_left_motor(){
    digitalWrite(LEFT_MOTOR_HI, LOW); digitalWrite(LEFT_MOTOR_HI, LOW);
}
void unpower_right_motor(){
    digitalWrite(RIGHT_MOTOR_HI, LOW); digitalWrite(RIGHT_MOTOR_LO, LOW);
}
void unpower_both_motors(){
    digitalWrite(LEFT_MOTOR_HI, LOW); digitalWrite(LEFT_MOTOR_HI, LOW);
    digitalWrite(RIGHT_MOTOR_HI, LOW); digitalWrite(RIGHT_MOTOR_LO, LOW);
    analogWrite(SPEED_CONTROL, 0);
}