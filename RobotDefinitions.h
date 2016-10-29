#ifndef ROBOT_DEFINITIONS_H
#define ROBOT_DEFINITIONS_H

#include "Vector2D.h"

// Inorder to compute the radius of the wheel.
// First move the robot X cm using mmx.runTachometer
// in the MotorsModule::GoDistance_cm method and play with
// TACHOS_IN_CM parameter that is located in MotorsModule.h.
// After that R = 180 / (PI * TACHOS_IN_CM)

// In order to compute the distance between the wheels use
// void MotorsModule::Rotate_deg(int deg, bool rotateRight) method.
// Play with TACHOS_IN_DEG parameter that is located in MotorsModule.h
// and make the robot rotatte to th ewanted angle.
// Then D = (180.0 * TACHOS_IN_DEG) / (TACHOS_IN_CM * PI) = TACHOS_IN_DEG * R

//// 1cm = 35deg : for mmx.runDegrees
//#define WHEEL_RADIUS    1.6370222718023520250513758518316
//#define WHEELS_DISTANCE 22.91831181

#define WHEEL_RADIUS    4.7351883895109356096527400672814    // cm  4.71
#define WHEELS_DISTANCE 20.413923279224922406058479401169    // cm

#pragma pack(push, 1) // exact fit - no padding

struct WheelsLocation
{
    WheelsLocation() { memset(this, 0, sizeof(WheelsLocation)); }
    Vector2D leftWheelLoc;
    Vector2D rightWheelLoc;
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
