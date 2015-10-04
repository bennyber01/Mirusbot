#ifndef IMUSENSOR_H
#define IMUSENSOR_H

#include "CommunicationDefinitions.h"

// MotionApps 2.0 DMP implementation, built using the MPU-6050EVB evaluation board
#define MPU6050_INCLUDE_DMP_MOTIONAPPS20
#include "MPU6050/MPU6050.h"

class IMUSensor : public ArduinoModule
{
public:
    IMUSensor();
    ~IMUSensor();

    void Init();
    void Update();

    int GetAzim();
    int GetElev();
    int GetRoll();

    void Reset() { isReset = true; }

private:
    int azim;
    int elev;
    int roll;

    bool isReset;
    int azimOffset;
    int elevOffset;
    int rollOffset;
};

#endif // IMUSENSOR_H
