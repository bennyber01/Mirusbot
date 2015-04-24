#include "cerebellum.h"
#include "Matrix2x2.h"

RobotBehaviour::RobotBehaviour()
{
    robotWeelsLocation.rightWheelLoc.Set(WHEELS_DISTANCE / 2.0,  0);
    robotWeelsLocation.leftWheelLoc.Set(-robotWeelsLocation.rightWheelLoc.x, 0);

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
    if (isHandlingEvent)
    {
        isHandlingEvent = motors.IsHandlingEvent();
        delay(2);
    }
    else
    {
        int halfs = 10;

        //MotorsSpeed motorsSpeed;
        //motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 70;
        //motors.SetMotorsSpeed(motorsSpeed);
//        motors.GoDistance_cm(halfs * 2520);
        motors.GoDistance_cm(20);
        isHandlingEvent = true;
    }
}

//void Cerebellum::UpdateRobotBehaviour()
//{
//    BumpersData bumpersData = sensors.GetBumpersData();
//
//    bool isHitSonthing = bumpersData.FLLBumper ||
//                         bumpersData.FLBumper  ||
//                         bumpersData.FCBumper  ||
//                         bumpersData.FRBumper  ||
//                         bumpersData.FRRBumper ||
//                         bumpersData.RRBumper  ||
//                         bumpersData.RLBumper;
//
//    if (isHitSonthing)
//    {
//        motors.StopAllMotors();
//        return;
//    }
//
//    FrontSensorsData sensorsData = sensors.GetFrontSensorsData();
//
//    bool isCloseToSomething = sensorsData.LSensorDist < 10.0 ||
//                              sensorsData.CSensorDist < 10.0 ||
//                              sensorsData.RSensorDist < 10.0;
//    if (isCloseToSomething)
//    {
//        MotorsSpeed motorsSpeed;
//        motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 0;
//        motors.SetMotorsSpeed(motorsSpeed);
//    }
//    else
//    {
//        MotorsSpeed motorsSpeed;
//        motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 70;
//        motors.SetMotorsSpeed(motorsSpeed);
//    }
//}
