#ifndef ARDUINO_DEFINITIONS_H
#define ARDUINO_DEFINITIONS_H

#include <Arduino.h>

// PWM pins: 2 to 13 and 44 to 46.

// Interrupt Pins: 2, 3, 18, 19, 20, 21

// sensors pins
#define FRONT_LEFT_DISTANCE_SENSOR_PIN      A0      // GP2Y0A21YK0F
#define FRONT_CENTER_DISTANCE_SENSOR_PIN    A1      // GP2Y0A21YK0F
#define FRONT_RIGHT_DISTANCE_SENSOR_PIN     A2      // GP2Y0A21YK0F
#define FRONT_LL_BUMPER_PIN                 30
#define FRONT_L_BUMPER_PIN                  27
#define FRONT_C_BUMPER_PIN                  28
#define FRONT_R_BUMPER_PIN                  29
#define FRONT_RR_BUMPER_PIN                 31
#define REAR_L_BUMPER_PIN                   12
#define REAR_R_BUMPER_PIN                   13
#define MPU6050_GYROSCOPE_INTERUPT_PIN      2       // interupt num 0

// display pins
#define DISPLAY_SCREEN_TX                   16
#define DISPLAY_SCREEN_RX                   17
#define CAMERA_SERVO_AZIM                   5
#define CAMERA_SERVO_ELEV                   6

#define I2C_ADDRESS 0x09

class ArduinoModule
{
public:
    virtual ~ArduinoModule() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
};
inline ArduinoModule::~ArduinoModule(){}
#endif
