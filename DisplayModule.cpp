#include <DisplayModule.h>

#define SCREEN_0       0
#define SCREEN_1       1
#define SCREEN_2       2
#define SCREEN_3       3

#define BUMPER_TOP_ON  4
#define BUMPER_TOP_OFF 5
#define BUMPER_MID_ON  6
#define BUMPER_MID_OFF 7

uint8_t scr_0[8] = {B11111,B11111,B11111,B11011,B11111,B11111,B11111};
uint8_t scr_1[8] = {B11111,B11111,B11011,B11111,B11011,B11111,B11111};
uint8_t scr_2[8] = {B11111,B11111,B11011,B11111,B10101,B11111,B11111};
uint8_t scr_3[8] = {B11111,B11111,B10101,B11111,B10101,B11111,B11111};
//uint8_t scr_4[8] = {B11111,B10101,B11111,B11011,B11111,B10101,B11111};
//uint8_t scr_5[8] = {B11111,B10101,B11111,B10101,B11111,B10101,B11111};

uint8_t bumper_Top1[8] = {B11111,
                          B11111,
                          B11111,
                          B00000,
                          B00000,
                          B00000,
                          B00000};

uint8_t bumper_Top0[8] = {B00000,
                          B11111,
                          B00000,
                          B00000,
                          B00000,
                          B00000,
                          B00000};

uint8_t bumper_Mid1[8] = {B00000,
                          B00000,
                          B11111,
                          B11111,
                          B11111,
                          B00000,
                          B00000};

uint8_t bumper_Mid0[8] = {B00000,
                          B00000,
                          B00000,
                          B11111,
                          B00000,
                          B00000,
                          B00000};

uint8_t bumper_Bot1[8] = {B00000,
                          B00000,
                          B00000,
                          B00000,
                          B11111,
                          B11111,
                          B11111};

uint8_t bumper_Bot0[8] = {B00000,
                          B00000,
                          B00000,
                          B00000,
                          B00000,
                          B11111,
                          B00000};

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

DisplayModule::DisplayModule() : lcd(0x27,20,4)  // set the LCD address to 0x27 for a 20 chars and 4 line display
{
    lastScreenChangeTime = 0;
    lastScreenUpdateTime = 0;

    memset(isUpdateScr, 0, sizeof(isUpdateScr));

    screenNum = -1;
    newScreenNum = 0;
}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::Init()
{
    lcd.init();                                     // initialize the lcd
    lcd.backlight();

    lcd.createChar(SCREEN_0       , scr_0);
    lcd.createChar(SCREEN_1       , scr_1);
    lcd.createChar(SCREEN_2       , scr_2);
    lcd.createChar(SCREEN_3       , scr_3);
    lcd.createChar(BUMPER_TOP_ON  , bumper_Top1);
    lcd.createChar(BUMPER_TOP_OFF , bumper_Top0);
    lcd.createChar(BUMPER_MID_ON  , bumper_Mid1);
    lcd.createChar(BUMPER_MID_OFF , bumper_Mid0);

    pinMode(DISPLAY_NEXT_SCREEN_PIN, INPUT_PULLUP); // set pin to input
}

void DisplayModule::Print(const MotorsTicks & ticks)
{
    bool isUpdate = motorsTicks.LMotorTick != ticks.LMotorTick ||
                    motorsTicks.RMotorTick != ticks.RMotorTick;

    motorsTicks = ticks;
    isUpdateScr[0] |= isUpdate;
}

void DisplayModule::Print(const MotorsSpeed & speeds)
{
    bool isUpdate = motorsSpeed.LMotorSpeed != speeds.LMotorSpeed ||
                    motorsSpeed.RMotorSpeed != speeds.RMotorSpeed;

    motorsSpeed = speeds;
    isUpdateScr[0] |= isUpdate;
}

void DisplayModule::Print(const FrontSensorsData & data)
{
    bool isUpdate = frontSensorsData.LSensorDist != data.LSensorDist ||
                    frontSensorsData.CSensorDist != data.CSensorDist ||
                    frontSensorsData.RSensorDist != data.RSensorDist;

    frontSensorsData = data;
    isUpdateScr[1] |= isUpdate;
}

void DisplayModule::Print(const WheelsLocation & loc)
{
    bool isUpdate = wheelsLocation.leftWheelLoc.x  != loc.leftWheelLoc.x ||
                    wheelsLocation.leftWheelLoc.y  != loc.leftWheelLoc.y ||
                    wheelsLocation.rightWheelLoc.x != loc.rightWheelLoc.x ||
                    wheelsLocation.rightWheelLoc.y != loc.rightWheelLoc.y;

    wheelsLocation = loc;
    isUpdateScr[2] |= isUpdate;
}

void DisplayModule::Print(const BumpersData & data)
{
    bool isUpdate = bumpersData.FLLBumper != data.FLLBumper ||
                    bumpersData.FLBumper  != data.FLBumper  ||
                    bumpersData.FCBumper  != data.FCBumper  ||
                    bumpersData.FRBumper  != data.FRBumper  ||
                    bumpersData.FRRBumper != data.FRRBumper ||
                    bumpersData.RLBumper  != data.RLBumper  ||
                    bumpersData.RRBumper  != data.RRBumper;

    bumpersData = data;
    isUpdateScr[3] |= isUpdate;
}

void DisplayModule::Update()
{
    unsigned long time = millis();
    if (lastScreenChangeTime < time - 400)
    {
        if (digitalRead(DISPLAY_NEXT_SCREEN_PIN) == LOW)
        {
            ShowNextScreen();
            lastScreenChangeTime = time;
        }
    }

    if (lastScreenUpdateTime < time - 400)
    {
        if (screenNum != newScreenNum || isUpdateScr[screenNum])
        {
            screenNum = newScreenNum;
            lcd.clear();
            switch (screenNum)
            {
                case 0:     ShowScreen0();      break;
                case 1:     ShowScreen1();      break;
                case 2:     ShowScreen2();      break;
                case 3:     ShowScreen3();      break;
            }
            lcd.setCursor(19, 0);
            lcd.printByte(screenNum);

            isUpdateScr[screenNum] = false;

            lastScreenUpdateTime = time;
        }
    }
}

void DisplayModule::ShowScreen0()
{
    lcd.setCursor(0, 0);
    lcd.print("LMotor Ticks: ");
    lcd.print(motorsTicks.LMotorTick);

    lcd.setCursor(0, 1);
    lcd.print("RMotor Ticks: ");
    lcd.print(motorsTicks.RMotorTick);

    lcd.setCursor(0, 2);
    lcd.print("LMotor Speed: ");
    lcd.print(motorsSpeed.LMotorSpeed);

    lcd.setCursor(0, 3);
    lcd.print("RMotor Speed: ");
    lcd.print(motorsSpeed.RMotorSpeed);
}

void DisplayModule::ShowScreen1()
{
    lcd.setCursor(0, 1);
    lcd.print("LSensor Dist:");
    lcd.print(frontSensorsData.LSensorDist, 1);
    lcd.print("cm");

    lcd.setCursor(0, 2);
    lcd.print("CSensor Dist:");
    lcd.print(frontSensorsData.CSensorDist, 1);
    lcd.print("cm");

    lcd.setCursor(0, 3);
    lcd.print("RSensor Dist:");
    lcd.print(frontSensorsData.RSensorDist, 1);
    lcd.print("cm");
}

void DisplayModule::ShowScreen2()
{
    lcd.setCursor(0, 0);
    lcd.print("Wheels Location:");

    lcd.setCursor(0, 1);
    lcd.print("L: (");
    lcd.print(wheelsLocation.leftWheelLoc.x);
    lcd.print(",");
    lcd.print(wheelsLocation.leftWheelLoc.y);
    lcd.print(")");

    lcd.setCursor(0, 2);
    lcd.print("R: (");
    lcd.print(wheelsLocation.rightWheelLoc.x);
    lcd.print(",");
    lcd.print(wheelsLocation.rightWheelLoc.y);
    lcd.print(")");

    Vector2D pos = (wheelsLocation.leftWheelLoc + wheelsLocation.rightWheelLoc) * 0.5;

    lcd.setCursor(0, 3);
    lcd.print("Pos: (");
    lcd.print(pos.x);
    lcd.print(",");
    lcd.print(pos.y);
    lcd.print(")");
}

void DisplayModule::ShowScreen3()
{
    lcd.setCursor(7, 1);
    if (bumpersData.FLLBumper) { lcd.printByte(BUMPER_MID_ON); } else { lcd.printByte(BUMPER_MID_OFF); }
    if (bumpersData.FLBumper)  { lcd.printByte(BUMPER_MID_ON); } else { lcd.printByte(BUMPER_MID_OFF); }
    if (bumpersData.FCBumper)  { lcd.printByte(BUMPER_TOP_ON); } else { lcd.printByte(BUMPER_TOP_OFF); }
    if (bumpersData.FRBumper)  { lcd.printByte(BUMPER_MID_ON); } else { lcd.printByte(BUMPER_MID_OFF); }
    if (bumpersData.FRRBumper) { lcd.printByte(BUMPER_MID_ON); } else { lcd.printByte(BUMPER_MID_OFF); }

    lcd.setCursor(7, 2);
    if (bumpersData.RLBumper)
    {
        lcd.printByte(BUMPER_MID_ON);
        lcd.printByte(BUMPER_MID_ON);
    }
    else
    {
        lcd.printByte(BUMPER_MID_OFF);
        lcd.printByte(BUMPER_MID_OFF);
    }

    lcd.print(" ");

    if (bumpersData.RRBumper)
    {
        lcd.printByte(BUMPER_MID_ON);
        lcd.printByte(BUMPER_MID_ON);
    }
    else
    {
        lcd.printByte(BUMPER_MID_OFF);
        lcd.printByte(BUMPER_MID_OFF);
    }
}
