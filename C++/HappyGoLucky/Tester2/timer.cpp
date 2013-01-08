#include "timer.h"

// Frame Constants
const int FRAMES_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

//Initializes variables
Timer::Timer() {
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

// The Various clock actions
void Timer::start() {
	// Start the Timer
	started = true;
	// Un-pause the Timer
	paused = false;
	// Get the Current Clock Time
	startTicks = SDL_GetTicks();
}

void Timer::stop() {
	// Stop the Timer
	started = false;

	// Un-pause the Timer
	paused = false;
}

void Timer::pause() {
	// If the Timer is running and Isn't Already Paused
	if( ( started == true ) && ( paused == false ) ) {
		// Pause the Timer
		paused = true;

		// Calculate the Paused Ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause() {
	//If the Timer is Paused
	if( paused == true ) {
		// Un-pause the Timer
		paused = false;

		//Reset the Starting Ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the Paused Ticks
		pausedTicks = 0;
	}
}

// Gets the Timer's Time
int Timer::get_ticks() {
	// If the Timer is Running
	if( started == true )
	{
		// If the Timer is Paused
		if( paused == true )
		{
			// Return the Number of Ticks When the Timer was Paused
			return pausedTicks;
		}
		else
		{
			// Return the Current Time Minus the Start Time
			return SDL_GetTicks() - startTicks;
		}
	}
	// If the Timer Isn't Running
	return 0;
}

// Checks the Status of the Timer
bool Timer::is_started() {
	return started;
}

bool Timer::is_paused() {
	return paused;
}