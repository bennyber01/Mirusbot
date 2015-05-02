#include "MotorsModule.h"

//----------------------------------------
// Config
//----------------------------------------

#define Kp              900L        // 1500L
#define Ki             1800L        // 900L
#define Kd                0L        // 0L
#define SYSTEM_BIAS     -90L        // compensate for lost time between calls of get ticks methods.
#define MAX_ADJUSTMENT    5         // max allowed step size for speed adjustment
#define MAX_SPEED       100         // max allowed speed

void MotorsModule::ResetPIDVars()
{
    pid_lastErr = 0;
    pid_sumErrs = 0;
    pid_lastCall = 0;
    pid_adjustLMotor = 0;
    pid_adjustRMotor = 0;
    pid_lastLSpeed = 0;
    pid_lastRSpeed = 0;
    pid_prevTicks.LMotorTick = 0;
    pid_prevTicks.RMotorTick = 0;
    pid_wantedMotorsSpeed.LMotorSpeed = 0;
    pid_wantedMotorsSpeed.RMotorSpeed = 0;
    pid_currentMotorsSpeed.LMotorSpeed = 0;
    pid_currentMotorsSpeed.RMotorSpeed = 0;
}

bool MotorsModule::GetTicksSinceLastUpdate( int16_t & lft, int16_t & rht, uint16_t & ms )
{
    unsigned long now = millis();
    if (!pid_lastCall)
        pid_lastCall = now;
    unsigned long tdelta_ms = now - pid_lastCall;

    if (tdelta_ms < 200)
    {
        lft = rht = ms = 0;
        return false;
    }

    int currLTicks = mmx.getEncoderPosition(MOTOR_L);
    int currRTicks = mmx.getEncoderPosition(MOTOR_R);

    lft = currLTicks - pid_prevTicks.LMotorTick;
    rht = currRTicks - pid_prevTicks.RMotorTick;
    ms  = tdelta_ms;

    pid_prevTicks.LMotorTick = currLTicks;
    pid_prevTicks.RMotorTick = currRTicks;
    pid_lastCall = now;

    return true;
}

void MotorsModule::UpdateMotorsSpeed()
{
    int16_t lticks, rticks;
    uint16_t ms;

    if (!GetTicksSinceLastUpdate( lticks, rticks, ms))
        return;

    int16_t rdir = rticks < 0 ? -1 : 1;
    int16_t ldir = lticks < 0 ? -1 : 1;

    // make the values positive
    lticks *= ldir;
    rticks *= rdir;

    int16_t bias = (rticks*SYSTEM_BIAS)/10000L;
    int16_t diff = ((lticks - rticks + bias) * 100L) / ms;

    // we want the difference to be 0

    // track the integral
    pid_sumErrs += diff;

    // get the differential
    int32_t delta = (int32_t) (diff - pid_lastErr);

    int16_t P = (int16_t) ((Kp*((int32_t)diff) + Ki*((int32_t)pid_sumErrs) + (Kd*delta))/1000L);

    pid_lastErr = diff;

    // a positive error means the left motor is
    // turning more than the right so adjust
    // each motor accordingly
    int16_t adjust = (P>>1);       // divide the update factor by 2

    pid_adjustLMotor -= adjust*ldir;
    pid_adjustRMotor += adjust*rdir;

    constrain(pid_adjustLMotor, -MAX_ADJUSTMENT, MAX_ADJUSTMENT);
    constrain(pid_adjustRMotor, -MAX_ADJUSTMENT, MAX_ADJUSTMENT);

    // compute new speed
    int lspeed = pid_currentMotorsSpeed.LMotorSpeed + pid_adjustLMotor;
    int rspeed = pid_currentMotorsSpeed.RMotorSpeed + pid_adjustRMotor;

//    if (1)
//    {
//        //Serial.print(pid_time); Serial.print(", ");
//        //Serial.print(ms); Serial.print(", ");
//        //Serial.print(lticks); Serial.print(", ");
//        //Serial.print(rticks); Serial.print(", ");
//        Serial.print(diff); Serial.print(", ");
//        Serial.print(pid_sumErrs); Serial.print(", ");
//        Serial.print(adjustLMotor); Serial.print(", ");
//        Serial.print(adjustRMotor);
//        Serial.println();
//    }
//    else if (1)
//    {
//        Serial.print("DIFF = ");
//        Serial.print(diff);
//        Serial.print(" ERR = ");
//        Serial.print(pid_sumErrs);
//        Serial.print(" ADJ = (");
//        Serial.print(adjustLMotor);
//        Serial.print(", ");
//        Serial.print(adjustRMotor);
//        Serial.println(")");
//    }


    // Put a limit on the total adjustment in case PID gets out of control
    constrain(lspeed, -MAX_SPEED, MAX_SPEED);
    constrain(rspeed, -MAX_SPEED, MAX_SPEED);

    // update motors
    static const uint8_t ctrl = MMX_CONTROL_SPEED | MMX_CONTROL_GO;

    if (pid_lastLSpeed != lspeed)
    {
        mmx.setSpeedTimeAndControl(MOTOR_L, lspeed, 0, ctrl);
        pid_lastLSpeed = lspeed;
    }

    if (pid_lastRSpeed != lspeed)
    {
        mmx.setSpeedTimeAndControl(MOTOR_R, rspeed, 0, ctrl);
        pid_lastRSpeed = lspeed;
    }
}
