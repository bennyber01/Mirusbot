#ifndef ARDUINO_DEFINITIONS_H
#define ARDUINO_DEFINITIONS_H

#include <Arduino.h>

// PWM pins: 3, 5, 6, 9, 10, 11

// I2C_SDA  A4
// I2C_SCL  A5

// Interrupt Pins: 2, 3

// sensors pins
#define FRONT_LEFT_DISTANCE_SENSOR_PIN      A0      // GP2Y0A21YK0F
#define FRONT_CENTER_DISTANCE_SENSOR_PIN    A1      // GP2D12
#define FRONT_RIGHT_DISTANCE_SENSOR_PIN     A2      // GP2Y0A21YK0F
#define L_BUMPER_PIN                        7
#define C_BUMPER_PIN                        8
#define R_BUMPER_PIN                        9

// display pins
#define DISPLAY_NEXT_SCREEN_PIN             4

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
