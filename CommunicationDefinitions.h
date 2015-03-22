#ifndef COMMUNICATION_DEFINITIONS_H
#define COMMUNICATION_DEFINITIONS_H

#ifdef __AVR_ATmega328P__
#include "ArduinoDefinitions.h"
#endif

#pragma pack(push, 1) // exact fit - no padding

#ifndef LONG
#define LONG long
#endif

#ifndef FLOAT
#define FLOAT float
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

struct MotorsSpeed
{
    MotorsSpeed() { memset(this, 0, sizeof(MotorsSpeed)); }
    UCHAR LMotorSpeed;
    UCHAR RMotorSpeed;
};

struct MotorsTicks
{
    MotorsTicks() { memset(this, 0, sizeof(MotorsTicks)); }
    LONG LMotorTick;
    LONG RMotorTick;
};

struct FrontSensorsData
{
    FrontSensorsData() { memset(this, 0, sizeof(FrontSensorsData)); }
    FLOAT LSensorDist;       // left sensor
    FLOAT CSensorDist;       // center sensor
    FLOAT RSensorDist;       // right sensor
};

struct BumpersData
{
    BumpersData() { memset(this, 0, sizeof(BumpersData)); }
    UCHAR FLLBumper;       // front most left bumper
    UCHAR FLBumper;        // front left bumper
    UCHAR FCBumper;        // front center bumper
    UCHAR FRBumper;        // front right bumper
    UCHAR FRRBumper;       // front most right bumper
    UCHAR RLBumper;        // rear left bumper
    UCHAR RRBumper;        // rear right bumper
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
