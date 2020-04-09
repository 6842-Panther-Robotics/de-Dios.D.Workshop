#include "main.h"

pros::Imu inertial(8);

pros::Motor rightFront (14 ,pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (6 ,pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront (13 ,pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (4 ,pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);

int TICS_PER_REVOLUTION = 360;
double WHEEL_DIAMETER = 4;
double pi = 3.14159;

double CORRECTION_FACTOR = 0.8;
int THRESHOLD = -5;

PIDController movePID(0.1, 30);
PIDController turnPID(2.5, 30);

void moveBackward (int inches) {

    rightFront.tare_position();
    leftFront.tare_position();

    int time = 0;

    double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

  while(time < 50) {

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = leftFront.get_position();

      int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

      if (rightFront.get_position() - leftFront.get_position() <= THRESHOLD) {
        right(-PIDSpeed);
        left(-PIDSpeed * CORRECTION_FACTOR);
      }
      else if (leftFront.get_position() - rightFront.get_position() <= THRESHOLD) {
      right(-PIDSpeed * CORRECTION_FACTOR);
      left(-PIDSpeed);
    }
    else {
      right(-PIDSpeed);
      left(-PIDSpeed);
    }
      if(fabs(movePID.getError()) < 1){
        time++;
        wait(2);
      }

    }
    left(0);
    right(0);
  }


void moveForward (int inches) {

  rightFront.tare_position();
  leftFront.tare_position();

  int time = 0;

  double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

while(time < 50) {

  int rightFrontPosition = rightFront.get_position();
  int leftFrontPosition = leftFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFront.get_position() - leftFront.get_position() <= THRESHOLD) {
      right(PIDSpeed);
      left(PIDSpeed * CORRECTION_FACTOR);
    }
    else if (leftFront.get_position() - rightFront.get_position() <= THRESHOLD) {
    right(PIDSpeed * CORRECTION_FACTOR);
    left(PIDSpeed);
  }
  else {
    right(PIDSpeed);
    left(PIDSpeed);
  }
    if(fabs(movePID.getError()) < 1){
      time++;
      wait(2);
    }

  }
  left(0);
  right(0);
}

void wait(int time){
  pros::delay(time);
}

void timedDrive(int time, int speed) {
right(speed);
left(speed);
wait(time);
right(0);
right(0);
}

void left(int speed)
{
  leftFront.move(speed);
  leftBack.move(speed);
}

void right(int speed)
{
  rightFront.move(speed);
  rightBack.move(speed);
}

void brake()
{
rightFront.set_brake_mode(pros:: E_MOTOR_BRAKE_BRAKE);
rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
leftFront.set_brake_mode(pros:: E_MOTOR_BRAKE_BRAKE);
leftBack.set_brake_mode(pros:: E_MOTOR_BRAKE_BRAKE);
}

void coast()
{
rightFront.set_brake_mode(pros:: E_MOTOR_BRAKE_COAST);
rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
leftFront.set_brake_mode(pros:: E_MOTOR_BRAKE_COAST);
leftBack.set_brake_mode(pros:: E_MOTOR_BRAKE_COAST);
}



void turn(int degrees) {

  int time = 0;

  while(time < 50) {


  left(turnPID.getSpeedToMotor(degrees,inertial.get_rotation()));
  right(-turnPID.getSpeedToMotor(degrees,inertial.get_rotation()));

  if (fabs(turnPID.getError()) < 1){
    time++;
    wait(2);
  }
}
right(0);
left(0);
}



void driveOP(){
rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
leftFront.move(master.get_analog(ANALOG_LEFT_Y));
leftBack.move(master.get_analog(ANALOG_LEFT_Y));
}
