#ifndef COMPUTE_LOCATION_H
#define COMPUTE_LOCATION_H

#include "CommunicationDefinitions.h"
#include "RobotDefinitions.h"

WheelsLocation computeNewLocation(const WheelsLocation & oldLocation, const MotorsTicks & motorsTicks);

#endif
