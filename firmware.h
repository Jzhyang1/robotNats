#pragma once
#include "placeholder.h"

void init_robot();
void power_left_motor(int speed);
void power_right_motor(int speed);

void unpower_left_motor();
void unpower_right_motor();
void unpower_both_motors();

void init_error();
void signal_error();
void clear_error();

int init_imu();
double get_rotation_vector();