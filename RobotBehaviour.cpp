#include "cerebellum.h"
#include "Matrix2x2.h"
#include "MathMethods.h"

RobotBehaviour::RobotBehaviour()
{
    robotWeelsLocation.rightWheelLoc.Set(WHEELS_DISTANCE / 2.0,  0);
    robotWeelsLocation.leftWheelLoc.Set(-robotWeelsLocation.rightWheelLoc.x, 0);

    isGoHome = false;

    actionQueue.Push(AT__GO_FORWARD, 20);
    actionQueue.Push(AT__ROTATE_IN_PLACE_RIGHT, 90);
    actionQueue.Push(AT__GO_FORWARD, 20);
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
        else if (!isGoHome)
        {
            GoHome();
            isGoHome = true;
        }
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

void RobotBehaviour::GoHome()
{
    int ang_deg = (int) ComputeRotationInPlaceAngleToCoord(robotWeelsLocation, Vector2D(0, 0));

    Vector2D pos = (robotWeelsLocation.leftWheelLoc + robotWeelsLocation.rightWheelLoc) * 0.5;
    int dist_cm = (int) ComputeDistance(pos, Vector2D(0, 0));

    if (ang_deg >= 0.0)
        actionQueue.Push(AT__ROTATE_IN_PLACE_RIGHT, ang_deg);
    else
        actionQueue.Push(AT__ROTATE_IN_PLACE_LEFT, -ang_deg);
    actionQueue.Push(AT__GO_FORWARD, dist_cm);
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
