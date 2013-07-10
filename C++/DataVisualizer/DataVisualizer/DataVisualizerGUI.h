/// simulationplotgui.h - GUI Class Implementation
/// Written By Jesse Z. Zhong
#ifndef __SIMULATIONPLOTGUI_H__
#define __SIMULATIONPLOTGUI_H__

#include "stdafx.h"
#include "ProjectSettings.h"
#include <QMainWindow>
#include "ui_simulationplotgui.h"
#include "DataVisualizerGUIEX.h"
#include "StartupUIEX.h"
#include "DataManager.h"
#include "Configuration.h"
#include "RPK.h"

// Graph Refresh Interval in Milliseconds
extern const int GRAPH_REFRESH_INTERVAL;

class SimulationPlotGUI : public QMainWindow {
	Q_OBJECT
private slots:
    // Updates the File Directory and
    // Reloads All the Data and Graphs
    void UpdateDirectory();
    
    // Opens File Dialog and Changes the
    // File Directory
    void SearchForDirectory();
    
	// Updates and Draws the Graphs
	void RefreshGraphs();

	// Overload with Set Value Built in
	void RefreshGraphs(int value);

	// Updates the Snapshot Line Edit
	void UpdateSnapshotLineEdit(int value);

	// Starts to Play Graphs in Order
	void StartPlayingGraphs();
    
    // Updates Line Edit Data
    void UpdateLineEditData();
    
    // Updates Graph Resolution
    void UpdateGraphResolution(QString width);
    
    // Update Refresh Interval and its Widgets
    void UpdateRefreshInterval(int value);
    
    // Update View Mode Depending on Index Passed
    void UpdateViewMode(int index);
    
    // Enlarges and Updates the Size of the Graphs
    void EnlargeGraphs();
    
    // Shrinks and Updates the Size of the Graphs
    void ShrinkGraphs();
    
    // Responds to a Change in the Program's File Directory
    void SetDirectory(QString value);
    
signals:
    // Emits a Signal when the Files Directory is Changed
    void ChangedDirectory(const QString& value);
    void ChangedDirectory();
    
public:
	// Constructor and Destructor
	SimulationPlotGUI(QWidget *parent = 0);
	~SimulationPlotGUI();

private:
	// Instance of UI Form
	DataVisualizerGUIEX ui;
    
    // Instance of Start Up Dialog
    StartupUIEX StartUpDialog_;
    
    // RPK
    DataRPK RPK_;

	// Graph Refresh Timer
	QTimer GraphUpdateTimer_;

	// Snapshot Manager for Reading
    // and Managing All Snapshot Data
    DataManager DataManager_;
    
    // Configurations Management
    Configuration Configurations_;

	// Current File Number
	int CurrentFileNumber_;

	// Keeps Track if the the
	// Graphs are Playing
	bool GraphsPlaying_;
    
    // Stores All of the Graph Data
    void StoreGraphData();
    
    // Initializes User Defined Signals and Slots
    void InitializeSignalsAndSlots();
    
    // Initialize Graphs with an Empty Data Template
    void InitializeGraphs();
    
    // Initialize Refresh Interval Widgets
    void InitializeRefreshIntervalWidgets();
    
    // Initialize Directory Preference Widgets
    void InitializeDirectoryPreferenceWidgets();
    
    // Initialize View Mode Preference Widgets
    void InitializeViewModePreferenceWidgets();
    
    // Initialize Graph Resize Buttons
    void InitializeGraphResizeButtons();
    
    // Initialize Slider Bar
    void InitializeSliderBar();
    
    // Creates a New Startup Prompt Box
    void CreateStartUpDialog();
};

#endif // SIMULATIONPLOTGUI_H
