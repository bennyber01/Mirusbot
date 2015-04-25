#ifndef ROBOT_BEHAVIOUR_H
#define ROBOT_BEHAVIOUR_H

#include "RobotDefinitions.h"
#include "ActionQueue.h"

class RobotBehaviour
{
public:
    RobotBehaviour();
    ~RobotBehaviour();

protected:
    ActionQueue actionQueue;
    WheelsLocation robotWeelsLocation;
};

#endif
