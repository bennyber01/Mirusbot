#include "CameraModule.h"

#define maestroSerial Serial3

CameraModule::CameraModule() : maestro(maestroSerial)
{
    azim = elev = 0;
}

CameraModule::~CameraModule()
{
    //dtor
}

void CameraModule::Init()
{
    maestroSerial.begin(9600);
}

void CameraModule::Update()
{

}

void CameraModule::ResetAngles()
{
    SetAzim(0);
    SetElev(0);
}

/* setTarget takes the channel number you want to control, and
   the target position in units of 1/4 microseconds. A typical
   RC hobby servo responds to pulses between 1 ms (4000) and 2
   ms (8000). */

// 6000 = 1500 us
// 7000 = 1750 us
// 5000 = 1250 us

void CameraModule::SetAzim(int val)
{
    azim = val;
    int ms = map(azim, -90, 90, 4000, 8000);
    maestro.setTarget(0, ms);
}
void CameraModule::SetElev(int val)
{
    elev = val;
    int ms = map(elev, -90, 90, 4000, 8000);
    maestro.setTarget(1, ms);
}
