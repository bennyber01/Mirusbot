#include "cerebellum.h"
#include "robot_location_computation.h"

Cerebellum::Cerebellum()
{

}

Cerebellum::~Cerebellum()
{

}

void Cerebellum::Init()
{
    disp.Init();
    motors.Init();
    sensors.Init();
}

void Cerebellum::Update()
{
    // update data from peripherals
    motors.Update();
    sensors.Update();

    MotorsTicks motorsTicks;
    motors.GetMotorsTicks(motorsTicks);
    robotWeelsLocation = computeNewLocation(robotWeelsLocation, motorsTicks);

    MotorsSpeed motorsSpeed;
    motors.GetMotorsSpeed(motorsSpeed);

    // set relevent paramt to disp.
    disp.Print(motorsTicks);
    disp.Print(motorsSpeed);
    disp.Print(sensors.GetFrontSensorsData());
    disp.Print(sensors.GetBumpersData());
    disp.Print(robotWeelsLocation);

    UpdateRobotBehaviour();

    // refresh screen
    disp.Update();

    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(2);
}
