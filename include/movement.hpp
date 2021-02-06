#ifndef MOVEMENT
#define MOVEMENT

namespace movement {
	void move(int leftSpeed, int rightSpeed, int milliseconds, bool stop = false);
	void move(int speed, int milliseconds, bool stop = false);
} // namespace movement

#endif