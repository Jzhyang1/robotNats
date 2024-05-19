#define MAIN
#include "library.h"


String path = R""""(
    F25R
    FFL
    FFFL
    FFF
)"""";
int target_millis = 60000;


const int MAX_SPEED = 255;
const int MIN_SPEED = 110;
const int TURN_SPEED = 150;

const int KILL_TMILLI = 400;


int left_turn_millis(int amt) {
  return 1000 * (amt/54.2);
}
int right_turn_millis(int amt) {
   return 1000 * (amt/54.2);
}

int forward_millis(int amt, int s){
  return 1000 * (amt * 300.2)/s;
}
int backward_millis(int amt, int s){
  return 1000 * (amt * 300.2)/s;
}


void setup() {
  set_path(path);
  set_target(target_millis);
  start();
}

void loop() {
  next_motion();
}
