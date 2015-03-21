#ifndef ROBOT_DEFINITIONS_H
#define ROBOT_DEFINITIONS_H

#include "Vector2D.h"

#define WHEEL_RADIUS    7

#pragma pack(push, 1) // exact fit - no padding

struct WheelsLocation
{
    WheelsLocation() { memset(this, 0, sizeof(WheelsLocation)); }
    Vector2D leftWheelLoc;
    Vector2D rightWheelLoc;
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
