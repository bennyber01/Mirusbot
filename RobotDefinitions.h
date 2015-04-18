#ifndef ROBOT_DEFINITIONS_H
#define ROBOT_DEFINITIONS_H

#include "Vector2D.h"

// 1cm = 35deg : for mmx.runDegrees
#define WHEEL_RADIUS    1.6370222718023520250513758518316
#define WHEELS_DISTANCE 1

#pragma pack(push, 1) // exact fit - no padding

struct WheelsLocation
{
    WheelsLocation() { memset(this, 0, sizeof(WheelsLocation)); }
    Vector2D leftWheelLoc;
    Vector2D rightWheelLoc;
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
