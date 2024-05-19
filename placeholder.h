#pragma once

#ifndef ARDUINO_IDE

#define delay(t) 

#include <string>
#include <vector>
#define String std::string
#define Vector std::vector
#define isDigit isdigit
#define millis() 1

#define pinMode(digital_pin, mode) 
#define OUTPUT
#define INPUT
#define digitalWrite(pin, power)
#define analogWrite(pin, power)
#define HIGH
#define LOW



#ifdef IMU
#define SH2_GAME_ROTATION_VECTOR 

class Adafruit_BNO08x {
public:
  Adafruit_BNO08x(int8_t reset_pin = -1);
  ~Adafruit_BNO08x();

  bool begin_I2C();

  void hardwareReset(void);
  bool wasReset(void);

  bool enableReport();
  bool getSensorEvent(sh2_SensorValue_t *value);
};

/**
 * @brief Rotation Vector with Accuracy
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RotationVectorWAcc {
    float i;  /**< @brief Quaternion component i */
    float j;  /**< @brief Quaternion component j */
    float k;  /**< @brief Quaternion component k */
    float real;  /**< @brief Quaternion component, real */
    float accuracy;  /**< @brief Accuracy estimate [radians] */
} sh2_RotationVectorWAcc_t;

/**
 * @brief Rotation Vector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RotationVector {
    float i;  /**< @brief Quaternion component i */
    float j;  /**< @brief Quaternion component j */
    float k;  /**< @brief Quaternion component k */
    float real;  /**< @brief Quaternion component real */
} sh2_RotationVector_t;

/**
 * @brief Gyro Integrated Rotation Vector
 *
 * See SH-2 Reference Manual for details.
 */
typedef struct sh2_GyroIntegratedRV {
    float i;        /**< @brief Quaternion component i */
    float j;        /**< @brief Quaternion component j */
    float k;        /**< @brief Quaternion component k */
    float real;     /**< @brief Quaternion component real */
    float angVelX;  /**< @brief Angular velocity about x [rad/s] */
    float angVelY;  /**< @brief Angular velocity about y [rad/s] */
    float angVelZ;  /**< @brief Angular velocity about z [rad/s] */
} sh2_GyroIntegratedRV_t;


typedef struct sh2_SensorValue {
    
    /** Which sensor produced this event. */
    uint8_t sensorId;

    /** @brief 8-bit unsigned integer used to track reports.
     *
     * The sequence number increments once for each report sent.  Gaps
     * in the sequence numbers indicate missing or dropped reports.
     */
    uint8_t sequence;

    /* Status of a sensor
     *   0 - Unreliable
     *   1 - Accuracy low
     *   2 - Accuracy medium
     *   3 - Accuracy high
     */
    uint8_t status; /**< @brief bits 7-5: reserved, 4-2: exponent delay, 1-0: Accuracy */

    uint64_t timestamp;  /**< [uS] */

    uint32_t delay; /**< @brief [uS] value is delay * 2^exponent (see status) */

    /** @brief Sensor Data
     *
     * Use the structure based on the value of the sensor
     * field.
     */
    union {
        sh2_RotationVectorWAcc_t rotationVector; 
        sh2_RotationVector_t gameRotationVector; 
        sh2_RotationVectorWAcc_t arvrStabilizedRV;
        sh2_RotationVector_t arvrStabilizedGRV;
        sh2_GyroIntegratedRV_t gyroIntegratedRV;
    } un;
} sh2_SensorValue_t;

#endif




#else

#ifdef IMU
#include <Adafruit_BNO08x.h>
#endif

#endif