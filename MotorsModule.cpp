#include "MotorsModule.h"

MotorsModule::MotorsModule()
{
    ticks.LMotorTick = 0;
    ticks.RMotorTick = 0;
    isHandlingEvent = false;
    isUsePID = false;
    ResetPIDVars();
}

MotorsModule::~MotorsModule()
{
    Reset();
}

void MotorsModule::Reset()
{
    mmx.reset();                // resets the encoder positions to zero
    delay(5);
    mmx.setSpeed(MOTOR_L, 0);
    delay(5);
    mmx.setSpeed(MOTOR_R, 0);
    delay(5);
    mmx.resetEncoder(MOTOR_L);
    delay(5);
    mmx.resetEncoder(MOTOR_R);
    delay(5);
    ticks.LMotorTick = 0;
    ticks.RMotorTick = 0;
}

void MotorsModule::Init()
{
    Reset();
}

void MotorsModule::Update()
{
    if (isUsePID)
    {
        if (pid_currentMotorsSpeed.LMotorSpeed < pid_wantedMotorsSpeed.LMotorSpeed)
        {
            UCHAR update = min(10, (pid_wantedMotorsSpeed.LMotorSpeed - pid_currentMotorsSpeed.LMotorSpeed));
            pid_currentMotorsSpeed.LMotorSpeed += update;
        }

        if (pid_currentMotorsSpeed.RMotorSpeed < pid_wantedMotorsSpeed.RMotorSpeed)
        {
            UCHAR update = min(10, (pid_wantedMotorsSpeed.RMotorSpeed - pid_currentMotorsSpeed.RMotorSpeed));
            pid_currentMotorsSpeed.RMotorSpeed += update;
        }

        UpdateMotorsSpeed();
    }
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
    int newLSpeed = constrain(newSpeeds.LMotorSpeed, -100, 100);
    int newRSpeed = constrain(newSpeeds.RMotorSpeed, -100, 100);

//    mmx.setSpeed(MOTOR_L, newLSpeed);           // this method doesn't move the robot. It only sets it's speed value.
//    mmx.setSpeed(MOTOR_R, newRSpeed);           // this method doesn't move the robot. It only sets it's speed value.

    if (newSpeeds.LMotorSpeed < 0)
        mmx.runUnlimited(MOTOR_L, MMX_Direction_Reverse,-newLSpeed);
    else
        mmx.runUnlimited(MOTOR_L, MMX_Direction_Forward, newLSpeed);

    if (newSpeeds.RMotorSpeed < 0)
        mmx.runUnlimited(MOTOR_R, MMX_Direction_Reverse,-newRSpeed);
    else
        mmx.runUnlimited(MOTOR_R, MMX_Direction_Forward, newRSpeed);
}

void MotorsModule::StopAllMotors()
{
    //mmx.setSpeed(uint8_t which_motor, int speed);

    mmx.stop(MMX_Motor_Both, MMX_Next_Action_BrakeHold);

    pid_wantedMotorsSpeed.LMotorSpeed  = pid_wantedMotorsSpeed.RMotorSpeed  = 0;
    pid_currentMotorsSpeed.LMotorSpeed = pid_currentMotorsSpeed.RMotorSpeed = 0;
    isHandlingEvent = false;
}

void MotorsModule::GetMotorsSpeed(MotorsSpeed & motorsSpeed)
{
    motorsSpeed.LMotorSpeed = mmx.getSpeed(MOTOR_L);
    motorsSpeed.RMotorSpeed = mmx.getSpeed(MOTOR_R);
}

void MotorsModule::GetMotorsTicks(MotorsTicks & motorsTicks)
{
    int lt = mmx.getEncoderPosition(MOTOR_L);
    int rt = mmx.getEncoderPosition(MOTOR_R);

    motorsTicks.LMotorTick = lt - ticks.LMotorTick;
    motorsTicks.RMotorTick = rt - ticks.RMotorTick;

    if (!isUsePID && IsTachoDone())
    {
        mmx.resetEncoder(MOTOR_L);
        delay(5);
        mmx.resetEncoder(MOTOR_R);
        delay(5);
        ticks.LMotorTick = 0;
        ticks.RMotorTick = 0;
        isHandlingEvent = false;
    }
    else
    {
        if (motorsTicks.LMotorTick > 35 || motorsTicks.RMotorTick > 35)
        {
            ticks.LMotorTick = lt;
            ticks.RMotorTick = rt;
        }
        else
        {
            motorsTicks.LMotorTick = 0;
            motorsTicks.RMotorTick = 0;
        }
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

void MotorsModule::RotateInPlace_deg(int deg, bool rotateRight)
{
    isHandlingEvent = true;

    // 180 deg = 2520 tachos
    long tachos = (long) ((double)deg) * 2524.0 / 360.0;

    uint8_t l_motor_dir = MMX_Direction_Reverse;
    uint8_t r_motor_dir = MMX_Direction_Forward;
    if (rotateRight)
    {
        l_motor_dir = MMX_Direction_Forward;
        r_motor_dir = MMX_Direction_Reverse;
    }

//    mmx.startMotorsInSync();
    mmx.runTachometer(
                      MOTOR_L,
                      l_motor_dir,
                      MMX_Speed_Medium,
                      tachos,
                      MMX_Move_Relative,
                      //MMX_Completion_Wait_For,
                      MMX_Completion_Dont_Wait,
                      MMX_Next_Action_Float
                      //MMX_Next_Action_BrakeHold
                     );

    mmx.runTachometer(
                      MOTOR_R,
                      r_motor_dir,
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

void MotorsModule::DriveStraight(UCHAR speed)
{
    isHandlingEvent = true;

    mmx.resetEncoder(MOTOR_L);
    delay(5);
    mmx.resetEncoder(MOTOR_R);
    delay(5);
    ticks.LMotorTick = 0;
    ticks.RMotorTick = 0;

    ResetPIDVars();

    mmx.startMotorsInSync();

    pid_wantedMotorsSpeed.LMotorSpeed = pid_wantedMotorsSpeed.RMotorSpeed = speed;

    pid_currentMotorsSpeed.LMotorSpeed = pid_currentMotorsSpeed.RMotorSpeed = min(5, speed);
    SetMotorsSpeed(pid_currentMotorsSpeed);

    isUsePID = true;
}
