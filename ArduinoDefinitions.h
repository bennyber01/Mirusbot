#ifndef ARDUINO_DEFINITIONS_H
#define ARDUINO_DEFINITIONS_H

#include <Arduino.h>

// PWM pins: 3, 5, 6, 9, 10, 11

// I2C_SDA  A4
// I2C_SCL  A5

// Interrupt Pins: 2, 3

// sensors pins
#define FRONT_LEFT_DISTANCE_SENSOR_PIN      A0      // GP2Y0A21YK0F
#define FRONT_CENTER_DISTANCE_SENSOR_PIN    A1      // GP2Y0A21YK0F
#define FRONT_RIGHT_DISTANCE_SENSOR_PIN     A2      // GP2Y0A21YK0F
#define FRONT_LL_BUMPER_PIN                 3
#define FRONT_L_BUMPER_PIN                  7
#define FRONT_C_BUMPER_PIN                  6
#define FRONT_R_BUMPER_PIN                  5
#define FRONT_RR_BUMPER_PIN                 4
#define REAR_L_BUMPER_PIN                   12
#define REAR_R_BUMPER_PIN                   13
#define MPU6050_GYROSCOPE_INTERUPT_PIN      2       // interupt num 0

// display pins
#define DISPLAY_SCREEN_0_PIN                11
#define DISPLAY_SCREEN_1_PIN                10
#define DISPLAY_SCREEN_2_PIN                9
#define DISPLAY_SCREEN_3_PIN                8

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
