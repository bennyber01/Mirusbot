#ifndef SENSORS_MODULE_H
#define SENSORS_MODULE_H

#include "CommunicationDefinitions.h"
#include "DistanceSensorFilter.h"
//#include "IMUSensor.h"

class SensorsModule : public ArduinoModule
{
public:
    SensorsModule();
    ~SensorsModule();

    void Init();
    void Update();

    FrontSensorsData GetFrontSensorsData();
    BumpersData GetBumpersData();

    int GetAzim() { return 0/*imuSensor.GetAzim()*/; }
    void ResetAzim() {}

private:
    FrontSensorsData frontSensorsData;
    BumpersData bumpersData;
    //IMUSensor imuSensor;

    DistanceSensorFilter frontLeftDistanceSensorFilter;
    DistanceSensorFilter frontCenterDistanceSensorFilter;
    DistanceSensorFilter frontRightDistanceSensorFilter;

    void UpdateFrontLeftDistanceSensorValue();
    void UpdateFrontCenterDistanceSensorValue();
    void UpdateFrontRightDistanceSensorValue();

    unsigned long lastUpdateTime_SensorL;
    unsigned long lastUpdateTime_SensorC;
    unsigned long lastUpdateTime_SensorR;
};

#endif
