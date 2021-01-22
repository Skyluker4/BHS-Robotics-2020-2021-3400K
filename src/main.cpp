#include "main.h"
#include "config.hpp"

void initialize()
{
	// Set up motors
	motors::initMotors();

	// Set up screen
	pros::lcd::initialize();
}

void disabled()
{
	// Stop All Motors
	motors::brakeModeHoldAllMotors();
	motors::stopAllMotors();
}

void competition_initialize() {}