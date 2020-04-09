#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

pros::ADIDigitalIn selector ('A');
int autonIndex = 0;

void autonSelector(){

	const int autoCount = 2;

	const char *autoNames[autoCount] = {
		"Red Front Auton"
		"Blue Front Auton"
	};

	while(true){
		if (selector.get_value() == 1){
			autonIndex++;
			if(autonIndex == autoCount){
				autonIndex = 0;
			}
			//%s = print string
			//%d = print int
			//%f = print for double or flout
			pros::lcd::print(4,"%s", autoNames[autonIndex]);
			wait(300);
		}
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::Task auton_selector(autonSelector);

	inertial.reset();

	int time = pros::millis();
	int iter= 0;
	while(inertial.is_calibrating()){
		iter+=10;
		wait(10);
	}
	}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
pros::Controller master(pros::E_CONTROLLER_MASTER);
void opcontrol() {

	while (true) {
		pros::lcd::print(5, "%f", inertial.get_rotation());
		if(master.get_digital(DIGITAL_A) && !pros::competition::is_connected())
		{
			autonomous();
		}
		liftOP();
		driveOP();
		pros::delay(20);
	}
}
