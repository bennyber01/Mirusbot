#ifndef MOTORS_MODULE_H
#define MOTORS_MODULE_H

#include "CommunicationDefinitions.h"
#include <NXTI2CDevice-master/NXTMMX.h>

#define MOTOR_L MMX_Motor_1
#define MOTOR_R MMX_Motor_2

class MotorsModule : public ArduinoModule
{
public:
    MotorsModule();
    ~MotorsModule();

    void Init();
    void Update();

    void Reset();

    void StopAllMotors();

    void SetMotorsSpeed(const MotorsSpeed & newSpeeds);
    MotorsSpeed GetMotorsSpeed();

    MotorsTicks GetMotorsTicks();

private:
    MotorsSpeed motorsSpeed;
    MotorsTicks motorsTicks;

    NXTMMX mmx;
};

#endif
