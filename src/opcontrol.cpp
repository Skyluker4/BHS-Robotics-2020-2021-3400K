#include <cstdint>

#include "config.hpp"
#include "main.h"

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
		// Set motors
		motors::driveLeft = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		motors::driveRight = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		return;
	}
}

inline void intake() {
	// Speed for intake
	constexpr uint_fast8_t intakeSpeed = 127;

	// Intake in
	if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		motors::intakeLeft = intakeSpeed;
		motors::intakeRight = intakeSpeed;
	}
	// Intake out
	else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
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
	constexpr uint_fast8_t scoringSpeed = 127;

	// Score down
	if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		motors::scoreRight = scoringSpeed;
		motors::scoreLeft = scoringSpeed;
	}
	// Score up
	else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		motors::scoreLeft = -scoringSpeed;
		motors::scoreRight = -scoringSpeed;
	}
	// Score hold
	else {
		motors::scoreLeft = 0;
		motors::scoreRight = 0;
	}
}

inline void flap() {
	// Flap in
	if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
		motors::flap = -127;
	}
	// Flap out
	else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
		motors::flap = 50;
	}
	// Flap hold
	else {
		motors::flap = 0;
	}
}

void opcontrol() {
	// Make sure we know what's going on
	pros::lcd::clear_line(0);
	pros::lcd::print(0, "Driver mode");
	controllers::master.clear_line(1);
	controllers::master.set_text(0, 0, "Driver control");

	// Setup variables
	uint_fast8_t driveSpeed = 127;

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