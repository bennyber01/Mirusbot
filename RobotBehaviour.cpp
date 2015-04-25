#include "cerebellum.h"
#include "Matrix2x2.h"

RobotBehaviour::RobotBehaviour()
{
    robotWeelsLocation.rightWheelLoc.Set(WHEELS_DISTANCE / 2.0,  0);
    robotWeelsLocation.leftWheelLoc.Set(-robotWeelsLocation.rightWheelLoc.x, 0);

    actionQueue.Push(AT__GO_FORWARD, 10);
    actionQueue.Push(AT__ROTATE_IN_PLACE_RIGHT, 90);
    actionQueue.Push(AT__GO_FORWARD, 10);
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
    if (motors.IsHandlingEvent())
    {
        //delay(2);
    }
    else
    {
        ActionEntry entry;
        bool isNewEvent = actionQueue.Pop(entry);
        if (isNewEvent)
            HandleEvent(entry);
    }
}

void Cerebellum::HandleEvent(const ActionEntry & entry)
{
    switch (entry.actionType)
    {
    case AT__GO_FORWARD:
        motors.GoDistance_cm(entry.param_int);
        break;

    case AT__GO_BACKWARD:
        motors.GoDistance_cm(-entry.param_int);
        break;

    case AT__ROTATE_RIGHT:
        motors.Rotate_deg(entry.param_int, true);
        break;

    case AT__ROTATE_LEFT:
        motors.Rotate_deg(entry.param_int, false);
        break;

    case AT__ROTATE_IN_PLACE_RIGHT:
        motors.RotateInPlace_deg(entry.param_int, true);
        break;

    case AT__ROTATE_IN_PLACE_LEFT:
        motors.RotateInPlace_deg(entry.param_int, false);
        break;

    case AT__STOP:
    default:
        motors.StopAllMotors();
        break;
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
