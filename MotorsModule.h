#ifndef MOTORS_MODULE_H
#define MOTORS_MODULE_H

#include "CommunicationDefinitions.h"
#include <NXTI2CDevice-master/NXTMMX.h>

#define MOTOR_R MMX_Motor_1
#define MOTOR_L MMX_Motor_2

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
    void GetMotorsSpeed(MotorsSpeed & motorsSpeed);
    void GetMotorsTicks(MotorsTicks & motorsTicks);

    bool IsHandlingEvent();

    void GoDistance_cm(int cm);

private:
    NXTMMX mmx;

    bool isHandlingEvent;
};

#endif
