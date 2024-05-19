#define IMU
#include "placeholder.h"
#include "firmware.h"
#define BNO08X_RESET -1

#define AWAIT_TRUE(condition) while(condition){signal_error();delay(10);}

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

int init_imu() {
  AWAIT_TRUE (!bno08x.begin_I2C());
  AWAIT_TRUE (! bno08x.enableReport(SH2_GAME_ROTATION_VECTOR));
}

double get_rotation_vector() {
  AWAIT_TRUE (! bno08x.getSensorEvent(&sensorValue));
  //TODO return rotation vector
  sensorValue.un.gameRotationVector;    //return part of this
}