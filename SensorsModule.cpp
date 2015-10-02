#include "SensorsModule.h"

#define UPDATE_TIME_DELTA_FOR_IR_DIASTANCE_SENSORS 10

inline double ConvertAnalogValueToCM_SharpSensor_GP2Y0A21(int val)
{
//    double volts = double(val) * 0.0048828125;      // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
//    double distance = 2076.0 / (val - 11.0);

//    double distance = -(3.078*pow(volts,5))+(29.645*pow(volts,4))-(110.68*pow(volts,3))+(201.94*pow(volts,2))-(186.84*pow(volts,1))+81.524;

//    return distance;
    if (val > 600)                             // lower boundary: 4 cm (3 cm means under the boundary)
    {
        return (3);
    }
    else if (val < 80 )                        //upper boundary: 36 cm (returning 37 means over the boundary)
    {
        return (37);
    }
    else
    {
        return (1 / (0.0002391473 * val - 0.0100251467));
    }
}

inline double ConvertAnalogValueToCM_SharpSensor_GP2D12(int val)
{
    double volts = double(val);// * 0.0048828125;      // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    double distance = (6787.0 / (volts - 3.0)) - 4.0;
    return distance;
}

SensorsModule::SensorsModule()
{
    frontSensorsData.LSensorDist = 0.0f;
    frontSensorsData.CSensorDist = 0.0f;
    frontSensorsData.RSensorDist = 0.0f;
    bumpersData.FLLBumper = 0;
    bumpersData.FLBumper  = 0;
    bumpersData.FCBumper  = 0;
    bumpersData.FRBumper  = 0;
    bumpersData.FRRBumper = 0;
    bumpersData.RLBumper  = 0;
    bumpersData.RRBumper  = 0;

    lastUpdateTime_SensorL = 0;
    lastUpdateTime_SensorC = 0;
    lastUpdateTime_SensorR = 0;
}

SensorsModule::~SensorsModule()
{

}

void SensorsModule::Init()
{
    //imuSensor.Init();

    // no need to init alanog pins for input
    pinMode(FRONT_LL_BUMPER_PIN, INPUT);
    pinMode(FRONT_L_BUMPER_PIN,  INPUT);
    pinMode(FRONT_C_BUMPER_PIN,  INPUT);
    pinMode(FRONT_R_BUMPER_PIN,  INPUT);
    pinMode(FRONT_RR_BUMPER_PIN, INPUT);
    pinMode(REAR_L_BUMPER_PIN,   INPUT);
    pinMode(REAR_R_BUMPER_PIN,   INPUT);
}

void SensorsModule::Update()
{
    //imuSensor.Update();

    bumpersData.FLLBumper = !digitalRead(FRONT_LL_BUMPER_PIN);
    //delay(2);
    bumpersData.FLBumper = digitalRead(FRONT_L_BUMPER_PIN);
    //delay(2);
    UpdateFrontLeftDistanceSensorValue();
    //delay(2);
    bumpersData.FCBumper = digitalRead(FRONT_C_BUMPER_PIN);
    //delay(2);
    UpdateFrontCenterDistanceSensorValue();
    //delay(2);
    bumpersData.FRBumper = digitalRead(FRONT_R_BUMPER_PIN);
    //delay(2);
    bumpersData.FRRBumper = !digitalRead(FRONT_RR_BUMPER_PIN);
    //delay(2);
    UpdateFrontRightDistanceSensorValue();
    //delay(2);
    bumpersData.RLBumper = digitalRead(REAR_L_BUMPER_PIN);
    //delay(2);
    bumpersData.RRBumper = digitalRead(REAR_R_BUMPER_PIN);
    //delay(2);
}

void SensorsModule::UpdateFrontLeftDistanceSensorValue()
{
    unsigned long time_millisec = millis();
    if (lastUpdateTime_SensorL < time_millisec - UPDATE_TIME_DELTA_FOR_IR_DIASTANCE_SENSORS)
    {
        int val = analogRead(FRONT_LEFT_DISTANCE_SENSOR_PIN);    // read the input pin
        int filteredVal = frontLeftDistanceSensorFilter.Filter(val);
        frontSensorsData.LSensorDist = ConvertAnalogValueToCM_SharpSensor_GP2Y0A21(filteredVal);
        lastUpdateTime_SensorL = time_millisec;
    }
}

void SensorsModule::UpdateFrontCenterDistanceSensorValue()
{
    unsigned long time_millisec = millis();
    if (lastUpdateTime_SensorC < time_millisec - UPDATE_TIME_DELTA_FOR_IR_DIASTANCE_SENSORS)
    {
        int val = analogRead(FRONT_CENTER_DISTANCE_SENSOR_PIN);    // read the input pin
        int filteredVal = frontCenterDistanceSensorFilter.Filter(val);
        frontSensorsData.CSensorDist = ConvertAnalogValueToCM_SharpSensor_GP2Y0A21(filteredVal);
        lastUpdateTime_SensorC = time_millisec;
    }
}

void SensorsModule::UpdateFrontRightDistanceSensorValue()
{
    unsigned long time_millisec = millis();
    if (lastUpdateTime_SensorR < time_millisec - UPDATE_TIME_DELTA_FOR_IR_DIASTANCE_SENSORS)
    {
        int val = analogRead(FRONT_RIGHT_DISTANCE_SENSOR_PIN);    // read the input pin
        int filteredVal = frontRightDistanceSensorFilter.Filter(val);
        frontSensorsData.RSensorDist = ConvertAnalogValueToCM_SharpSensor_GP2Y0A21(filteredVal);
        lastUpdateTime_SensorR = time_millisec;
    }
}

FrontSensorsData SensorsModule::GetFrontSensorsData()
{
    return frontSensorsData;
}

BumpersData SensorsModule::GetBumpersData()
{
    return bumpersData;
}
