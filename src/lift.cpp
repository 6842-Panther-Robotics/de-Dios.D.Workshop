#include "main.h"

pros::Motor liftMotor (3, pros::E_MOTOR_GEARSET_36, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer pot('B');

pros::ADILineSensor line ('G');

PIDController liftPID(5,5);

void liftBrake(){
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void lift(int speed){
  liftMotor.move_velocity(speed);
}

void moveLift(int target){

  int time = 0;

  while(time < 50){

    int PIDSpeed = -liftPID.getSpeedToMotor(target, pot.get_value());

    if(fabs(liftPID.getError()) < 10){
      time++;
      wait(2);
    }

    lift(PIDSpeed);
  }
  lift(0);
  liftBrake();
}

void liftOP(){

  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  if(master.get_digital(DIGITAL_L1)) {
    liftMotor.move_velocity(100);
  }
  else if (master.get_digital(DIGITAL_L2)){
    liftMotor.move_velocity(-100);
  }
  else {
    liftMotor.move_velocity(0);
  }
}
