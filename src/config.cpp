#include "config.hpp"
#include "main.h"
#include "movement.hpp"

// Drive motors
pros::Motor motors::driveLeft(DRIVE_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, false);
pros::Motor motors::driveRight(DRIVE_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, true);

// Intake motors
pros::Motor motors::intakeLeft(INTAKE_LEFT_MOTOR_PORT, true);
pros::Motor motors::intakeRight(INTAKE_RIGHT_MOTOR_PORT, false);
pros::Motor motors::intakeMover(INTAKE_MOVER_PORT, false);

// Scoring motors
pros::Motor motors::scoreLeft(SCORE_LEFT_MOTOR_PORT, false);
pros::Motor motors::scoreRight(SCORE_RIGHT_MOTOR_PORT, true);

// Flap motor
pros::Motor motors::flap(FLAP_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, true);

// Controllers
pros::Controller controllers::master(pros::E_CONTROLLER_MASTER);

uint_fast8_t motors::motorPorts[] = {
	DRIVE_LEFT_MOTOR_PORT, DRIVE_RIGHT_MOTOR_PORT, INTAKE_LEFT_MOTOR_PORT,
	INTAKE_RIGHT_MOTOR_PORT, SCORE_LEFT_MOTOR_PORT,
	SCORE_RIGHT_MOTOR_PORT, FLAP_MOTOR_PORT};

// Functions
void motors::initMotors() {
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
void motors::brakeModeHoldAllMotors() {
	for(const auto& motor : motors::motorPorts)
		pros::c::motor_set_brake_mode(motor, pros::E_MOTOR_BRAKE_HOLD);
}

void motors::stopAllMotors() {
	for(const auto& motor : motors::motorPorts)
		pros::c::motor_move(motor, 0);
}

// Controls

simpleControl::simpleControl(pros::controller_digital_e_t f, pros::controller_digital_e_t b) {
	forward = f;
	backward = b;
}

simpleControl controls::intake(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_Y);
simpleControl controls::scoring(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_Y);
simpleControl controls::flap(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_Y);

bool controls::arcade = false;
bool controls::scoreArcade = false;
bool controls::leftArcade = true;

void controls::configButton() {
	using namespace controls;

	bool buttonsMapped = false;

	while(!buttonsMapped) {
		// Ethan
		if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			intake.forward = pros::E_CONTROLLER_DIGITAL_R1;
			intake.backward = pros::E_CONTROLLER_DIGITAL_L1;

			scoring.forward = controls::intake.forward;
			scoring.backward = controls::intake.backward;

			flap.forward = pros::E_CONTROLLER_DIGITAL_X;
			flap.backward = pros::E_CONTROLLER_DIGITAL_B;

			arcade = false;

			buttonsMapped = true;
		}
		// Samuel
		else if(controllers::master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			intake.forward = pros::E_CONTROLLER_DIGITAL_R1;
			intake.backward = pros::E_CONTROLLER_DIGITAL_R2;

			scoring.forward = controls::intake.forward;
			scoring.backward = controls::intake.backward;

			flap.forward = pros::E_CONTROLLER_DIGITAL_L1;
			flap.backward = pros::E_CONTROLLER_DIGITAL_L2;

			arcade = true;
			scoreArcade = true;
			leftArcade = false;

			buttonsMapped = true;
		}
		pros::delay(2);
	}

	controllers::master.rumble("...");
}