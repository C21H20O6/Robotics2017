#include <Arduino.h>
#include <defines.h>
#include "motorController.h"


void MotorController::Setup(int robot){
  if (robot==2){
    motorBackLeft.Setup(13,12,11,true);
    motorFrontLeft.Setup(10,9,8,false);
    motorFrontRight.Setup(7,6,5,true);
    motorBackRight.Setup(4,3,2,false);
  }else{
    motorFrontLeft.Setup(13,12,11,true);
    motorBackLeft.Setup(10,9,8,false);
    motorBackRight.Setup(7,6,5,true);
    motorFrontRight.Setup(4,2,3,false);
  }
}

void MotorController::Move(int angle, int rotation, int speed){
  double angRad = degreesToRadians(360-angle);

  double weights[2] = {
      cos(degreesToRadians(45+90)-angRad),
      cos(degreesToRadians(-45+90)-angRad)
  };


  double maxVal = fmax(doubleAbs(weights[0]),doubleAbs(weights[1]));

  double power = speed/maxVal;

  for(int i = 0; i < 2; i++){
    weights[i] = round(weights[i]*power)+rotation;
  }

  maxVal = fmax(doubleAbs(weights[0]),doubleAbs(weights[1]));

  double changeFactor = speed/maxVal;

  for(int i = 0; i < 2; i++){
    weights[i] = round(weights[i]*changeFactor);
  }

  motorFrontRight.Move(weights[1]);
  motorFrontLeft.Move(weights[0]);
  motorBackRight.Move(-weights[0]);
  motorBackLeft.Move(-weights[1]);
}

void MotorController::Turn(int speed){
  motorFrontLeft.Move(speed);
  motorFrontRight.Move(speed);
  motorBackLeft.Move(speed);
  motorBackRight.Move(speed);
}

void MotorController::Brake(){
  motorFrontLeft.Move(0);
  motorFrontRight.Move(0);
  motorBackLeft.Move(0);
  motorBackRight.Move(0);
}
