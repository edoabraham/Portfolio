/// simulationplotgui.cpp - GUI Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "simulationplotgui.h"

// Graph Refresh Interval in Milliseconds
const int DEFAULT_GRAPH_REFRESH_INTERVAL = 200;
const int MIN_REFRESH_INTERVAL = 100;
const int MAX_REFRESH_INTERVAL = 1000;
const int REFRESH_INTERVAL_INCREMENT = 100;

// Graph Resizing Rules
const int MAX_GRAPH_SIZE = 500;
const int MIN_GRAPH_SIZE = 300;
const int GRAPH_RESIZE_INCREMENT = 10;

// Constructor
SimulationPlotGUI::SimulationPlotGUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags) {
        
        // Load Application Configurations
        Configurations_.ReadConfig();

        // Initializing the UI Forms
        ui.InitializeUI(this);
        
        // Initialize User Defined Signals and Slots
        InitializeSignalsAndSlots();
        
        // Initialize States
        CurrentFileNumber_ = 0;
        GraphsPlaying_ = false;
        
        // Create New Prompt if Necessary
        if(!Configurations_.IsDirectorySet()) {
            CreateStartUpDialog();
        } else {
            // Initalize Empty Data
            UpdateDirectory();
        }

        // * [ Slider Initialization ]
        InitializeSliderBar();
        
        // * [ Graph Update Timer Initialization ]
        // Set Time Out Interval into the Timer
        GraphUpdateTimer_.setInterval(Configurations_.GetRefreshInterval());

        // Connect the Timer with the Graph Refresh Method
        connect(&GraphUpdateTimer_, SIGNAL(timeout()), this, SLOT(RefreshGraphs()));

        // * [ Snapshot Number Line Edit Initialization ]
        // Set Initial Starting Value
        UpdateSnapshotLineEdit(1);

        // Connect the Line Box to the Slider
        connect(ui.SeekSlider, SIGNAL(valueChanged(int)), this, SLOT(UpdateSnapshotLineEdit(int)));

        // * [ Initialize Start Button ]
        // Connect Start Button
        connect(ui.StartButton, SIGNAL(clicked()), this, SLOT(StartPlayingGraphs()));
        
        // * [ Data Line Edit ]
        // Connects Line Edits to Updater Method
        
        // * [ Refresh Interval ]
        // Initiate All Refresh Interval Widgets
        InitializeRefreshIntervalWidgets();
        
        // * [ File Directory ]
        InitializeDirectoryPreferenceWidgets();
        
        // * [ Graph Resize Buttons ]
        InitializeGraphResizeButtons();
        
}

// Destructor
SimulationPlotGUI::~SimulationPlotGUI() {
    
    // Writes a New Configuration File on Exit
    Configurations_.WriteConfig();
}

///
/// SIGNALS & UPDATE METHODS
///

// Updates the File Directory and
// Reloads All the Data and Graphs
void SimulationPlotGUI::UpdateDirectory() {
    
    // Check and Store All Files to the Data Manager
    DataManager_ = DataManager(Configurations_.GetFilesDirectory().toStdString());
    DataManager_.StoreData();
    
    // Read and Store RPK
    RPK_ = RPK();
    RPK_.Parse(Configurations_.GetFilesDirectory().toStdString() + "RPactual.dat");
}

// Opens File Dialog and Changes the
// File Directory
void SimulationPlotGUI::SearchForDirectory() {
    
    // Open FileDialog to Prompt User for the Directory of the Simulation
	QString directoryName = QFileDialog::getExistingDirectory();
    
    // Change the Directory
    SetDirectory(directoryName + QString("/"));
}

// Updates and Draws the Graphs
void SimulationPlotGUI::RefreshGraphs() {

 	// Refresh the Graphs
	RefreshGraphs(CurrentFileNumber_);
    
    // Update Slider and Line Edit
    ui.SeekSlider->setValue(CurrentFileNumber_);
		
 	// Iterate Up
 	if(GraphsPlaying_) CurrentFileNumber_++;
}

// Overload with Set Value Built in
void SimulationPlotGUI::RefreshGraphs(int value) {
	CurrentFileNumber_ = value;
	if(CurrentFileNumber_ < DataManager_.GetMaxNumOfFiles()) {

        // Update the Graphs
        ui.IonizationVsRadiusGraph_.StorePoints(DataManager_.GetSnapshotData(CurrentFileNumber_));
        ui.DensityVsRadiusGraph_.StorePoints(DataManager_.GetSnapshotData(CurrentFileNumber_));
        ui.TemperatureVsRadiusGraph_.StorePoints(DataManager_.GetSnapshotData(CurrentFileNumber_));
        ui.WallRadiusVsTimeGraph_.StorePoints(RPK_.GetSubSection(CurrentFileNumber_));
        ui.ParticleDistributionPlot_.StorePoints(DataManager_.GetSavepointData(CurrentFileNumber_));
        ui.CollisionEnergyPlot_.StorePoints(DataManager_.GetCollisionEnergyData(CurrentFileNumber_));
        
        // Update Line Edit Box
        UpdateLineEditData();
        
	} else {
		// Stop the Timer if it is Running
		GraphsPlaying_ = false;
		if(GraphUpdateTimer_.isActive()) GraphUpdateTimer_.stop();
		ui.StartButton->setText("Start");
	}
}

// Updates the Snapshot Line Edit
void SimulationPlotGUI::UpdateSnapshotLineEdit(int value) {
	ui.CurrentSnapshotLineEdit->setText(QString().setNum(value));
	ui.CurrentSnapshotLineEdit->setAlignment(Qt::AlignRight);
}

// Starts to Play Graphs in Order
void SimulationPlotGUI::StartPlayingGraphs() {
	
	if(GraphsPlaying_) GraphsPlaying_ = false;
	else if(!GraphsPlaying_) GraphsPlaying_ = true;

	if(GraphsPlaying_) {
		GraphUpdateTimer_.start();
		ui.StartButton->setText("Stop");
	} else {
		GraphUpdateTimer_.stop();
		ui.StartButton->setText("Start");
	}
}

// Updates Line Edit Data
void SimulationPlotGUI::UpdateLineEditData() {
    
    QString tempQString;
    // Check for Correct Time
    ui.TimeLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).SimTime));
    ui.WallRadiusLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).BubbleRadius));
    ui.WallVelocityLineEdit->setText(tempQString.setNum(RPK_[CurrentFileNumber_].WallVelocity));
    ui.MaxPressureLineEdit->setText(tempQString.setNum(RPK_[CurrentFileNumber_].Pressure));
    ui.AveragePressureLineEdit->setText(tempQString.setNum(RPK_[CurrentFileNumber_].Pressure));
    ui.MaxTemperatureLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).GetData(SSD_MaxTemperature)));
    ui.AverageTemperatureLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).GetData(SSD_AvgTemperature)));
    ui.MaxEnergyLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).GetData(SSD_MaxEnergy)));
    ui.AverageEnergyLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).GetData(SSD_AvgEnergy)));
    ui.NumberOfFusionsLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).FusionRate));
    ui.MaxDensityLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).GetData(SSD_MaxDensity)));
    ui.AverageDensityLineEdit->setText(tempQString.setNum(DataManager_.GetSnapshotData(CurrentFileNumber_).GetData(SSD_AvgDensity)));
}

// Updates Graph Resolution
void SimulationPlotGUI::UpdateGraphResolution(QString width) {
    ui.ChangeGraphWidths(width.toInt());
}

// Update Refresh Interval Milliseconds Label
void SimulationPlotGUI::UpdateRefreshInterval(int value) {
    QString labelName = QString().setNum(value);
    labelName += " Milliseconds";
    ui.RefreshIntervalSecondsLabel->setText(labelName);
    if(value < 0)
        throw "The graph refresh interval cannot be a negative number";
    GraphUpdateTimer_.setInterval(value);
    Configurations_.SetRefreshInterval(value);
}

// Enlarges and Updates the Size of the Graphs
void SimulationPlotGUI::EnlargeGraphs() {
    if(ui.GetGraphWidth() < MAX_GRAPH_SIZE)
        ui.ChangeGraphWidths(ui.GetGraphWidth() + GRAPH_RESIZE_INCREMENT);
}

// Shrinks and Updates the Size of the Graphs
void SimulationPlotGUI::ShrinkGraphs() {
    if(ui.GetGraphWidth() > MIN_GRAPH_SIZE)
        ui.ChangeGraphWidths(ui.GetGraphWidth() - GRAPH_RESIZE_INCREMENT);
}

// Responds to a Change in the Program's File Directory
void SimulationPlotGUI::SetDirectory(QString value) {
    if(value != Configurations_.GetFilesDirectory()) {
        Configurations_.SetFilesDirectory(value);
        emit ChangedDirectory(value);
        emit ChangedDirectory();
    }
}

///
/// INITIALIZATION METHODS
///

// Initialize User Defined Signals and Slots
void SimulationPlotGUI::InitializeSignalsAndSlots() {
    connect(this, SIGNAL(ChangedDirectory(QString)), this, SLOT(SetDirectory(QString)));
}

// Initialize Refresh Interval Widgets
void SimulationPlotGUI::InitializeRefreshIntervalWidgets() {
    ui.RefreshIntervalSlider->setMinimum(MIN_REFRESH_INTERVAL);
    ui.RefreshIntervalSlider->setMaximum(MAX_REFRESH_INTERVAL);
    connect(ui.RefreshIntervalSlider, SIGNAL(valueChanged(int)), this, SLOT(UpdateRefreshInterval(int)));
    
    // Set the Value to Default
    ui.RefreshIntervalSlider->setValue(Configurations_.GetRefreshInterval());
}

// Initialize Directory Preference Widgets
void SimulationPlotGUI::InitializeDirectoryPreferenceWidgets() {
    ui.SimulationDirectoryLineEdit->setText(Configurations_.GetFilesDirectory());
    connect(ui.BrowseDirectoryButton, SIGNAL(clicked()), this, SLOT(SearchForDirectory()));
    connect(this, SIGNAL(ChangedDirectory(QString)), ui.SimulationDirectoryLineEdit, SLOT(setText(QString)));
    connect(this, SIGNAL(ChangedDirectory()), this, SLOT(UpdateDirectory()));
}

// Initialize Graph Resize Buttons
void SimulationPlotGUI::InitializeGraphResizeButtons() {
    
    // Connect the Methods
    connect(ui.EnlargeGraphButton, SIGNAL(pressed()), this, SLOT(EnlargeGraphs()));
    connect(ui.ShrinkGraphButton, SIGNAL(pressed()), this, SLOT(ShrinkGraphs()));
    
    // Set so the Action Continues when Buttons are Held Down
    ui.EnlargeGraphButton->setAutoRepeat(true);
    ui.ShrinkGraphButton->setAutoRepeat(true);
    
    // Set the Shortcuts for the Buttons
    ui.EnlargeGraphButton->setShortcut(QString("="));
    ui.ShrinkGraphButton->setShortcut(QString("-"));
    
    // Set the Tooltips for the Buttons
    ui.EnlargeGraphButton->setToolTip(QString("Enlarges the Graphs when pressed. Alternatively, press <b>\"=\"</b> to enlarge."));
    ui.ShrinkGraphButton->setToolTip(QString("Shrinks the Graphs when pressed. Alternatively, press <b>\"=\"</b> to shrink."));
}

// Initialize Slider Bar
void SimulationPlotGUI::InitializeSliderBar() {
    
    // Initialize Slider Bar with the Correct Values
    ui.SeekSlider->setMinimum(START_VALUE);
    ui.SeekSlider->setMaximum(DataManager_.GetMaxNumOfFiles());
    
    // Connect Slider
    connect(ui.SeekSlider, SIGNAL(valueChanged(int)), this, SLOT(RefreshGraphs(int)));
}

///
/// DIALOG BOXES
///

// Creates a New Startup Prompt Box
void SimulationPlotGUI::CreateStartUpDialog() {
    QDialog* dialogBox = new QDialog(ui.centralWidget);
    StartUpDialog_.InitializeUI(dialogBox);
    
    // Begin Connections
    connect(StartUpDialog_.DirectoryLineEdit, SIGNAL(textChanged(QString)), this, SLOT(SetDirectory(QString)));
    connect(StartUpDialog_.BrowseDirectoryButton, SIGNAL(clicked()), this, SLOT(SearchForDirectory()));
    connect(this, SIGNAL(ChangedDirectory(QString)), StartUpDialog_.DirectoryLineEdit, SLOT(setText(QString)));
    
    dialogBox->setModal(true);
    dialogBox->show();
    
    if( dialogBox->exec() == QDialog::Accepted ) {
        UpdateDirectory();
    }
    
    delete dialogBox;
}