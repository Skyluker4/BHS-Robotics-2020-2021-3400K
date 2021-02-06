#include "config.hpp"
#include "main.h"
#include "movement.hpp"

// Autonomous declarations
void redLeft(), redRight(), blueLeft(), blueRight(), any(), skills();

// Run correct autonomous
void autonomous() {
#ifdef RED_LEFT
	redLeft();
#endif
#ifdef RED_RIGHT
	redRight();
#endif
#ifdef BLUE_LEFT
	blueLeft();
#endif
#ifdef BLUE_RIGHT
	blueRight();
#endif
#ifdef ANY
	any();
#endif
#ifdef SKILLS
	skills();
#endif
}

// Autonomous definitions
using namespace movement;

void intake(int speed) {
	motors::intakeLeft = speed;
	motors::intakeRight = speed;

	motors::scoreLeft = speed;
	motors::scoreRight = speed;
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
	motors::flap = 127;
	pros::delay(510);

	// Turn left
	move(-127, 127, 500, true);
	pros::delay(500);

	// Forward
	move(127, 500, true);
	pros::delay(500);

	// Turn left
	move(-127, 127, 500, true);
	pros::delay(500);

	// Forward
	move(127, 500, true);
	pros::delay(500);

	// Score
	intake(127);
	pros::delay(2000);
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