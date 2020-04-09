#include "main.h"

PIDController::PIDController(double inkP, int inMinSpeed){
  kP = inkP;
  minSpeed = inMinSpeed;
}

int PIDController::getSpeedToMotor(int target, int current){

  double error = target - current;

  int speed = error *kP;

  if(speed <= minSpeed && speed >= 0){
    speed = minSpeed;
  }
  else if(speed <= minSpeed && speed <= 0){
    speed = -minSpeed;
  }

  return 0;

}

double PIDController:: getError(){
  return error;
}
