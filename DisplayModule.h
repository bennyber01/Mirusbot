#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "CommunicationDefinitions.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "RobotDefinitions.h"

#define MAX_NUM_OF_SCREENS  4

class DisplayModule : public ArduinoModule
{
public:
    DisplayModule();
    ~DisplayModule();

    void Init();

    void Print(const MotorsTicks & ticks);
    void Print(const MotorsSpeed & speeds);
    void Print(const FrontSensorsData & data);
    void Print(const BumpersData & data);
    void Print(const WheelsLocation & wheelsLocation);

    void ShowNextScreen() { newScreenNum = (newScreenNum + 1) % MAX_NUM_OF_SCREENS; }

    void Update();

private:
    LiquidCrystal_I2C lcd;

    int screenNum;
    int newScreenNum;
    unsigned long lastScreenChangeTime;
    unsigned long lastScreenUpdateTime;

    bool isUpdateScr[MAX_NUM_OF_SCREENS];

    MotorsTicks motorsTicks;                // scr: 0
    MotorsSpeed motorsSpeed;                // scr: 0
    FrontSensorsData frontSensorsData;      // scr: 1
    WheelsLocation wheelsLocation;          // scr: 2
    BumpersData bumpersData;                // scr: 3

    void ShowScreen0();
    void ShowScreen1();
    void ShowScreen2();
    void ShowScreen3();
};

#endif
