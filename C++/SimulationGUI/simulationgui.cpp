/// SimulationGUI.cpp - SimulationGUI Main Window Class Methods Implementation
/// Written by Jesse Z. Zhong

#include "simulationgui.h"

// Tree Path for Environment Variables
const std::string ENVIRONMENT_PATH = "Environment.";

// Tree Path for Atomic Particles
const std::string PARTICLE_PATH = "Particles.";

// Set the Time Resolution
const int TIME_RESOLUTION = 100;

//// Declare Default Number Precision
//const int DEFAULT_PRECISION = 4;
//
//// Declare Default QString to Number Format
//const char DEFAULT_QSRT_TO_NUM_FORMAT = 'g';


// Default and Init Constructor
SimulationGUI::SimulationGUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags) {
	ui.setupUi(this);

	// Connect the Timer with UpdateGUITImer()
	connect(&SimulationTimerProc_, SIGNAL(timeout()), this, SLOT(UpdateTime()));
	connect(&SimulationTimerProc_, SIGNAL(timeout()), this, SLOT(UpdateGUITimer()));

	// Connect the "Start" Button to the StartSimulation() Method
	connect(ui.StartButton, SIGNAL(clicked()), this, SLOT(StartSimulation()));

	// Connect the "Change Directory to .." Button to the SetSimulationDirectory() Method
	connect(ui.ChangeDirectoryToButton, SIGNAL(clicked()), this, SLOT(SetSimulationDirectory()));

	// Connect the "Load Parameters from File" Button to the LoadParamFromFile() Method
	connect(ui.LoadParametersFromFileButton, SIGNAL(clicked()), this, SLOT(LoadParamFromFile()));

	// Connect the "Save Current Parameters" Button to the SaveParamToFile() Method
	connect(ui.SaveCurrentParametersButton, SIGNAL(clicked()), this, SLOT(SaveParamToFile()));

	// Connect the "Gas 1" Edit Line Box to UpdateGasBoxes()
	connect(ui.Gas1LineText, SIGNAL(editingFinished()), this, SLOT(UpdateGasBoxes()));

	// Connect the "Gas 2" Edit Line Box to UpdateGasBoxes()
	connect(ui.Gas2LineText, SIGNAL(editingFinished()), this, SLOT(UpdateGasBoxes()));

	// Connect All Parameters Box to UpdateParamters()
	connect(ui.ConeAngleLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.TemperatureLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.WallTemperatureLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.EquilibriumRadiusLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.DriverPressureLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.FrequencyLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.InitialTimeLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.InitialRadiusLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));
	connect(ui.InitialVelocityLineText, SIGNAL(editingFinished()), this, SLOT(UpdateParameters()));

	// Connect Gas Drop Down Boxes to UpdateGasComp()
	connect(ui.GasComboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGasComp()));
	connect(ui.GasComboBox2, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGasComp()));
}

// Destructor
SimulationGUI::~SimulationGUI() {

}

// Starts the Simulation
void SimulationGUI::StartSimulation() {

	// Attempt to Run the Simulation; If Successful, Start Timer
	if(SimulationController_.RunSimulation())
		StartTimer();

	// If Running, Change "Start" Button to "Stop"
	ChangeStartButtonName();




	// Connect the Start Button to the StopSimulation() Method
	connect(ui.StartButton, SIGNAL(clicked()), this, SLOT(StopSimulation()));

	// Disconnect the Start Button from the StartSimulation() Method
	disconnect(ui.StartButton, SIGNAL(clicked()), this, SLOT(StartSimulation()));
}

// Stops the Simulation if the Simulation is Already Running
void SimulationGUI::StopSimulation() {

	// Attempt to Stop the Simulation; If Successful, Pause Timer
	if(SimulationController_.StopSimulation())
		PauseTimer();

	// If Not Running, Change "Stop" Button to "Start"
	ChangeStartButtonName();



	// Connect the Start Button to the StartSimulation() Method
	connect(ui.StartButton, SIGNAL(clicked()), this, SLOT(StartSimulation()));

	// Disconnect the Start Button from the StopSimulation() Method
	disconnect(ui.StartButton, SIGNAL(clicked()), this, SLOT(StopSimulation()));
}

// Sets the Directory of the Simulation
void SimulationGUI::SetSimulationDirectory() {

	// Open FileDialog to Prompt User for the Directory of the Simulation
	// Return the File Name
	QString directoryName = QFileDialog::getExistingDirectory();

	// Check if Name Exists
	if(directoryName != NULL) {

		// Store the Directory Name
		SimulationController_.SetDirectory(directoryName.toStdString());

		// Update the Box
		UpdateChangeDirBox();

		// Update Action Log
		UpdateActionLog("Simulation Directory set to<br>" + directoryName);
	}
}

// Reads File from FileDialog and Parses it for Data
void SimulationGUI::LoadParamFromFile() {

	// Open FileDialog to Prompt User for the File Name with the Parameters
	// Returns the File Name
	// Selected Filter for Only JSON Files [text File Support Later, Maybe]
	QString fileName = QFileDialog::getOpenFileName(0, tr("Select file to open"), QString(), tr("JSON Files (*.json)"));

	// Checks if There was a File Looked Up and if it's Valid; Also, Check if
	// the Dialog was Cancelled or Not
	// If it was Cancelled, it Should Not Be Allowed to Change Anything in the Program
	if(fileName != NULL) {

		// Read the JSON File
		// Put a Check for the Extension Name [Yes, I will be Picky]
		if(fileName.endsWith(".json", Qt::CaseInsensitive)) {

			// Pass File Name to ReadJSON() After Converting to std::string
			SimulationController_.ReadJSON(fileName.toStdString());

			#ifdef BUILD_WITH_BOOST
			// Fill in the Read Parameters
			FillParameters(SimulationController_.GetData());
			#endif

			// Update Action Log
			UpdateActionLog("Parameter JSON file loaded from<br>" + fileName);
		} 
	}
}

// Saves Parameters to File Using File Dialog to Navigate for
// the Directory and the File Name
void SimulationGUI::SaveParamToFile() {

	// Select File Name and Where to Save
	QString fileName = QFileDialog::getSaveFileName(0, tr("Save Parameters"), QString(), tr("JSON Files (*.json)"));

	// Check if File Name was Looked Up and Stored
	if(fileName != NULL) {

		// Store Whether or Not the User wants to Overwrite an Existing File
		bool okayToWrite = true;

		// Check if File Exists
		std::ifstream checkMyFile(fileName.toStdString().c_str());
		if(checkMyFile.is_open()) {

			// Prompt User
			// Insert Dialog Box Here

			// If Cancel is Hit, Set Writing to False
			if(false)
				okayToWrite = false;
		}

		// Close File Stream
		checkMyFile.close();

		// Write to File
		if(okayToWrite)
			SimulationController_.WriteJSON(fileName.toStdString());

		// Update Action Log
		UpdateActionLog("Parameters successfully saved to<br>" + fileName);
	}
}

// Updates Gas Edit Line Boxes Depending User Input
void SimulationGUI::UpdateGasBoxes() {
	
	// Legacy	
	//// Find the Ratio of the Current Selected Gas in Respect to the Other Gas
	//double gas1Ratio = ui.Gas1LineText->text().toDouble() / 
	//	(ui.Gas1LineText->text().toDouble() + ui.Gas2LineText->text().toDouble());

	//// Find Second Gas Ratio
	//double gas2Ratio = 1 - gas1Ratio;

	// Find the First Gas Ratio
	double gas1Ratio = ui.Gas1LineText->text().toDouble() / 1;

	// Find the Second Gas Ratio
	double gas2Ratio = 0.0;
	if(gas1Ratio <= 1) gas2Ratio = 1 - gas1Ratio;

	// Update the Second Gas Box
	ui.Gas2LineText->setText(QString().setNum(gas2Ratio, 'g', 6));

	// Store into Simulation
	SimulationController_.SetGasRatio(0, gas1Ratio);
	SimulationController_.SetGasRatio(1, gas2Ratio);
}

// Update Gas Compositions
void SimulationGUI::UpdateGasComp() {

	// Store Values to Simulation
	SimulationController_.SetGasComp(0, ui.GasComboBox1->currentIndex());
	SimulationController_.SetGasComp(1, ui.GasComboBox2->currentIndex());
}

// Updates All of the Parameters
void SimulationGUI::UpdateParameters() {

	// Set the Value Depending on Arguments Input
	SimulationController_.SetParameter(CONE_ANGLE, ui.ConeAngleLineText->text().toDouble());
	SimulationController_.SetParameter(TEMPERATURE, ui.TemperatureLineText->text().toDouble());
	SimulationController_.SetParameter(WALL_TEMPERATURE, ui.WallTemperatureLineText->text().toDouble());
	SimulationController_.SetParameter(EQUILIBRIUM_RADIUS, ui.EquilibriumRadiusLineText->text().toDouble());
	SimulationController_.SetParameter(DRIVER_PRESSURE, ui.DriverPressureLineText->text().toDouble());
	SimulationController_.SetParameter(FREQUENCY, ui.FrequencyLineText->text().toDouble());
	SimulationController_.SetParameter(INITIAL_TIME, ui.InitialRadiusLineText->text().toDouble());
	SimulationController_.SetParameter(INITIAL_RADIUS, ui.InitialRadiusLineText->text().toDouble());
	SimulationController_.SetParameter(INITIAL_VELOCITY, ui.InitialVelocityLineText->text().toDouble());

	#ifdef DEBUG_MODE
	qDebug() << QString(SimulationController_.PrintParams().c_str());
	#endif
}

// Changes the Name of the Start Button Depending on the State
// of the Simulation
void SimulationGUI::ChangeStartButtonName() {
	if(SimulationController_.GetRunState()) ui.StartButton->setText("Stop");
	else if(!SimulationController_.GetRunState()) ui.StartButton->setText("Start");

	// Update Action Log
	if(SimulationController_.GetRunState()) UpdateActionLog("Simulation was started.");
	else if(!SimulationController_.GetRunState()) UpdateActionLog("Simulation was stopped.");

	// Print Result
	if(SimulationController_.GetRunState()) qDebug() << "Running\n";
	else if(!SimulationController_.GetRunState()) qDebug() << "Not Running\n";
}

// Updates the Change Directory Box with the Directory
void SimulationGUI::UpdateChangeDirBox() {
	ui.SimulationDirectoryBox->setText(QString(SimulationController_.GetDirectory().c_str()));
}

// Updates the Action Log Box
void SimulationGUI::UpdateActionLog(QString line) {
	
	// Grab the Local Time
	time_t localTime = time(NULL);

	// Add Onto to the Action Log String without Overwriting
	char* timeCString = asctime(localtime(&localTime));
	timeCString[strlen(timeCString) - 1] = 0;
	ActionLogString_ += "<b>" + QString(timeCString) + "</b>:<br>" + line + "<br>";

	// Write to the Action Log and Scroll Down
	ui.ActionLogBox->setText(ActionLogString_);
	ui.ActionLogBox->verticalScrollBar()->setValue(ui.ActionLogBox->verticalScrollBar()->maximum());
}

#ifdef BUILD_WITH_BOOST
// Fills a Single Parameter According to Specifications
void SimulationGUI::FillParameters(boost::property_tree::ptree& data) {

	// Display Cone Angle in Box
	FillSingleParam(data, ENVIRONMENT_PATH + "ConeAngle", ui.ConeAngleLineText);

	// Display Temperature in Box
	FillSingleParam(data, ENVIRONMENT_PATH + "Temperature", ui.TemperatureLineText);

	// Display Wall Temperature in Box
	FillSingleParam(data, ENVIRONMENT_PATH + "WallTemp", ui.WallTemperatureLineText);

	// Display Equilibrium Radius in Box
	FillSingleParam(data, ENVIRONMENT_PATH +  "RO", ui.EquilibriumRadiusLineText);

	// Display Pressure Driver in Box
	FillSingleParam(data, ENVIRONMENT_PATH +  "Pd", ui.DriverPressureLineText);

	// Display Frequency in Box
	FillSingleParam(data, ENVIRONMENT_PATH +  "Frequency", ui.FrequencyLineText);

	// Display Initial Time in Box
	FillSingleParam(data, ENVIRONMENT_PATH +  "Tini", ui.InitialTimeLineText);

	// Display Initial Radius in Box
	FillSingleParam(data, ENVIRONMENT_PATH +  "Rini", ui.InitialRadiusLineText);

	// Display Initial Velocity in Box
	FillSingleParam(data, ENVIRONMENT_PATH +  "Vini", ui.InitialVelocityLineText);

	// Display Gas1 in Box
	FillSingleParam(data, PARTICLE_PATH + "AtomicParts", ui.Gas1LineText, 0);

	// Display Gas2 in Box
	FillSingleParam(data, PARTICLE_PATH + "AtomicParts", ui.Gas2LineText, 1);
}

// Fills a Single Parameter According to Specifications
void SimulationGUI::FillSingleParam(boost::property_tree::ptree& data, std::string name, QLineEdit* lineEditBox, int indexVal) {

	// Create String to Store Result
	std::string result;

	// >> Dirty Hack <<
	if(name.find(PARTICLE_PATH) != std::string::npos) {
		// Create Vector as Temporary Storage for JSON Array
		// NOTE: This needs to be revised somehow.
		std::vector<std::string> tempStorage = ParseArray<std::string>(data.get_child(name));

		// Check and Pull Value
		if(!tempStorage.empty() && (indexVal < tempStorage.size()))
			result = tempStorage[indexVal];
	} else {
		// Store the Required Data
		/*std::string */result = data.get<std::string>(name, "0");
	}

	// Display Cone Angle in Box
	lineEditBox->setText(QString(result.c_str()));
}
#endif

// Start the Timer
void SimulationGUI::StartTimer() {
	SimulationTimerProc_.start(TIME_RESOLUTION);
	AccurateTimer_.StartTimer();
}

// Pause the Timer
void SimulationGUI::PauseTimer() {
	AccurateTimer_.PauseTimer();
}

// Updates the Time
void SimulationGUI::UpdateTime() {
	AccurateTimer_.Update();
}

// Update the GUI LCD Timer
void SimulationGUI::UpdateGUITimer() {

	// Create String to Store the Prepared Output
	QString theTime = AccurateTimer_.QGetHours() + ":" + AccurateTimer_.QGetMinutes() + ":" + 
		AccurateTimer_.QGetSeconds() + ":" + AccurateTimer_.QGetMilliseconds();

	// Change the Boxes Value
	ui.GUITimerBox->setText(theTime);
	ui.GUITimerBox->setAlignment(Qt::AlignCenter);

	// Set Font
	QFont Font0;
	Font0.setPointSize(12);
	Font0.setWeight(80);
	ui.GUITimerBox->setFont(Font0);
}