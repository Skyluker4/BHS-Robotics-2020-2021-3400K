#include "config.hpp"

// Drive motors
pros::Motor motors::driveLeft(DRIVE_LEFT_MOTOR_PORT, false);
pros::Motor motors::driveRight(DRIVE_RIGHT_MOTOR_PORT, true);

// Intake motors
pros::Motor motors::intakeLeft(INTAKE_LEFT_MOTOR_PORT, true);
pros::Motor motors::intakeRight(INTAKE_RIGHT_MOTOR_PORT, false);

// Scoring motors
pros::Motor motors::scoreLeft(SCORE_LEFT_MOTOR_PORT, false);
pros::Motor motors::scoreRight(SCORE_RIGHT_MOTOR_PORT, true);

// Flap motor
pros::Motor motors::flap(FLAP_MOTOR_PORT, true);

// Controllers
pros::Controller controllers::master(pros::E_CONTROLLER_MASTER);

uint_fast8_t motors::motorPorts[] = {
	DRIVE_LEFT_MOTOR_PORT, DRIVE_RIGHT_MOTOR_PORT, INTAKE_LEFT_MOTOR_PORT,
	INTAKE_RIGHT_MOTOR_PORT, SCORE_LEFT_MOTOR_PORT,
	SCORE_RIGHT_MOTOR_PORT, FLAP_MOTOR_PORT};

// Functions
void motors::initMotors()
{
	// Set braking modes for motors
	// Drive Motors
	motors::driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	motors::driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Intake motors
	motors::intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	motors::intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Holder motor
	motors::scoreLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	motors::scoreRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Flap Motor
	motors::flap.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void motors::brakeModeHoldAllMotors()
{
	for (const auto &motor : motors::motorPorts)
		pros::c::motor_set_brake_mode(motor, pros::E_MOTOR_BRAKE_HOLD);
}

void motors::stopAllMotors()
{
	for (const auto &motor : motors::motorPorts)
		pros::c::motor_move(motor, 0);
}