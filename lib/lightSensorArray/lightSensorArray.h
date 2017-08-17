#ifndef LIGHTSENSORARRAY_H_
#define LIGHTSENSORARRAY_H_

#include <Arduino.h>
#include <lightSensor.h>
#include <defines.h>
#include <apexCommon.h>

class LightSensorArray{
public:
  int onWhite[4];
  double angle;
  int iComp = 0;
  int jComp = 0;
  int vectori, vectorj;
  int iCords[4] = {0, 1, 0, -1};
  int jCords[4] = {1, 0, -1, 0};
  int lightValues[4] = {0};
  int thresholds[4] = {0};

  LightSensor lsFront;
  LightSensor lsLeft;
  LightSensor lsBack;
  LightSensor lsRight;

  void Setup();
  void SetThresh();
  void GetVal();
  double LightAngle();
};

#endif