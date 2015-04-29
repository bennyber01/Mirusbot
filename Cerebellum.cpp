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
    //Serial.begin(115200);
}

void Cerebellum::Update()
{
    // update data from peripherals
    motors.Update();
    sensors.Update();

    MotorsTicks motorsTicks;
    motors.GetMotorsTicks(motorsTicks);

    //if (motorsTicks.LMotorTick > 0 || motorsTicks.RMotorTick > 0)
    //{
    //    Serial.print(motorsTicks.LMotorTick);
    //    Serial.print(", ");
    //    Serial.println(motorsTicks.RMotorTick);
    //    Serial.println("");
    //}

    robotWeelsLocation = computeNewLocation(robotWeelsLocation, motorsTicks);

    MotorsSpeed motorsSpeed;
    motors.GetMotorsSpeed(motorsSpeed);

    // set relevent paramt to disp.
    disp.Print(motorsTicks);
    disp.Print(motorsSpeed);
    disp.Print(sensors.GetFrontSensorsData());
    disp.Print(sensors.GetBumpersData());
    disp.Print(robotWeelsLocation);
    disp.Print(motors.GetBatteryVoltage());

    UpdateRobotBehaviour();

    // refresh screen
    disp.Update();

    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(2);
}
