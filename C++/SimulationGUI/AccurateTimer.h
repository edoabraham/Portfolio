/// AccurateTimer.h - Accurate Time Class Implementation
/// Written By Jesse Z. Zhong

// Precompiled Header
#include "PrecompiledHeader.h"
#include <QObject>

/// Timer Class that Uses the clock() for Accurate Time Readings
/// And the Qt QTimer Object to Update the Timer's Time
/// Use Along Side a QTimer to Achieve the Correct Behavior
class AccurateTimer : public QObject {
	Q_OBJECT

public:
	// Default-Constructor
	AccurateTimer();

	// Returns the Milliseconds
	int GetMilliseconds() const;

	// Returns the Seconds
	int GetSeconds() const;

	// Returns the Minutes
	int GetMinutes() const;

	// Returns the Hours
	int GetHours() const;

	// Returns the Milliseconds as a QString
	QString QGetMilliseconds() const;

	// Returns the Seconds as a QString
	QString QGetSeconds() const;

	// Returns the Minutes as a QString
	QString QGetMinutes() const;

	// Returns the Hours as a QString
	QString QGetHours() const;

	// Starts the Timer
	void StartTimer();

	// Pauses the Timer
	void PauseTimer();

	// Clears the Timer
	void ClearTimer();

	// [SLOT] Updates the Current Progress of the Timer
	// When the QTimer Times Out
	Q_SLOT void Update();

private:
	// Checks if It is a Fresh Start or Not
	bool FreshStart_;

	// Checks if the Timer is Active
	bool IsRunning_;

	// Store the Start Time
	long int StartTime_;

	// Store Time From an Old Run
	long int OldTime_;

	// Stores the Accumulated Time During a Single Run
	long int ElapsedTime_;

	// Stores the Total Elapsed Time
	long int TotalElapsedTime_;

};