#include <cstdint>

#include "config.hpp"
#include "main.h"

bool scoreArcade = false;
bool leftArcade = true;

inline void drive(uint_fast8_t& driveSpeed) {
	// Change speed for linear movements (Buttons A (increase) and Y (decrease))
	if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && driveSpeed < 127)
		driveSpeed++;
	else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && driveSpeed > 1)
		driveSpeed--;

	// Backwards (Button Down) and move cubes out
	if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		motors::driveLeft = -driveSpeed;
		motors::driveRight = -driveSpeed;
	}

	// Forwards (Button Up)
	if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		motors::driveLeft = driveSpeed;
		motors::driveRight = driveSpeed;
		return;
	}

	// Turn Left (Button Left)
	else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		motors::driveLeft = -driveSpeed;
		motors::driveRight = driveSpeed;
		return;
	}

	// Turn Right (Button Right)
	else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		motors::driveLeft = driveSpeed;
		motors::driveRight = -driveSpeed;
		return;
	}

	// Use analog stick if no drive movement buttons are pressed
	else {
		// Arcade drive
		if(controls::arcade) {
			int power, turn;
			if(leftArcade) {
				power = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
				turn = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
			} else {
				power = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
				turn = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
			}

			motors::driveLeft = power + turn;
			motors::driveRight = power - turn;
		}
		// Tank drive
		else {
			motors::driveLeft = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			motors::driveRight = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		}
		return;
	}
}

inline void intake() {
	// Speed for intake
	constexpr uint_fast8_t intakeSpeed = 127;

	// Intake in
	if(controllers::master.get_digital(controls::intake.forward)) {
		motors::intakeLeft = intakeSpeed;
		motors::intakeRight = intakeSpeed;
	}
	// Intake out
	else if(controllers::master.get_digital(controls::intake.backward)) {
		motors::intakeLeft = -intakeSpeed;
		motors::intakeRight = -intakeSpeed;
	}
	// Intake hold
	else {
		motors::intakeLeft = 0;
		motors::intakeRight = 0;
	}
}

inline void scoring() {
	uint_fast8_t scoringSpeed = 127;

	if(!scoreArcade) {
		// Score up
		if(controllers::master.get_digital(controls::scoring.forward)) {
			motors::scoreRight = -scoringSpeed;
			motors::scoreLeft = -scoringSpeed;
		}
		// Score down
		else if(controllers::master.get_digital(controls::scoring.backward)) {
			motors::scoreLeft = scoringSpeed;
			motors::scoreRight = scoringSpeed;
		}
		// Score hold
		else {
			motors::scoreLeft = 0;
			motors::scoreRight = 0;
		}
	} else {
		scoringSpeed = -controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		motors::scoreLeft = scoringSpeed;
		motors::scoreRight = scoringSpeed;
	}
}

inline void flap() {
	// Flap in
	if(controllers::master.get_digital(controls::flap.forward)) {
		motors::flap = -127;
	}
	// Flap out
	else if(controllers::master.get_digital(controls::flap.backward)) {
		motors::flap = 50;
	}
	// Flap hold
	else {
		motors::flap = 0;
	}
}

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
			scoreArcade = true;
			leftArcade = false;
		}
		pros::delay(2);
	}

	controllers::master.rumble("...");
}

void opcontrol() {
	// Make sure we know what's going on
	pros::lcd::clear_line(0);
	pros::lcd::print(0, "Driver mode");
	controllers::master.clear_line(1);
	controllers::master.set_text(0, 0, "Driver control");

	// Prompt for button layout
	configButton();

	// Setup variables
	uint_fast8_t driveSpeed = 127;

	// Move intakes down
	motors::intakeMover = 127;
	pros::delay(300);
	motors::intakeMover = 0;

	// Tell driver we're ready
	controllers::master.rumble("-.");

	// Begin control
	while(true) {
		// Run all subsystems
		drive(driveSpeed);
		intake();
		scoring();
		flap();

		// Delay for controller
		pros::delay(2);
	}
}