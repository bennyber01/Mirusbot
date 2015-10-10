#ifndef IMUSENSOR_H
#define IMUSENSOR_H

#include "CommunicationDefinitions.h"
#include "Kalman.h"

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
    int azim;           // Calculated angle using a Kalman filter
    int elev;           // Calculated angle using a Kalman filter
    int roll;           // Calculated angle using a Kalman filter

    double rawAzim;     // Angle calculate using the gyro only
    double rawElev;     // Angle calculate using the gyro only
    double rawRoll;     // Angle calculate using the gyro only
    Kalman kalmanAzim;  // Create the Kalman instances
    Kalman kalmanElev;
    Kalman kalmanRoll;
    uint32_t timer;     // last data read

    bool isReset;
    int azimOffset;
    int elevOffset;
    int rollOffset;
};

#endif // IMUSENSOR_H
