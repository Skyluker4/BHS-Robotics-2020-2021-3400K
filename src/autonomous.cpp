#include "config.hpp"
#include "main.h"
#include "movement.hpp"

void autonomous() {
	using namespace movement;
	move(127, 2000, true);
}
