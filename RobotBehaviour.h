#ifndef ROBOT_BEHAVIOUR_H
#define ROBOT_BEHAVIOUR_H

#include "RobotDefinitions.h"

class RobotBehaviour
{
public:
    RobotBehaviour();
    ~RobotBehaviour();

protected:
    bool isHandlingEvent;

    WheelsLocation robotWeelsLocation;
};

#endif
