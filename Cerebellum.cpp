#include "cerebellum.h"
#include "robot_location_computation.h"

Cerebellum::Cerebellum() : disp(this)
{
    azimMove = elevMove = 0;
    lastCameraAnglesUpdate = 0;
}

Cerebellum::~Cerebellum()
{

}

void Cerebellum::Init()
{
    disp.Init();
    motors.Init();
    sensors.Init();
    cameraModule.Init();
    //Serial.begin(115200);
}

void Cerebellum::Update()
{
    UpdateCamLocation();

    // update data from peripherals
    motors.Update();
    sensors.Update();
    cameraModule.Update();

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
    disp.PrintWandering(isWander);
    disp.PrintCameraAngles(cameraModule.GetAzim(), cameraModule.GetElev());
    disp.PrintAzim(sensors.GetAzim());

    if (isWander)
        UpdateRobotBehaviour();

    // refresh screen
    disp.Update();

    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(2);
}

void Cerebellum::ToggleWander()
{
    isWander = !isWander;
}

void Cerebellum::UpdateCamLocation()
{
    unsigned long time = millis();

    if (lastCameraAnglesUpdate + 50 < time)
    {
        if (azimMove)
            cameraModule.SetAzim(cameraModule.GetAzim() + azimMove);

        if (elevMove)
            cameraModule.SetElev(cameraModule.GetElev() + elevMove);

        lastCameraAnglesUpdate = time;
    }
}

void Cerebellum::CenterCam()
{
    cameraModule.ResetAngles();
}
