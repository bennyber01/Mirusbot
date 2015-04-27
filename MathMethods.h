#ifndef MATH_METHODS_H
#define MATH_METHODS_H

#include "Vector2D.h"
#include "math.h"
#include "RobotDefinitions.h"

#pragma pack(push, 1) // exact fit - no padding


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

inline double deg_2_rad(double deg) { return deg * M_PI / 180.0; }
inline double rad_2_deg(double rad) { return rad * 180.0 / M_PI; }

inline double ComputeDistance(const Vector2D & v0, const Vector2D & v1) { return (v0 - v1).Length(); }

inline double ComputeAngle_deg(const Vector2D & from, const Vector2D & to)
{
    double cos_alpha_rad = atan2(from.y, from.x) - atan2(to.y, to.x);
    double cos_alpha_deg = rad_2_deg(cos_alpha_rad);
    return cos_alpha_deg;
}

inline double ComputeRotationInPlaceAngleToCoord(WheelsLocation robotWeelsLocation, const Vector2D & coord)
{
    Vector2D from = robotWeelsLocation.leftWheelLoc - robotWeelsLocation.rightWheelLoc;
    Vector2D pos = (robotWeelsLocation.leftWheelLoc + robotWeelsLocation.rightWheelLoc) * 0.5;
    from.Set(-from.y, from.x);
    Vector2D to = coord - pos;
    return ComputeAngle_deg(from, to);
}

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
