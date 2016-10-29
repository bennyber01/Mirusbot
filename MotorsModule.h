#ifndef MOTORS_MODULE_H
#define MOTORS_MODULE_H

#include "CommunicationDefinitions.h"
#include <NXTI2CDevice-master/NXTMMX.h>

#define MOTOR_L MMX_Motor_1
#define MOTOR_R MMX_Motor_2

#define ROBOT_NORMAL_SPEED 35
#define TACHOS_IN_CM       12.1                  // 1cm = 35 deg for small wheels
#define TACHOS_IN_DEG      (776.0 / 180.0)       // 180 deg = 2520 tachos for small wheel (2524.0 last was used)

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
    void Rotate_deg(int deg, bool rotateRight);
    void RotateInPlace_deg(int deg, bool rotateRight);

    void DriveStraight(UCHAR speed);

    int GetBatteryVoltage();

private:
    NXTMMX mmx;

    MotorsTicks ticks;
    bool isHandlingEvent;

    bool IsTachoDone();

    bool isUsePID;
    int16_t pid_lastErr;
    int16_t pid_sumErrs;
    unsigned long pid_lastCall;
    int pid_adjustLMotor;
    int pid_adjustRMotor;
    int pid_lastLSpeed;
    int pid_lastRSpeed;
    volatile MotorsTicks pid_prevTicks;
    MotorsSpeed pid_wantedMotorsSpeed;
    MotorsSpeed pid_currentMotorsSpeed;
    void ResetPIDVars();
    bool GetTicksSinceLastUpdate( int16_t & lft, int16_t & rht, uint16_t & ms );
    void UpdateMotorsSpeed();
};

#endif
