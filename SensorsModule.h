#ifndef SENSORS_MODULE_H
#define SENSORS_MODULE_H

#include "CommunicationDefinitions.h"
#include "DistanceSensorFilter.h"

class SensorsModule : public ArduinoModule
{
public:
    SensorsModule();
    ~SensorsModule();

    void Init();
    void Update();

    FrontSensorsData GetFrontSensorsData();
    BumpersData GetBumpersData();

private:
    FrontSensorsData frontSensorsData;
    BumpersData bumpersData;

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
