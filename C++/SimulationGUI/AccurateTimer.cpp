/// AccurateTimer.h - Accurate Time Class Methods Implementation
/// Written By Jesse Z. Zhong

#include "AccurateTimer.h"


// Default-Constructor
AccurateTimer::AccurateTimer() {

	// Initialize Variables
	FreshStart_ = true;
	IsRunning_ = false;
	StartTime_ = 0;
	OldTime_ = 0;
	ElapsedTime_ = 0;
	TotalElapsedTime_ = 0;
}

// Returns the Milliseconds
int AccurateTimer::GetMilliseconds() const {
	return ((TotalElapsedTime_ % 3600000) % 60000) % 1000;
}

// Returns the Seconds
int AccurateTimer::GetSeconds() const {
	return ((TotalElapsedTime_ % 3600000) % 60000) / 1000;
}

// Returns the Minutes
int AccurateTimer::GetMinutes() const {
	return (TotalElapsedTime_ % 3600000) / 60000;
}

// Returns the Hours
int AccurateTimer::GetHours() const {
	return TotalElapsedTime_ / 36000000;
}

// Returns the Milliseconds as a QString
QString AccurateTimer::QGetMilliseconds() const {

	// Temporarily Store the Milliseconds
	int millis = GetMilliseconds();

	// Convert to QString with the 000 Format
	QString result, conversion;
	if((millis / 100) >= 1) result = conversion.setNum(millis);
	else if((millis / 10) >= 1) result = "0" + conversion.setNum(millis);
	else result = "00" + conversion.setNum(millis);

	// Return the Result
	return result;
}

// Returns the Seconds as a QString
QString AccurateTimer::QGetSeconds() const {
	// Temporarily Store the Milliseconds
	int secs = GetSeconds();

	// Convert to QString with the 000 Format
	QString result, conversion;
	if((secs / 10) >= 1) result = conversion.setNum(secs);
	else result = "0" + conversion.setNum(secs);

	// Return the Result
	return result;
}

// Returns the Minutes as a QString
QString AccurateTimer::QGetMinutes() const {
	// Temporarily Store the Milliseconds
	int mins = GetMinutes();

	// Convert to QString with the 000 Format
	QString result, conversion;
	if((mins / 10) >= 1) result = conversion.setNum(mins);
	else result = "0" + conversion.setNum(mins);

	// Return the Result
	return result;
}

// Returns the Hours as a QString
QString AccurateTimer::QGetHours() const {
	// Temporarily Store the Milliseconds
	int hrs = GetHours();

	// Convert to QString with the 000 Format
	QString result, conversion;
	if((hrs / 10) >= 1) result = conversion.setNum(hrs);
	else result = "0" + conversion.setNum(hrs);

	// Return the Result
	return result;
}

// Starts the Timer
void AccurateTimer::StartTimer() {

	// Set the Start Time to Current Time
	StartTime_ = clock();

	// Set FreshStart_ to False
	FreshStart_ = false;

	// Set IsRunning_ to True to Start the Updating
	IsRunning_ = true;
}

// Pauses the Timer
void AccurateTimer::PauseTimer() {

	// Set IsRunning_ to False to Stop the Updating
	IsRunning_ = false;

	// Set OldTime_ to Now Save the Accumulated Time of ElapsedTime_
	TotalElapsedTime_ = OldTime_ = ElapsedTime_ + OldTime_;
}

// Clears the Timer
void AccurateTimer::ClearTimer() {

	// Reset All Values
	FreshStart_ = true;
	IsRunning_ = false;
	StartTime_ = 0;
	OldTime_ = 0;
	ElapsedTime_ = 0;
	TotalElapsedTime_ = 0;
}

// [SLOT] Updates the Current Progress of the Timer
// When the QTimer Times Out
Q_SLOT void AccurateTimer::Update() {

	// Check the Activity of this Timer
	if(IsRunning_) {

		// Update this Current Run's Elapsed Time (from Start -> Pause is One Run)
		ElapsedTime_ = clock() - StartTime_;

		// Update the Total Elapsed Time
		// Check if it was a Fresh Start or Not; If it is, the Total is Just the
		// Elapsed Time from the Start; If Not, Add this Run's Elapsed Time with the Old Time
		if(FreshStart_) TotalElapsedTime_ = ElapsedTime_;
		else TotalElapsedTime_ = ElapsedTime_ + OldTime_;
	}
}