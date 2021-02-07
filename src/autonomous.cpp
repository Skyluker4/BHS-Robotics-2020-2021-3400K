#include "config.hpp"
#include "main.h"
#include "movement.hpp"

// Autonomous declarations
void redLeft(), redRight(), blueLeft(), blueRight(), any(), skills();

// Run correct autonomous
void autonomous() {
	skills();
}

// Autonomous definitions
using namespace movement;

void intake(int speed) {
	motors::intakeLeft = speed;
	motors::intakeRight = speed;

	motors::scoreLeft = -speed;
	motors::scoreRight = -speed;
}

void skills() {
	// Move forward some
	move(127, 500);

	// Start intake
	intake(127);
	pros::delay(500);

	// Stop robot and intake
	move(0, 0, 10, true);
	intake(0);
	pros::delay(100);

	// Move scorer up
	motors::flap = -127;
	pros::delay(500);
	motors::flap = 127;
	pros::delay(510);
	motors::flap = -127;
	pros::delay(500);
	motors::flap = 50;
	pros::delay(230);
	motors::flap = -127;
	pros::delay(500);
	motors::flap = 127;
	pros::delay(510);
	motors::flap = -127;
	pros::delay(20);
	motors::flap = 0;

	// Turn left
	move(-127, 127, 500, true);
	pros::delay(500);

	// Forward
	move(127, 1580, true);
	pros::delay(500);

	// Turn left
	move(-127, 127, 600, true);
	pros::delay(500);

	// Forward
	move(127, 900, true);
	pros::delay(500);

	// Turn right
	move(127, -127, 100, true);
	pros::delay(500);

	// Score
	motors::flap = 127;
	pros::delay(10);
	motors::flap = 0;
	pros::delay(510);
	intake(-127);
	pros::delay(400);
	intake(127);
	pros::delay(5000);
	intake(0);

	// Forward
	move(100, 100, true);
	pros::delay(500);

	// Backward
	move(-127, 750, true);
	pros::delay(500);

	// Stop
	move(0, 0, 10, true);
	motors::stopAllMotors();

	// Done
}