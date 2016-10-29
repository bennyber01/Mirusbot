#include "cerebellum.h"
#include "Matrix2x2.h"
#include "MathMethods.h"

RobotBehaviour::RobotBehaviour()
{
    robotWeelsLocation.rightWheelLoc.Set(WHEELS_DISTANCE / 2.0,  0);
    robotWeelsLocation.leftWheelLoc.Set(-robotWeelsLocation.rightWheelLoc.x, 0);

    isGoHome = false;
    isLookStraight = false;

//    actionQueue.Push(AT__GO_FORWARD, 20);
//    actionQueue.Push(AT__ROTATE_IN_PLACE_RIGHT, 90);
//    //actionQueue.Push(AT__ROTATE_RIGHT, 90);
//    actionQueue.Push(AT__GO_FORWARD, 20);

    eventQueue.Push(ET__GO_TO, 0, 60);
    eventQueue.Push(ET__GO_TO, 40, 20);

  //  commandQueue.Push(CT__ROTATE_RIGHT, 118);
  //  commandQueue.Push(CT__ROTATE_IN_PLACE_RIGHT, 118);
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
    Test1();
    //Test2();
}

void Cerebellum::Test1()
{
    if (motors.IsHandlingEvent())
    {
        delay(2);
    }
    else
    {
        CommandEntry entry;
        bool isNewCommand = commandQueue.Pop(entry);
        if (isNewCommand)
            HandleCommand(entry);
        else
        {
            EventEntry entry;
            bool isNewEvent = eventQueue.Pop(entry);
            if (isNewEvent)
                RobotBehaviour::HandleEvent(entry);
            else if (!isGoHome)
            {
                GoToLocation(0, 0);
                isGoHome = true;
            }
            else if (!isLookStraight)
            {
                LookStraight();
                isLookStraight = true;
            }
        }
    }
}

void Cerebellum::HandleCommand(const CommandEntry & entry)
{
    switch (entry.command)
    {
    case CT__GO_FORWARD:
        motors.GoDistance_cm(entry.param_int);
        break;

    case CT__GO_BACKWARD:
        motors.GoDistance_cm(-entry.param_int);
        break;

    case CT__ROTATE_RIGHT:
        motors.Rotate_deg(entry.param_int, true);
        break;

    case CT__ROTATE_LEFT:
        motors.Rotate_deg(entry.param_int, false);
        break;

    case CT__ROTATE_IN_PLACE_RIGHT:
        motors.RotateInPlace_deg(entry.param_int, true);
        break;

    case CT__ROTATE_IN_PLACE_LEFT:
        motors.RotateInPlace_deg(entry.param_int, false);
        break;

    case CT__STOP:
    default:
        motors.StopAllMotors();
        break;
    }

}

void RobotBehaviour::HandleEvent(const EventEntry & entry)
{
    switch (entry.eventType)
    {
    case ET__GO_TO:
        GoToLocation(entry.param_int0, entry.param_int1);
        break;

    case ET__STOP:
    default:
        commandQueue.Push(CT__STOP);
        break;
    }
}

void RobotBehaviour::GoToLocation(double x, double y)
{
    Vector2D dest(x, y);

    int ang_deg = (int) ComputeRotationInPlaceAngleToCoord(robotWeelsLocation, dest);
    if (ang_deg >= 0.0)
        commandQueue.Push(CT__ROTATE_IN_PLACE_RIGHT, ang_deg);
    else
        commandQueue.Push(CT__ROTATE_IN_PLACE_LEFT, -ang_deg);

    Vector2D pos = (robotWeelsLocation.leftWheelLoc + robotWeelsLocation.rightWheelLoc) * 0.5;
    int dist_cm = (int) ComputeDistance(pos, dest);
    commandQueue.Push(CT__GO_FORWARD, dist_cm);

#ifdef _DEBUG
    if (1)
    {
        Serial.print("pos(");
        Serial.print(pos.x);
        Serial.print(",");
        Serial.print(pos.y);
        Serial.print("), dest(");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print("), ang(");
        Serial.print(ang_deg);
        Serial.println("), dist(");
        Serial.print(dist_cm);
        Serial.println(")");
    }
#endif
}

void RobotBehaviour::LookStraight()
{
    int ang_deg = (int) ComputeRotationInPlaceAngleToLookAtDirection(robotWeelsLocation, Vector2D(0, 1));
    if (ang_deg >= 0.0)
        commandQueue.Push(CT__ROTATE_IN_PLACE_RIGHT, ang_deg);
    else
        commandQueue.Push(CT__ROTATE_IN_PLACE_LEFT, -ang_deg);
}





void Cerebellum::Test2()
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
        motors.StopAllMotors();
        return;
    }

    //MotorsSpeed motorsSpeed;
    //motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 70;
    //motors.SetMotorsSpeed(motorsSpeed);

    if (!motors.IsHandlingEvent())
        motors.DriveStraight(70);
}
