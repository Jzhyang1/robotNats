#define ERROR_LED 12
#include "firmware.h"


void init_error() {
    pinMode(ERROR_LED, OUTPUT)
}
void signal_error(){
    digitalWrite(ERROR_LED, HIGH);
}
void clear_error(){
    digitalWrite(ERROR_LED, LOW);
}