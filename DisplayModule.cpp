#include "DisplayModule.h"
#include "NextionGlobalCallbacks.h"
#include "cerebellum.h"

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

extern bool sendNextionCommand(const char * format, ...);

const char * mainMenu[] =
{
    "Sensors",
    "Motors",
    "Camera",
    "Location",
    "Wandering",
    "About"
};

const int MAIN_MENU_SIZE = sizeof(mainMenu) / sizeof(mainMenu[0]);

//-------------------------------------------------------------------

const char * sensorsMenu[] =
{
    "Distance",
    "Bumpers",
    "Rotation"
};

const int SENSORS_MENU_SIZE = sizeof(sensorsMenu) / sizeof(sensorsMenu[0]);

DisplayModule::DisplayModule(Cerebellum * c) : cerebellum(c), menuVisualizer(this)
{
    lastScreenUpdateTime = 0;
    isCurrScreenNeedUpdate = false;

    currMenu = ABOUT_DLG;

    lastMainMenuScreen = -1;
    lastSensorsMenuScreen = -1;

    camAzim = camElev = 0;

    isWander = false;
}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::Print(const MotorsTicks & ticks)
{
    bool isUpdate = motorsTicks.LMotorTick != ticks.LMotorTick ||
                    motorsTicks.RMotorTick != ticks.RMotorTick;

    motorsTicks = ticks;

    if (currMenu == MOTORS_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::Print(const MotorsSpeed & speeds)
{
    bool isUpdate = motorsSpeed.LMotorSpeed != speeds.LMotorSpeed ||
                    motorsSpeed.RMotorSpeed != speeds.RMotorSpeed;

    motorsSpeed = speeds;

    if (currMenu == MOTORS_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::Print(const FrontSensorsData & data)
{
    bool isUpdate = frontSensorsData.LSensorDist != data.LSensorDist ||
                    frontSensorsData.CSensorDist != data.CSensorDist ||
                    frontSensorsData.RSensorDist != data.RSensorDist;

    frontSensorsData = data;

    if (currMenu == SENSORS_DISTANCE_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::Print(const WheelsLocation & loc)
{
    bool isUpdate = wheelsLocation.leftWheelLoc.x  != loc.leftWheelLoc.x ||
                    wheelsLocation.leftWheelLoc.y  != loc.leftWheelLoc.y ||
                    wheelsLocation.rightWheelLoc.x != loc.rightWheelLoc.x ||
                    wheelsLocation.rightWheelLoc.y != loc.rightWheelLoc.y;

    wheelsLocation = loc;

    if (currMenu == LOCATION_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
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

    if (currMenu == SENSORS_BUMPERS_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::Print(int azim)
{
    bool isUpdate = this -> azim != azim;
    this -> azim = azim;

    if (currMenu == SENSORS_ROTATION_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::PrintWandering(bool isWander)
{
    bool isUpdate = this -> isWander != isWander;
    this -> isWander = isWander;

    if (currMenu == WANDERING_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::PrintCameraAngles(int azim, int elev)
{
    bool isUpdate = camAzim != azim || camElev != elev;

    camAzim = azim;
    camElev = elev;

    if (currMenu == CAMERA_DLG)
        isCurrScreenNeedUpdate |= isUpdate;
}

void DisplayModule::Init()
{
    dbSerialBegin(9600);
    dbSerialPrintln("setup begin");

    nexInit();

    SetCallbacksToNextionVars();

    menuVisualizer.Init();

    dbSerialPrintln("setup end");

    ShowAboutDialog();
}

void DisplayModule::SetCallbacksToNextionVars()
{
    // about dialog
    page0.attachPop(goBackCallback, this);
    t0_0.attachPop(goBackCallback, this);

    // text dialog
    t2_0.attachPop(goBackCallback, this);
    q2_0.attachPop(goBackCallback, this);

    // camera dialog
    t3_0.attachPop(goBackCallback, this);
    q3_0.attachPop(goBackCallback, this);

    // go back
    q1_5.attachPop(goBackCallback, this);
    t1_0.attachPop(goBackCallback, this);

    // menu 1
    q1_0.attachPop(menu1Callback, &menuVisualizer);
    t1_1.attachPop(menu1Callback, &menuVisualizer);

    // menu 2
    q1_1.attachPop(menu2Callback, &menuVisualizer);
    t1_2.attachPop(menu2Callback, &menuVisualizer);

    // menu 3
    q1_2.attachPop(menu3Callback, &menuVisualizer);
    t1_3.attachPop(menu3Callback, &menuVisualizer);

    // Up/Down menus
    q1_3.attachPop(showNextMenuCallback, &menuVisualizer);
    q1_4.attachPop(showPrevMenuCallback, &menuVisualizer);

    ////////////////////////////////////////

    m3_0.attachPush(cameraLeftArrowPressedCallback, cerebellum);
    m3_0.attachPop(cameraLeftArrowReleasedCallback, cerebellum);
    m3_1.attachPush(cameraUpArrowPressedCallback, cerebellum);
    m3_1.attachPop(cameraUpArrowReleasedCallback, cerebellum);
    m3_2.attachPop(cameraCenterCallback, cerebellum);
    m3_3.attachPush(cameraDownArrowPressedCallback, cerebellum);
    m3_3.attachPop(cameraDownArrowReleasedCallback, cerebellum);
    m3_4.attachPush(cameraRightArrowPressedCallback, cerebellum);
    m3_4.attachPop(cameraRightArrowReleasedCallback, cerebellum);

    t4_0.attachPop(goBackCallback, this);
    q4_0.attachPop(goBackCallback, this);
    p4_0.attachPop(toggleWanderingCallback, cerebellum);

    t5_0.attachPop(goBackCallback, this);
    q5_0.attachPop(goBackCallback, this);
    m5_0.attachPop(resetGaugeCallback, cerebellum -> GetSensorsModule());
}

void DisplayModule::Update()
{
    nexLoop(nex_listen_list);

    unsigned long time = millis();
    if (lastScreenUpdateTime + 100 < time && isCurrScreenNeedUpdate)
    {
        switch (currMenu)
        {
        case SENSORS_DISTANCE_DLG:     UpdateSensorsDistanceDialog();   break;
        case SENSORS_BUMPERS_DLG:      UpdateSensorsBumpersDialog();    break;
        case SENSORS_ROTATION_DLG:     UpdateSensorsRotationDialog();   break;
        case MOTORS_DLG:               UpdateMotorsDialog();            break;
        case CAMERA_DLG:               UpdateCameraArrowsDialog();      break;
        case LOCATION_DLG:             UpdateLocationDialog();          break;
        case WANDERING_DLG:            UpdateWanderingDialog();         break;
        case ABOUT_DLG:                ShowAboutDialog();               break;
        }

        isCurrScreenNeedUpdate = false;
        lastScreenUpdateTime = time;
    }
}

void DisplayModule::ShowMainMenu()
{
    menuVisualizer.SetMenuTitles(mainMenu, MAIN_MENU_SIZE, "Menu");
    menuVisualizer.Show(lastMainMenuScreen);
    currMenu = MAIN_MENU;
}

void DisplayModule::ShowSensorsMenu()
{
    menuVisualizer.SetMenuTitles(sensorsMenu, SENSORS_MENU_SIZE, "Sensors");
    menuVisualizer.Show(lastSensorsMenuScreen);
    currMenu = SENSORS_MENU;
}

void DisplayModule::GoBack()
{
    switch (currMenu)
    {
    case MAIN_MENU:
        ShowAboutDialog();
        break;
    case SENSORS_MENU:
        ShowMainMenu();
        break;
    //---------------------------------
    case SENSORS_DISTANCE_DLG:
        ShowSensorsMenu();
        break;
    case SENSORS_BUMPERS_DLG:
        ShowSensorsMenu();
        break;
    case SENSORS_ROTATION_DLG:
        ShowSensorsMenu();
        break;
    case MOTORS_DLG:
        ShowMainMenu();
        break;
    case CAMERA_DLG:
        ShowMainMenu();
        break;
    case LOCATION_DLG:
        ShowMainMenu();
        break;
    case WANDERING_DLG:
        ShowMainMenu();
        break;
    case ABOUT_DLG:
        ShowMainMenu();
        break;
    }
}

void DisplayModule::SetSelectedMenu(int i)
{
    int currScreen = menuVisualizer.GetLastScreenNum();

    switch (currMenu)
    {
    case MAIN_MENU:
        SetSelectedMainMenu(i, currScreen);
        break;
    case SENSORS_MENU:
        SetSelectedSensorsMenu(i, currScreen);
        break;
    }
}

void DisplayModule::SetSelectedMainMenu(int i, int currScreen)
{
    lastMainMenuScreen = currScreen;

    switch (i)
    {
    case 0:
        ShowSensorsMenu();
        break;
    case 1:
        ShowMotorsDialog();
        break;
    case 2:
        ShowCameraArrowsDialog();
        break;
    case 3:
        ShowLocationDialog();
        break;
    case 4:
        ShowWanderingDialog();
        break;
    case 5:
        ShowAboutDialog();
        break;
    }
}

void DisplayModule::SetSelectedSensorsMenu(int i, int currScreen)
{
    lastSensorsMenuScreen = currScreen;

    switch (i)
    {
    case 0:
        ShowSensorsDistanceDialog();
        break;
    case 1:
        ShowSensorsBumpersDialog();
        break;
    case 2:
        ShowSensorsRotationDialog();
        break;
    }
}
