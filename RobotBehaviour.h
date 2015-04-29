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
    EventQueue eventQueue;               // holds main events
    CommandQueue commandQueue;           // hold each event substages for execution
    WheelsLocation robotWeelsLocation;

    void HandleEvent(const EventEntry & entry);

    bool isGoHome;
    bool isLookStraight;
    void LookStraight();

    void GoToLocation(double x, double y);
};

#endif
