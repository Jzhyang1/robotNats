#pragma once
#include "placeholder.h"


extern const int MAX_SPEED;
extern const int MIN_SPEED;
extern const int TURN_SPEED;

extern const int KILL_TMILLI;

int left_turn_millis(int amt);
int right_turn_millis(int amt);

int forward_millis(int amt, int s);
int backward_millis(int amt, int s);


void set_path(String path);
void set_target(int tmillis);

void start();
void next_motion();