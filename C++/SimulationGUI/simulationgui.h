/// SimulationGUI.h - SimulationGUI Main Window Class Implementation
/// Written by Jesse Z. Zhong

#ifndef __SIMULATIONGUI_H__
#define __SIMULATIONGUI_H__

// Qt Libraries
#include <QtGui/QMainWindow>
#include <QTimer>
#include <QFileDialog>

// Precompiled Header
#include "PrecompiledHeader.h"

// Program Includes
#include "ui_simulationgui.h"
#include "SimulationController.h"
#include "AccurateTimer.h"

// Tree Path for Environment Variables
extern const std::string ENVIRONMENT_PATH;

// Tree Path for Atomic Particles
extern const std::string PARTICLE_PATH;

// Set the Time Resolution
extern const int TIME_RESOLUTION;

//// Declare Default Number Precision
//extern const int DEFAULT_PRECISION;
//
//// Declare Default QString to Number Format
//extern const char DEFAULT_QSRT_TO_NUM_FORMAT;


class SimulationGUI : public QMainWindow {
	Q_OBJECT

public:
	// Default and Init Constructor
	SimulationGUI(QWidget *parent = 0, Qt::WFlags flags = 0);

	// Destructor
	~SimulationGUI();

private slots:
	// Starts the Simulation
	void StartSimulation();

	// Stops the Simulation if the Simulation is Already Running
	void StopSimulation();

	// Sets the Directory of the Simulation
	void SetSimulationDirectory();

	// Reads File from FileDialog and Parses it for Data
	void LoadParamFromFile();

	// Saves Parameters to File Using File Dialog to Navigate for
	// the Directory and the File Name
	void SaveParamToFile();

	// Updates Gas Edit Line Boxes Depending User Input
	void UpdateGasBoxes();

	// Update Gas Compositions
	void UpdateGasComp();

	// Updates a Selected Parameter
	void UpdateParameters();

	// Update the GUI LCD Timer
	void UpdateGUITimer();

	// Updates the Time
	void UpdateTime();

private:
	// Changes the Name of the Start Button Depending on the State
	// of the Simulation
	void ChangeStartButtonName();

	// Updates the Change Directory Box with the Directory
	void UpdateChangeDirBox();

	// Updates the Action Log Box with the Passed String
	void UpdateActionLog(QString line);

	// Start the Timer
	void StartTimer();

	// Pause the Timer
	void PauseTimer();


	#ifdef BUILD_WITH_BOOST
	// Fills in Parameter Boxes With Passed Data
	void FillParameters(boost::property_tree::ptree& data);

	// Fills a Single Parameter According to Specifications
	void FillSingleParam(boost::property_tree::ptree& data, std::string name, 
		QLineEdit* lineEditBox, int indexVal = 0);
	#endif

	// Simulation Controller
	SimulationController SimulationController_;

	// Action Log String
	QString ActionLogString_;

	// Timer for On Screen Timer
	QTimer SimulationTimerProc_;

	// Initialize Instance of AccurateTimer for a
	// System Clock Precise Timer
	AccurateTimer AccurateTimer_;

	// Instance of the UI
	Ui::SimulationGUIClass ui;
};

#endif // SIMULATIONGUI_H
