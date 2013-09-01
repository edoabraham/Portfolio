// DataVisualizer.h - Main UI class implementation.
// Written By Jesse Z. Zhong
#ifndef __Data_Visualizer_Plot_GUI_H__
#define __Data_Visualizer_Plot_GUI_H__
#pragma region Includes
#include "stdafx.h"
#include <QMainWindow>
#include "DataVisualizerGUIEX.h"
#include "StartupUIEX.h"
#include "DataManager.h"
using namespace std;
#pragma endregion
#pragma region Window Titles
const string ApplicationName = "Data Visualizer";
const string OrganizationName = "Quantum Potential Corporation";
const string StartupTitle = "Welcome to Data Visualizer";
#pragma endregion
// The implementation of the main form.
class DataVisualizer : public QMainWindow {
	Q_OBJECT
public:
#pragma region Instance
	// Constructor and Destructor
	DataVisualizer(QWidget *parent = 0) 
		: QMainWindow(parent) {

			// Program data storage containers.
			this->DataManager_ = DataManager(this);
			this->ProgramSettings_ = new QSettings(OrganizationName.c_str(),
				ApplicationName.c_str(), this);

			// Initialize the main form.
			this->UI_.setupUi(this);
			this->UI_.InitializeUI(this);
			this->setWindowTitle(tr(ApplicationName.c_str()));

			// Initialize the startup form.
			this->StartupBox_ = new QDialog(this);
			this->StartupUI_.setupUi(this->StartupBox_);
			this->StartupUI_.InitializeUI(this->StartupBox_);
			this->StartupBox_->setWindowTitle(StartupTitle.c_str());

			// Initialize members.
			this->CurrentPlot_ = 0;
			this->PlotsIterating_ = false;
			this->PlotUpdateTimer_ = new QTimer(this);

			// Initialize and bring together various UI elements.
			this->SetupUI();

			// Initialize user defined signals and slots
			this->ConnectWidgets();

			// Display the startup UI.
			this->StartupBox_->show();
	}

	~DataVisualizer() {
		// Delete the startup box.
		delete this->StartupBox_;
	}
#pragma endregion
private slots:
#pragma region Private Slots
#pragma region Data and Plots
	// Reads and stores data using the directory provided.
	void StoreData();

	// Updates and Draws the Graphs
	void RefreshGraphs();

	// Overload with Set Value Built in
	void RefreshGraphs(int value);

	// Allows for the change of states between
	// iterating and not iterating through plots.
	void ToggleIteratingPlots();

	// Increase the size of the plots and redraw.
	void EnlargePlots();

	// Decrease the size of the plots and redraw.
	void ShrinkPlots();
#pragma endregion
#pragma region Preference Tab
	// Prompts the user for a directory
	// that contains simulation data.
	void UserSetDirectory();

	// Changes the amount of milliseconds of delay there 
	// is between the drawing of one graph and the next.
	void ChangeInterval(int value);

	// Changes the type of data and units that are displayed.
	void ChangeViewMode(int index);
#pragma endregion
#pragma endregion
signals:
#pragma region Signals
    // Emits a Signal when the Files Directory is Changed
    void ChangedDirectory(const QString& value);
    void ChangedDirectory();
#pragma endregion
private:
#pragma region Helper Methods
	// Manages the connection of signals and slots.
	void ConnectWidgets();

	// Sets up various UI elements for the program to use.
	void SetupUI();
#pragma endregion
#pragma region Program Forms
	// The main UI form window for this program.
	DataVisualizerGUIEX UI_;

	// Form used for first time setup.
	StartupUIEX StartupUI_;
	QDialog* StartupBox_;
#pragma endregion
#pragma region Data Storage
	// Reads and stores data for bulks of snapshot,
	// save points, collision energy, and RPK data types.
	DataManager DataManager_;

	// Reads and writes the system settings for the program.
	QSettings* ProgramSettings_;
#pragma endregion
#pragma region Plot Data
	// Indicates the current plot that is shown.
	int CurrentPlot_;

	// Indicates whether plots are being cycled through (animated).
	bool PlotsIterating_;

	// Timer used to check when to increment to the next plot.
	QTimer* PlotUpdateTimer_;
#pragma endregion
};

#endif // __Data_Visualizer_Plot_GUI_H__
