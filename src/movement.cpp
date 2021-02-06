#include "movement.hpp"
#include "config.hpp"
#include "main.h"

void movement::move(int leftSpeed, int rightSpeed, int milliseconds, bool stop) {
	motors::driveLeft = leftSpeed;
	motors::driveRight = rightSpeed;
	pros::delay(milliseconds);

	if(stop) {
		motors::driveLeft = 0;
		motors::driveRight = 0;
	}
}

void movement::move(int speed, int milliseconds, bool stop) {
	move(speed, speed, milliseconds, stop);
}