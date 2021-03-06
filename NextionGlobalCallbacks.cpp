#include "NextionGlobalCallbacks.h"
#include "MenuVisualizer.h"
#include "DisplayModule.h"
#include "CameraModule.h"
#include "Cerebellum.h"
#include "SensorsModule.h"

void showMainMenuCallback(void *ptr)
{
    dbSerialPrintln("showMainMenuCallback");
    DisplayModule * disp = (DisplayModule*) ptr;
    disp -> ShowMainMenu();
}

void showCameraArrowsCallback(void *ptr)
{
    dbSerialPrintln("showCameraArrowsCallback");
    DisplayModule * disp = (DisplayModule*) ptr;
    disp -> ShowCameraArrowsDialog();
}

///////////////////////////////////////////////////////////

void goBackCallback(void *ptr)
{
    dbSerialPrintln("goBackCallback");
    DisplayModule * disp = (DisplayModule*) ptr;
    disp -> GoBack();
}

void menu1Callback(void *ptr)
{
    dbSerialPrintln("menu1Callback");
    MenuVisualizer * vis = (MenuVisualizer*) ptr;
    vis -> PressedMenu1();
}

void menu2Callback(void *ptr)
{
    dbSerialPrintln("menu2Callback");
    MenuVisualizer * vis = (MenuVisualizer*) ptr;
    vis -> PressedMenu2();
}

void menu3Callback(void *ptr)
{
    dbSerialPrintln("menu3Callback");
    MenuVisualizer * vis = (MenuVisualizer*) ptr;
    vis -> PressedMenu3();
}

void showNextMenuCallback(void *ptr)
{
    dbSerialPrintln("showNextMenuCallback");
    MenuVisualizer * vis = (MenuVisualizer*) ptr;
    vis -> ShowNextMenu();
}

void showPrevMenuCallback(void *ptr)
{
    dbSerialPrintln("showPrevMenuCallback");
    MenuVisualizer * vis = (MenuVisualizer*) ptr;
    vis -> ShowPrevMenu();
}

///////////////////////////////////////////////////////////

void cameraUpArrowPressedCallback(void *ptr)
{
    dbSerialPrintln("cameraUpArrowPressedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetElevMove(-1);
}

void cameraUpArrowReleasedCallback(void *ptr)
{
    dbSerialPrintln("cameraUpArrowReleasedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetElevMove(0);
}

void cameraDownArrowPressedCallback(void *ptr)
{
    dbSerialPrintln("cameraDownArrowPressedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetElevMove(1);
}

void cameraDownArrowReleasedCallback(void *ptr)
{
    dbSerialPrintln("cameraDownArrowReleasedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetElevMove(0);
}

void cameraLeftArrowPressedCallback(void *ptr)
{
    dbSerialPrintln("cameraLeftArrowPressedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetAzimMove(1);
}

void cameraLeftArrowReleasedCallback(void *ptr)
{
    dbSerialPrintln("cameraLeftArrowReleasedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetAzimMove(0);
}

void cameraRightArrowPressedCallback(void *ptr)
{
    dbSerialPrintln("cameraRightArrowPressedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetAzimMove(-1);
}

void cameraRightArrowReleasedCallback(void *ptr)
{
    dbSerialPrintln("cameraRightArrowReleasedCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> SetAzimMove(0);
}

void cameraCenterCallback(void *ptr)
{
    dbSerialPrintln("cameraCenterCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> CenterCam();
}

void toggleWanderingCallback(void *ptr)
{
    dbSerialPrintln("toggleWanderingCallback");
    Cerebellum * cerebellum = (Cerebellum*) ptr;
    cerebellum -> ToggleWander();
}

void resetGaugeCallback(void *ptr)
{
    dbSerialPrintln("resetGaugeCallback");
    SensorsModule * sensors = (SensorsModule*) ptr;
    sensors -> ResetAzim();
}

