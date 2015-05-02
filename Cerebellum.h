#ifndef CEREBELLUM_H
#define CEREBELLUM_H

#include <Arduino.h>
#include "CommunicationDefinitions.h"
#include "DisplayModule.h"
#include "MotorsModule.h"
#include "SensorsModule.h"
#include "RobotDefinitions.h"
#include "RobotBehaviour.h"

class Cerebellum : public ArduinoModule, public RobotBehaviour
{
public:
    Cerebellum();
    ~Cerebellum();

    void Init();
    void Update();

private:
    DisplayModule disp;
    MotorsModule motors;
    SensorsModule sensors;

    void UpdateRobotBehaviour();
    void Test1();
    void Test2();

    void HandleCommand(const CommandEntry & entry);
};

#endif
