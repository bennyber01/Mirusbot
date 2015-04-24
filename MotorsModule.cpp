#include "MotorsModule.h"

MotorsModule::MotorsModule()
{
    ticks.LMotorTick = 0;
    ticks.RMotorTick = 0;
    isHandlingEvent = false;
}

MotorsModule::~MotorsModule()
{
    Reset();
}

void MotorsModule::Reset()
{
    mmx.reset();                // resets the encoder positions to zero
    mmx.setSpeed(MOTOR_L, 0);
    mmx.setSpeed(MOTOR_R, 0);
    mmx.resetEncoder(MOTOR_L);
    mmx.resetEncoder(MOTOR_R);
    ticks.LMotorTick = 0;
    ticks.RMotorTick = 0;
}

void MotorsModule::Init()
{
    Reset();
}

void MotorsModule::Update()
{

}

//    mmx.runRotations(MMX_Motor_1,
//                     MMX_Direction_Forward,
//                     MMX_Speed_Medium,
//                     rotations,
//                     MMX_Completion_Wait_For,
//                     MMX_Next_Action_BrakeHold);
//
//	mmx.runDegrees(MMX_Motor_Both,
//                   MMX_Direction_Forward,
//                   MMX_Speed_Full,
//                   degrees,
//                   MMX_Completion_Wait_For,
//                   MMX_Next_Action_Float);
//
//	mmx.runSeconds(MMX_Motor_Both,
//                   MMX_Direction_Reverse,
//                   MMX_Speed_Slow,
//                   seconds,
//                   MMX_Completion_Wait_For,
//                   MMX_Next_Action_Float);
//
//	mmx.runUnlimited(MMX_Motor_1,
//                     MMX_Direction_Forward,
//                     MMX_Speed_Slow);

// Motors seepd can be any value between 0 and 100.
void MotorsModule::SetMotorsSpeed(const MotorsSpeed & newSpeeds)
{
    //mmx.setSpeed(uint8_t which_motor, int speed);

    if (newSpeeds.LMotorSpeed < 0)
        mmx.runUnlimited(MOTOR_L, MMX_Direction_Reverse,-newSpeeds.LMotorSpeed);
    else
        mmx.runUnlimited(MOTOR_L, MMX_Direction_Forward, newSpeeds.LMotorSpeed);

    if (newSpeeds.RMotorSpeed < 0)
        mmx.runUnlimited(MOTOR_R, MMX_Direction_Reverse,-newSpeeds.RMotorSpeed);
    else
        mmx.runUnlimited(MOTOR_R, MMX_Direction_Forward, newSpeeds.RMotorSpeed);
}

void MotorsModule::StopAllMotors()
{
    //mmx.setSpeed(uint8_t which_motor, int speed);

    mmx.stop(MMX_Motor_Both, MMX_Next_Action_BrakeHold);

//    mmx.runDegrees(MMX_Motor_Both,
//                   MMX_Direction_Forward,
//                   0,
//                   0,
//                   MMX_Completion_Wait_For,
//                   MMX_Next_Action_BrakeHold);
}

void MotorsModule::GetMotorsSpeed(MotorsSpeed & motorsSpeed)
{
    motorsSpeed.LMotorSpeed = mmx.getSpeed(MOTOR_L);
    motorsSpeed.RMotorSpeed = mmx.getSpeed(MOTOR_R);
}

void MotorsModule::GetMotorsTicks(MotorsTicks & motorsTicks)
{
    if (IsTachoDone())
    {
        motorsTicks.LMotorTick = 0;
        motorsTicks.RMotorTick = 0;
        mmx.resetEncoder(MOTOR_L);
        mmx.resetEncoder(MOTOR_R);
        ticks.LMotorTick = 0;
        ticks.RMotorTick = 0;
    }
    else
    {
        int lt = mmx.getEncoderPosition(MOTOR_L);
        int rt = mmx.getEncoderPosition(MOTOR_R);

        motorsTicks.LMotorTick = lt - ticks.LMotorTick;
        motorsTicks.RMotorTick = rt - ticks.RMotorTick;
        ticks.LMotorTick = lt;
        ticks.RMotorTick = rt;
    }
}

bool MotorsModule::IsTachoDone()
{
    bool isDone = mmx.isTachoDone(MMX_Motor_Both);
    return isDone;
}

int MotorsModule::GetBatteryVoltage()
{
    return (int) mmx.getBatteryVoltage(); // retrun voltage in mv
}

void MotorsModule::GoDistance_cm(int cm)
{
    isHandlingEvent = true;

    // 1cm = 35 deg
    long degs = cm * 35;

//    mmx.startMotorsInSync();
    mmx.runTachometer(
                      MMX_Motor_Both,
                      //MMX_Motor_2,
                      MMX_Direction_Forward,
                      MMX_Speed_Medium,
                      degs,
                      MMX_Move_Relative,
                      //MMX_Completion_Wait_For,
                      MMX_Completion_Dont_Wait,
                      MMX_Next_Action_Float
                      //MMX_Next_Action_BrakeHold
                     );
}

void MotorsModule::Rotate_deg(int deg, bool rotateRight)
{
    isHandlingEvent = true;

    // 180 deg = 2520 tachos
    long tachos = (long) ((double)deg) * 2524.0 / 180.0;

    uint8_t motor = (rotateRight) ? MOTOR_L : MOTOR_R;

//    mmx.startMotorsInSync();
    mmx.runTachometer(
                      motor,
                      MMX_Direction_Forward,
                      MMX_Speed_Medium,
                      tachos,
                      MMX_Move_Relative,
                      //MMX_Completion_Wait_For,
                      MMX_Completion_Dont_Wait,
                      MMX_Next_Action_Float
                      //MMX_Next_Action_BrakeHold
                     );
}

bool MotorsModule::IsHandlingEvent()
{
    return isHandlingEvent;
}
