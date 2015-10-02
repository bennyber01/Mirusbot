#ifndef IMUSENSOR_H
#define IMUSENSOR_H

#include "CommunicationDefinitions.h"
#include "I2Cdev/I2Cdev.h"

#include "MPU6050/MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050/MPU6050.h"

class IMUSensor : public ArduinoModule
{
public:
    IMUSensor();
    ~IMUSensor();

    void Init();
    void Update();

    int GetAzim() { return azim; }
    int GetElev() { return elev; }
    int GetRoll() { return roll; }

private:
    double azim;
    double elev;
    double roll;
};

#endif // IMUSENSOR_H
