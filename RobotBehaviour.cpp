#include "cerebellum.h"
#include "Matrix2x2.h"

RobotBehaviour::RobotBehaviour()
{
    isHandlingEvent = false;
}

RobotBehaviour::~RobotBehaviour()
{

}

//    DisplayModule disp;
//    MotorsModule motors;
//    SensorsModule sensors;
//    WheelsLocation robotWeelsLocation;
void Cerebellum::UpdateRobotBehaviour()
{
    BumpersData bumpersData = sensors.GetBumpersData();

    bool isHitSonthing = bumpersData.FLLBumper ||
                         bumpersData.FLBumper  ||
                         bumpersData.FCBumper  ||
                         bumpersData.FRBumper  ||
                         bumpersData.FRRBumper ||
                         bumpersData.RRBumper  ||
                         bumpersData.RLBumper;

    if (isHitSonthing)
    {
        motors.StopAllMotors();
        return;
    }

    FrontSensorsData sensorsData = sensors.GetFrontSensorsData();

    bool isCloseToSomething = sensorsData.LSensorDist < 10.0 ||
                              sensorsData.CSensorDist < 10.0 ||
                              sensorsData.RSensorDist < 10.0;
    if (isCloseToSomething)
    {
        MotorsSpeed motorsSpeed;
        motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 0;
        motors.SetMotorsSpeed(motorsSpeed);
    }
    else
    {
        MotorsSpeed motorsSpeed;
        motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 70;
        motors.SetMotorsSpeed(motorsSpeed);
    }
}
