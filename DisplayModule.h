#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "CommunicationDefinitions.h"
#include "Nextion/Nextion.h"
#include "RobotDefinitions.h"
#include "MenuVisualizer.h"

#include "CameraModule.h"

enum WindowTypes
{
    MAIN_MENU,
    SENSORS_MENU,

    SENSORS_DISTANCE_DLG,
    SENSORS_BUMPERS_DLG,
    SENSORS_ROTATION_DLG,
    MOTORS_DLG,
    CAMERA_DLG,
    LOCATION_DLG,
    WANDERING_DLG,
    ABOUT_DLG
};

class Cerebellum;

class DisplayModule : public ArduinoModule
{
public:
    DisplayModule(Cerebellum * c);
    ~DisplayModule();

    void Init();
    void Update();

    void Print(const MotorsTicks & ticks);
    void Print(const MotorsSpeed & speeds);
    void Print(const FrontSensorsData & data);
    void Print(const BumpersData & data);
    void Print(const WheelsLocation & wheelsLocation);
    void Print(int azim);

    void ShowMainMenu();
    void ShowSensorsMenu();
    void SetSelectedMenu(int i);

    void GoBack();

    void ShowAboutDialog();
    void ShowCameraArrowsDialog();
    void ShowLocationDialog();
    void ShowSensorsDistanceDialog();
    void ShowSensorsBumpersDialog();
    void ShowSensorsRotationDialog();
    void ShowMotorsDialog();
    void ShowWanderingDialog();

    MenuVisualizer * GetMenuVisualizer() { return &menuVisualizer; }

    void CenterCam();
    void SetAzimMove(int a) { azimMove = a; }
    void SetElevMove(int e) { elevMove = e; }

private:
    unsigned long lastScreenUpdateTime;
    bool isCurrScreenNeedUpdate;

    MotorsTicks motorsTicks;
    MotorsSpeed motorsSpeed;
    FrontSensorsData frontSensorsData;
    WheelsLocation wheelsLocation;
    BumpersData bumpersData;
    int azim;

    MenuVisualizer menuVisualizer;
    int lastMainMenuScreen;
    int lastSensorsMenuScreen;
    WindowTypes currMenu;

    Cerebellum * cerebellum;
    int azimMove, elevMove;
    unsigned long lastCameraAnglesUpdate;
    void UpdateCamLocation();

    void SetCallbacksToNextionVars();

    void SetSelectedMainMenu(int i, int currScreen);
    void SetSelectedSensorsMenu(int i, int currScreen);
};

#endif
