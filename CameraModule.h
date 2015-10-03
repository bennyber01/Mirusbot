#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include "CommunicationDefinitions.h"

#include <PololuMaestro/PololuMaestro.h>

class CameraModule
{
public:
    CameraModule();
    virtual ~CameraModule();

    void Init();
    void Update();

    void ResetAngles();

    void SetAzim(int val);
    void SetElev(int val);

    int GetAzim() { return azim; }
    int GetElev() { return elev; }

private:
    int azim;
    int elev;

    MiniMaestro maestro;
};

#endif // CAMERAMODULE_H
