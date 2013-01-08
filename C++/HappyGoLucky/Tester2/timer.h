#ifndef _TIME_H
#define _TIME_H
#define _SECURE_SCL 1
#include "characterOBJ.h"

// Frame Constants
extern const int FRAMES_PER_SECOND;
extern const int SKIP_TICKS;

// Timer functions from Lazyfoo
class Timer {
private:
	// The Clock Time When the Timer Started
	int startTicks;

	// The Ticks Stored When the Timer was Paused
	int pausedTicks;

	// The Timer Status
	bool paused;
	bool started;

public:
	// Initializes Variables
	Timer();

	// The Various Clock Actions
	void start();

	void stop();

	void pause();

	void unpause();

	// Gets the Timer's Time
	int get_ticks();

	// Checks the Status of the Timer
	bool is_started();

	bool is_paused();
};

































#endif