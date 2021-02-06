#ifndef MOTORCONFIG
#define MOTORCONFIG

#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"
#include <cstdint>

// Port Mapping
// Drive motors
#define DRIVE_LEFT_MOTOR_PORT 11
#define DRIVE_RIGHT_MOTOR_PORT 20

// Intake motors
#define INTAKE_LEFT_MOTOR_PORT 1
#define INTAKE_RIGHT_MOTOR_PORT 10

// Scoring motors
#define SCORE_LEFT_MOTOR_PORT 2
#define SCORE_RIGHT_MOTOR_PORT 9

// Flap motor
#define FLAP_MOTOR_PORT 8

namespace motors {
	// Drive motors
	extern pros::Motor driveLeft;
	extern pros::Motor driveRight;

	// Intake motors
	extern pros::Motor intakeLeft;
	extern pros::Motor intakeRight;

	// Scoring motors
	extern pros::Motor scoreLeft;
	extern pros::Motor scoreRight;

	// Flap motor
	extern pros::Motor flap;

	extern uint_fast8_t motorPorts[];

	// Functions
	extern void initMotors();
	extern void brakeModeHoldAllMotors();
	extern void stopAllMotors();
} // namespace motors

struct simpleControl {
	pros::controller_digital_e_t forward;
	pros::controller_digital_e_t backward;

	simpleControl(pros::controller_digital_e_t f, pros::controller_digital_e_t b);
};

namespace controls {
	extern simpleControl intake;
	extern simpleControl scoring;
	extern simpleControl flap;

	extern bool arcade;
} // namespace controls

namespace controllers {
	extern pros::Controller master;
}

#endif