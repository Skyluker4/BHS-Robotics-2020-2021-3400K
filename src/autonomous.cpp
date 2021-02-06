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

void skills() {
	move(127, 2000, true);
}