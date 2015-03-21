#include "robot_location_computation.h"
#include <math.h>
#include "Matrix2x2.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

double deg_2_rad(double deg) { return deg * M_PI / 180.0; }
double rad_2_deg(double rad) { return rad * 180.0 / M_PI; }

WheelsLocation compute_new_location_no_rotation(const WheelsLocation & oldLocation, double wheel_l_dist, double wheel_r_dist)
{
	Vector2D dir_x = oldLocation.rightWheelLoc - oldLocation.leftWheelLoc;
	dir_x.Normalize();
	Vector2D dir_y(-dir_x.y, dir_x.x);

	// compute final result
	WheelsLocation result;
	result.leftWheelLoc  = oldLocation.leftWheelLoc  + dir_y * wheel_l_dist;
	result.rightWheelLoc = oldLocation.rightWheelLoc + dir_y * wheel_r_dist;

	return result;
}

WheelsLocation compute_new_location_with_roration(const WheelsLocation & oldLocation, double wheel_l_dist, double wheel_r_dist)
{
	double dist_between_wheels  = (oldLocation.rightWheelLoc - oldLocation.leftWheelLoc).Length();

	double alpha_rad = (wheel_l_dist - wheel_r_dist) / dist_between_wheels;

	double r = wheel_r_dist / alpha_rad;

	// compute final result
	Matrix2x2 rotation_matrix(cos(alpha_rad), sin(alpha_rad), -sin(alpha_rad), cos(alpha_rad));
	Vector2D dir_x = oldLocation.rightWheelLoc - oldLocation.leftWheelLoc;
	dir_x.Normalize();
	Vector2D center = oldLocation.rightWheelLoc + dir_x * r;

	WheelsLocation result;
	result.leftWheelLoc  = center + rotation_matrix * (oldLocation.leftWheelLoc - center);
	result.rightWheelLoc = center + rotation_matrix * (oldLocation.rightWheelLoc - center);

	return result;
}

WheelsLocation computeNewLocation(const WheelsLocation & oldLocation, const MotorsTicks & motorsTicks)
{
	double wheel_l_dist = deg_2_rad(motorsTicks.LMotorTick) * WHEEL_RADIUS;
	double wheel_r_dist = deg_2_rad(motorsTicks.RMotorTick) * WHEEL_RADIUS;

	WheelsLocation result;

	if (motorsTicks.LMotorTick == motorsTicks.RMotorTick)
		result = compute_new_location_no_rotation(oldLocation, wheel_l_dist, wheel_r_dist);
	else
		result = compute_new_location_with_roration(oldLocation, wheel_l_dist, wheel_r_dist);

	return result;
}
