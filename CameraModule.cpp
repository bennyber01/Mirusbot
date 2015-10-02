#include "CameraModule.h"

CameraModule::CameraModule()
{
    azim = elev = 0;
}

CameraModule::~CameraModule()
{
    //dtor
}

void CameraModule::Init()
{
    azim_servo.attach(CAMERA_SERVO_AZIM);
    elev_servo.attach(CAMERA_SERVO_ELEV);
}

void CameraModule::Update()
{

}

void CameraModule::ResetAngles()
{
    SetAzim(0);
    SetElev(0);
}

void CameraModule::SetAzim(int val)
{
    azim = val;
    azim_servo.write(azim + 90);
}
void CameraModule::SetElev(int val)
{
    elev = val;
    elev_servo.write(elev + 90);
}
