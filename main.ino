#include "cerebellum.h"
#include <Servo.h>
#include <Wire.h>

Cerebellum cerebellum;

void setup()
{
    cerebellum.Init();
}

void loop()
{
    cerebellum.Update();
}
