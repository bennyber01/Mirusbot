#include "DisplayModule.h"
#include "NextionGlobalCallbacks.h"
#include "cerebellum.h"


const char * version = "Version 1.0.0";

extern bool sendNextionCommand(const char * format, ...);

void DisplayModule::ShowAboutDialog()
{
    sendNextionCommand("page 0");
    sendNextionCommand("t0.txt=\"%s\"", version);
    currMenu = ABOUT_DLG;
}

void DisplayModule::ShowCameraArrowsDialog()
{
    sendNextionCommand("page 3");
    sendNextionCommand("t0.txt=\"Camera Controls\"");
    UpdateCameraArrowsDialog();
    currMenu = CAMERA_DLG;
}

void DisplayModule::UpdateCameraArrowsDialog()
{
    sendNextionCommand("t1.txt=\"Azim:%d\"", cerebellum -> GetCameraModule().GetAzim());
    sendNextionCommand("t2.txt=\"Elev:%d\"", cerebellum -> GetCameraModule().GetElev());
}

void DisplayModule::ShowSensorsDistanceDialog()
{
    sendNextionCommand("page 2");
    sendNextionCommand("t0.txt=\"Distance Sensors\"");
    UpdateSensorsDistanceDialog();
    currMenu = SENSORS_DISTANCE_DLG;
}

void DisplayModule::UpdateSensorsDistanceDialog()
{
    sendNextionCommand("t1.txt=\"LSensor Dist: %0.1f cm\"", frontSensorsData.LSensorDist);
    sendNextionCommand("t2.txt=\"CSensor Dist: %0.1f cm\"", frontSensorsData.CSensorDist);
    sendNextionCommand("t3.txt=\"RSensor Dist: %0.1f cm\"", frontSensorsData.RSensorDist);
}

void DisplayModule::ShowSensorsBumpersDialog()
{
    sendNextionCommand("page 2");
    sendNextionCommand("t0.txt=\"Bumpers Sensors\"");
    UpdateSensorsBumpersDialog();
    currMenu = SENSORS_BUMPERS_DLG;
}

void DisplayModule::UpdateSensorsBumpersDialog()
{
    char bmpr[9];
    bmpr[0] = ((bumpersData.FLLBumper)?'*':'-');
    bmpr[1] = ((bumpersData.FLBumper)?'*':'-');
    bmpr[2] = ((bumpersData.FCBumper)?'*':'-');
    bmpr[3] = ((bumpersData.FRBumper)?'*':'-');
    bmpr[4] = ((bumpersData.FRRBumper)?'*':'-');
    bmpr[5] = 0;
    sendNextionCommand("t1.txt=\"%s\"", bmpr);

    bmpr[0] = ((bumpersData.RLBumper)?'*':'-');
    bmpr[1] = ((bumpersData.RRBumper)?'*':'-');
    bmpr[2] = 0;
    sendNextionCommand("t2.txt=\"%s\"", bmpr);
}

void DisplayModule::ShowSensorsRotationDialog()
{
    sendNextionCommand("page 5");
    sendNextionCommand("t0.txt=\"Rotation Sensors\"");
    UpdateSensorsRotationDialog();
    currMenu = SENSORS_ROTATION_DLG;
}

void DisplayModule::UpdateSensorsRotationDialog()
{
    sendNextionCommand("z0.val=%d", azim);
}

void DisplayModule::ShowLocationDialog()
{
    sendNextionCommand("page 2");
    sendNextionCommand("t0.txt=\"Location\"");
    UpdateLocationDialog();
    currMenu = LOCATION_DLG;
}

void DisplayModule::UpdateLocationDialog()
{
    sendNextionCommand("t1.txt=\"L: (%d,%d)\"", wheelsLocation.leftWheelLoc.x,  wheelsLocation.leftWheelLoc.y);
    sendNextionCommand("t2.txt=\"R: (%d,%d)\"", wheelsLocation.rightWheelLoc.x, wheelsLocation.rightWheelLoc.y);
    Vector2D pos = (wheelsLocation.leftWheelLoc + wheelsLocation.rightWheelLoc) * 0.5;
    sendNextionCommand("t3.txt=\"Pos: (%d,%d)\"", pos.x, pos.y);
}

void DisplayModule::ShowMotorsDialog()
{
    sendNextionCommand("page 2");
    sendNextionCommand("t0.txt=\"Motors\"");
    UpdateMotorsDialog();
    currMenu = MOTORS_DLG;
}

void DisplayModule::UpdateMotorsDialog()
{
    sendNextionCommand("t1.txt=\"LMotor Ticks: %d\"", motorsTicks.LMotorTick);
    sendNextionCommand("t2.txt=\"RMotor Ticks: %d\"", motorsTicks.RMotorTick);
    sendNextionCommand("t3.txt=\"LMotor Speed: %d\"", motorsSpeed.LMotorSpeed);
    sendNextionCommand("t4.txt=\"RMotor Speed: %d\"", motorsSpeed.RMotorSpeed);
}

void DisplayModule::ShowWanderingDialog()
{
    sendNextionCommand("page 4");
    sendNextionCommand("t0.txt=\"Wander\"");
    UpdateWanderingDialog();
    currMenu = WANDERING_DLG;
}

void DisplayModule::UpdateWanderingDialog()
{
    sendNextionCommand("p0.pic=%d", ((cerebellum -> IsWander())?8:7));
}
