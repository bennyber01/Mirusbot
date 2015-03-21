#include "MotorsModule.h"

MotorsModule::MotorsModule()
{
    motorsSpeed.LMotorSpeed = 0;
    motorsSpeed.RMotorSpeed = 0;
    motorsTicks.LMotorTick = 0;
    motorsTicks.RMotorTick = 0;
}

MotorsModule::~MotorsModule()
{
    Reset();
}

void MotorsModule::Reset()
{
    motorsSpeed.LMotorSpeed = 0;
    motorsSpeed.RMotorSpeed = 0;
    motorsTicks.LMotorTick  = 0;
    motorsTicks.RMotorTick  = 0;
    mmx.reset();                // resets the encoder positions to zero
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

    motorsSpeed = newSpeeds;
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

MotorsSpeed MotorsModule::GetMotorsSpeed()
{
    motorsSpeed.LMotorSpeed = mmx.getSpeed(MOTOR_L);
    motorsSpeed.RMotorSpeed = mmx.getSpeed(MOTOR_R);
    return motorsSpeed;
}

MotorsTicks MotorsModule::GetMotorsTicks()
{
    motorsTicks.LMotorTick = mmx.getEncoderPosition(MOTOR_L);
    motorsTicks.RMotorTick = mmx.getEncoderPosition(MOTOR_R);
    return motorsTicks;
}
