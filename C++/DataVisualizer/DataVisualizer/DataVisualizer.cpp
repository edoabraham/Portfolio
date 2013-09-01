// DataVisualizer.cpp - Main UI class implementation.
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "DataVisualizer.h"
#pragma endregion
#pragma region Constants
#pragma region Refresh Interval
// Default refresh interval used when no value is specified.
const int DefaultInterval = 200;

// Specifies the lower range of the refresh interval.
const int MinInterval = 100;

// Specifies the upper range of the refresh interval.
const int MaxInterval = 1000;
#pragma endregion
#pragma region Plot Dimensions
// Specifies the lower range for plot widths.
const int MinPlotSize = 300;

// Specifies the upper range for plot widths.
const int MaxPlotSize = 500;

// Specifies the pixel width a plot can be expanded or reduced by.
const int ResizeIncrement = 10;
#pragma endregion
#pragma region Registry Items
// Registry key for the directory being used to read files.
const QString FileDirectory = "File Directory";

// Registry key for the refresh interval for iterating through plots.
const QString RefereshInterval = "Refresh Interval";
#pragma endregion
#pragma endregion
#pragma region Private Slots
#pragma region Data and Plots
// Reads and stores data using the directory provided.
void DataVisualizer::StoreData() {

	// Localize the previous directory, if it exists.
	QString dir = "";
	if(this->ProgramSettings_->contains(FileDirectory))
		dir = this->ProgramSettings_->value(FileDirectory).toString();

	// Check if the director is valid.
	if(!QDir().exists(dir)) {
		Util::Print(dir.toStdString() + " does not exist.");
		return;
	}

	// Set the directory that the data manager will read data from.
	this->DataManager_.SetDirPath(dir);

	// Begin storing the data into the program.
	Util::Print("Attempting to read data from " + dir.toStdString() + ".");
	this->DataManager_.StoreData();
	Util::Print("Data stored.");

	// Initialize Slider Bar with the Correct Values
	this->UI_.SeekSlider->setMinimum(0);
	this->UI_.SeekSlider->setMaximum((this->DataManager_.GetMaxSets() < -1) 
		? 0 : (this->DataManager_.GetMaxSets() - 1));

	// Reset the all the plot related UI's.
	this->RefreshGraphs(0);
}

// Updates and Draws the Graphs
void DataVisualizer::RefreshGraphs() {

 	// Refresh the Graphs
	this->RefreshGraphs(this->CurrentPlot_);
		
 	// Iterate Up
 	if(this->PlotsIterating_) this->CurrentPlot_++;
}

// Overload with Set Value Built in
void DataVisualizer::RefreshGraphs(int value) {
	this->CurrentPlot_ = value;
	if((0 <= this->CurrentPlot_) 
		&& (this->CurrentPlot_ < this->DataManager_.GetMaxSets())) {

			// Remove all the previous data in the plots.
			for(int i = 0, j = this->UI_.Plots.size(); i < j; i++)
				this->UI_.Plots[i]->GetGraph()->Clear();

			// Localize data files.
			auto currentSnapshot = this->DataManager_.GetSnapshotData(this->CurrentPlot_);
			auto rpk = this->DataManager_.GetRPKData();

			// Store data into their respective plots.
			this->UI_.IonRadius->AddPlot(currentSnapshot);
			this->UI_.DensityRadius->AddPlot(currentSnapshot);
			this->UI_.TempRadius->AddPlot(currentSnapshot);
			this->UI_.WallRadTime->AddPlot(rpk);

			// Refresh to redraw the plots.
			for(int i = 0, j = this->UI_.Plots.size(); i < j; i++) {
				this->UI_.Plots[i]->GetGraph()->Refresh();
				//this->UI_.Plots[i]->GetGraph()->ResetView();
			}

			// Display the number of the current plot in the line edit.
			this->UI_.CurrentSnapshotLineEdit->setText(QString().setNum(value));
			this->UI_.CurrentSnapshotLineEdit->setAlignment(Qt::AlignRight);

			// Set the position of the slider to the value of the current plot.
			this->UI_.SeekSlider->setValue(this->CurrentPlot_);

			// Write certain averages and maximums to the line edits.
			
			this->UI_.TimeLineEdit->setText(QString().setNum(currentSnapshot.GetSimulationTime()));
 			this->UI_.WallRadiusLineEdit->setText(QString().setNum(currentSnapshot.GetWallRadius()));
			//UI_.WallVelocityLineEdit->setText(QString().setNum(currentSnapshot.GetWallRadius()));
			this->UI_.MaxPressureLineEdit->setText(QString().setNum(currentSnapshot.GetMaxPressure()));
			this->UI_.AveragePressureLineEdit->setText(QString().setNum(currentSnapshot.GetAvgPressure()));
			this->UI_.MaxTemperatureLineEdit->setText(QString().setNum(currentSnapshot.GetMaxTemperature()));
			this->UI_.AverageTemperatureLineEdit->setText(QString().setNum(currentSnapshot.GetAvgTemperature()));
			this->UI_.MaxEnergyLineEdit->setText(QString().setNum(currentSnapshot.GetMaxEnergy()));
			this->UI_.AverageEnergyLineEdit->setText(QString().setNum(currentSnapshot.GetAvgEnergy()));
			this->UI_.NumberOfFusionsLineEdit->setText(QString().setNum(currentSnapshot.GetFusionRate()));
			this->UI_.MaxDensityLineEdit->setText(QString().setNum(currentSnapshot.GetMaxDensity()));
			this->UI_.AverageDensityLineEdit->setText(QString().setNum(currentSnapshot.GetAvgDensity()));
        
	} else {
		// Stop the Timer if it is Running
		this->PlotsIterating_ = false;
		if(this->PlotUpdateTimer_->isActive()) this->PlotUpdateTimer_->stop();
		UI_.StartButton->setText("Start");
	}
}

// Allows for the change of states between
// iterating and not iterating through plots.
void DataVisualizer::ToggleIteratingPlots() {
	
	// Invert the previous state.
	if(this->PlotsIterating_) 
		this->PlotsIterating_ = false;
	else if(!this->PlotsIterating_) 
		this->PlotsIterating_ = true;

	// Change the display text of the
	// button and toggle the state of the
	// timer depending on the current state.
	if(this->PlotsIterating_) {
		this->PlotUpdateTimer_->start();
		this->UI_.StartButton->setText("Stop");
	} else {
		this->PlotUpdateTimer_->stop();
		this->UI_.StartButton->setText("Start");
	}
}

// Increase the size of the plots and redraw.
void DataVisualizer::EnlargePlots() {
	if(this->UI_.GetGraphWidth() < MaxPlotSize)
		this->UI_.ChangePlotWidths(this->UI_.GetGraphWidth() + ResizeIncrement);
}

// Decrease the size of the plots and redraw.
void DataVisualizer::ShrinkPlots() {
	if(this->UI_.GetGraphWidth() > MinPlotSize)
		this->UI_.ChangePlotWidths(this->UI_.GetGraphWidth() - ResizeIncrement);
}
#pragma endregion
#pragma region Preference Tab
// Prompts the user for a directory
// that contains simulation data.
void DataVisualizer::UserSetDirectory() {

	// Localize the previous directory, if it exists.
	QString prevDir = "";
	if(this->ProgramSettings_->contains(FileDirectory))
		prevDir = this->ProgramSettings_->value(FileDirectory).toString();

	// Open FileDialog to Prompt User for the Directory of the Simulation
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), prevDir);
		
	// Check if there was a directory referenced.
	if(dir == "")
		return;

	// Change the directory saved to the registry.
	this->ProgramSettings_->setValue(FileDirectory, dir);

	// Sets the line edits for the UI's.
	this->UI_.SimulationDirectoryLineEdit->setText(dir);
	this->StartupUI_.DirectoryLineEdit->setText(dir);

	// Emit signals alerting connected methods of the change.
	emit ChangedDirectory(dir);
	emit ChangedDirectory();
}

// Changes the amount of milliseconds of delay there 
// is between the drawing of one graph and the next.
void DataVisualizer::ChangeInterval(int value) {

	// Check if the interval is non-negative.
	if(value < 0) {
		Util::Print("The refresh interval cannot be a negative number.");
		return;
	}

	// Sets the interval for the timer with the passed value.
	this->PlotUpdateTimer_->setInterval(value);

	// Re-adjust the slider with the correct value.
	this->UI_.RefreshIntervalSlider->setValue(value);

	// Change the line edit used to display the interval.
	const QString label = "%1 Milliseconds";
	this->UI_.RefreshIntervalMSLabel->setText(label.arg(value));
	
	// Change the value stored in the registry.
	this->ProgramSettings_->setValue(RefereshInterval, value);
}

// Changes the type of data and units that are displayed.
void DataVisualizer::ChangeViewMode(int index) {
	switch (index) {
	case ComplexDisplayMode:
		this->UI_.ChangeLabelDisplayMode(index);
		break;
	case SimpleDisplayMode:
		this->UI_.ChangeLabelDisplayMode(index);
		break;
	default:
		break;
	}
}
#pragma endregion
#pragma endregion
#pragma region Helper Methods
// Initialize User Defined Signals and Slots
void DataVisualizer::ConnectWidgets() {
	connect(this->UI_.StartButton, SIGNAL(clicked()), this, SLOT(ToggleIteratingPlots()));
	connect(this->UI_.SeekSlider, SIGNAL(valueChanged(int)), this, SLOT(RefreshGraphs(int)));
	connect(this->UI_.ViewModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeViewMode(int)));
	connect(this->UI_.BrowseDirectoryButton, SIGNAL(clicked()), this, SLOT(UserSetDirectory()));
	connect(this->UI_.DirLoadButton, SIGNAL(clicked()), this, SLOT(StoreData()));
	connect(this->UI_.RefreshIntervalSlider, SIGNAL(valueChanged(int)), this, SLOT(ChangeInterval(int)));
	connect(this->UI_.EnlargeGraphButton, SIGNAL(pressed()), this, SLOT(EnlargePlots()));
	connect(this->UI_.ShrinkGraphButton, SIGNAL(pressed()), this, SLOT(ShrinkPlots()));
	connect(this->PlotUpdateTimer_, SIGNAL(timeout()), this, SLOT(RefreshGraphs()));
	connect(this->StartupUI_.buttonBox, SIGNAL(accepted()), this, SLOT(StoreData()));
	connect(this->StartupUI_.BrowseDirectoryButton, SIGNAL(clicked()), this, SLOT(UserSetDirectory()));
}

// Sets up various UI elements for the program to use.
void DataVisualizer::SetupUI() {

	// Allows for button effects to continue when held down.
	this->UI_.EnlargeGraphButton->setAutoRepeat(true);
	this->UI_.ShrinkGraphButton->setAutoRepeat(true);

	// Bind keyboard keys to each of the buttons, so that they can be used as hotkeys.
	this->UI_.EnlargeGraphButton->setShortcut(QString("="));
	this->UI_.ShrinkGraphButton->setShortcut(QString("-"));

	// Writes tool tips for each button indicating what they do.
	this->UI_.EnlargeGraphButton->setToolTip(QString("Enlarges the plots when pressed. Alternatively, press <b>\"=\"</b> to enlarge."));
	this->UI_.ShrinkGraphButton->setToolTip(QString("Shrinks the plots when pressed. Alternatively, press <b>\"=\"</b> to shrink."));

	// Initialize the numerical range of the refresh interval slider.
	this->UI_.RefreshIntervalSlider->setMinimum(MinInterval);
	this->UI_.RefreshIntervalSlider->setMaximum(MaxInterval);

	// Check if the refresh interval is recorded in the registry.
	// If so, grab the value and set it to the slider. Otherwise assign the default.
	if(this->ProgramSettings_->contains(RefereshInterval))
		this->ChangeInterval(this->ProgramSettings_->value(RefereshInterval).toInt());
	else
		this->ChangeInterval(DefaultInterval);

	// Localize the previous directory, if it exists.
	QString dir = "";
	if(this->ProgramSettings_->contains(FileDirectory))
		dir = this->ProgramSettings_->value(FileDirectory).toString();

	// Sets the line edits for the UI's.
	this->UI_.SimulationDirectoryLineEdit->setText(dir);
	this->StartupUI_.DirectoryLineEdit->setText(dir);
}
#pragma endregion