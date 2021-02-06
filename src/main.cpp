#include "main.h"
#include "config.hpp"

void configButton() {
	bool buttonsMapped = false;

	while(!buttonsMapped) {
		// Ethan
		if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			controls::intake.forward = pros::E_CONTROLLER_DIGITAL_R1;
			controls::intake.backward = pros::E_CONTROLLER_DIGITAL_L1;

			controls::scoring.forward = controls::intake.forward;
			controls::scoring.backward = controls::intake.backward;

			controls::flap.forward = pros::E_CONTROLLER_DIGITAL_X;
			controls::flap.backward = pros::E_CONTROLLER_DIGITAL_B;

			buttonsMapped = true;

			controls::arcade = false;
		}
		// Samuel
		else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			controls::intake.forward = pros::E_CONTROLLER_DIGITAL_R1;
			controls::intake.backward = pros::E_CONTROLLER_DIGITAL_R2;

			controls::scoring.forward = controls::intake.forward;
			controls::scoring.backward = controls::intake.backward;

			controls::flap.forward = pros::E_CONTROLLER_DIGITAL_L1;
			controls::flap.backward = pros::E_CONTROLLER_DIGITAL_L2;

			buttonsMapped = true;

			controls::arcade = true;
		}
		pros::delay(2);
	}

	controllers::master.rumble("...");
}

void initialize() {
	// Set up motors
	motors::initMotors();

	// Set up screen
	pros::lcd::initialize();

	// Prompt for button layout
	configButton();
}

void competition_initialize() {}

void disabled() {
	// Stop All Motors
	motors::brakeModeHoldAllMotors();
	motors::stopAllMotors();
}