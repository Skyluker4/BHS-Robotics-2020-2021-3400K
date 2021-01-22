#include <cstdint>

#include "config.hpp"
#include "main.h"
#include "pros/misc.h"

// Initialize variables
uint_fast8_t speed = 32;
// int_fast8_t power, turn;

inline void drive()
{
	// Change speed for linear movements (Buttons X (increase) and B (decrease))
	if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && speed < 127)
		speed++;
	else if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && speed > 1)
		speed--;

	// Backwards (Button Down) and move cubes out
	if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
	{
		motors::driveLeft = -speed;
		motors::driveRight = -speed;
	}

	// Forwards (Button Up)
	if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
	{
		motors::driveLeft = speed;
		motors::driveRight = speed;
		return;
	}

	// Turn Left (Button Left)
	else if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
	{
		motors::driveLeft = -127;
		motors::driveRight = 127;
		return;
	}

	// Turn Right (Button Right)
	else if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
	{
		motors::driveLeft = 127;
		motors::driveRight = -127;
		return;
	}

	// Use analog stick if no drive movement buttons are pressed
	else
	{
		//power = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		//turn = controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

		// Set motors
		motors::driveLeft =
			controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		motors::driveRight =
			controllers::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		return;
	}
}

inline void intake()
{
	// Intake in
	if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
	{
		motors::intakeLeft = -127;
		motors::intakeRight = -127;
	}
	// Intake out
	else if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
	{
		motors::intakeLeft = 127;
		motors::intakeRight = 127;
	}
	// Intake hold
	else
	{
		motors::intakeLeft = 0;
		motors::intakeRight = 0;
	}
}

inline void scoring()
{
	// Score down
	if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
	{
		motors::scoreLeft = -127;
		motors::scoreRight = -127;
	}
	// Score up
	else if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
	{
		motors::scoreLeft = 127;
		motors::scoreRight = 127;
	}
	// Score hold
	else
	{
		motors::scoreLeft = 0;
		motors::scoreRight = 0;
	}
}

inline void flap()
{
	// Flap in
	if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
	{
		motors::flap = -127;
	}
	// Flap out
	else if (controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
	{
		motors::flap = 127;
	}
	// Flap hold
	else
	{
		motors::flap = 0;
	}
}

void opcontrol()
{
	// Make sure we know what's going on
	pros::lcd::clear_line(0);
	pros::lcd::print(0, "Driver mode");
	controllers::master.clear_line(1);
	controllers::master.set_text(0, 0, "Driver control");

	// Tell driver we're ready
	controllers::master.rumble("-.");

	// Begin control
	while (true)
	{
		// Run the stuff
		drive();
		intake();
		scoring();
		flap();

		// Delay for controller
		pros::delay(2);
	}
}
