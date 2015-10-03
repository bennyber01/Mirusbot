#ifndef CEREBELLUM_H
#define CEREBELLUM_H

#include <Arduino.h>
#include "CommunicationDefinitions.h"
#include "DisplayModule.h"
#include "MotorsModule.h"
#include "SensorsModule.h"
#include "RobotDefinitions.h"
#include "RobotBehaviour.h"

class Cerebellum : public ArduinoModule, public RobotBehaviour
{
public:
    Cerebellum();
    ~Cerebellum();

    void Init();
    void Update();

    void ToggleWander();
    bool IsWander() { return isWander; }

    SensorsModule * GetSensorsModule() { return &sensors; }

    void CenterCam();
    void SetAzimMove(int a) { azimMove = a; }
    void SetElevMove(int e) { elevMove = e; }

private:
    DisplayModule disp;
    MotorsModule motors;
    SensorsModule sensors;
    CameraModule cameraModule;

    void UpdateRobotBehaviour();
    void Test1();
    void Test2();

    void HandleCommand(const CommandEntry & entry);

    bool isWander;

    int azimMove, elevMove;
    unsigned long lastCameraAnglesUpdate;
    void UpdateCamLocation();
};

#endif
