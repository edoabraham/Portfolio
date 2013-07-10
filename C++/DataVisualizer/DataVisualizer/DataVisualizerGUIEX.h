// SimulationPlotGUI_UI.h - Simulation plot GUI class expansion
// Written By Jesse Z. Zhong
#ifndef __DataVisualizerGUIEX_H__
#define __DataVisualizerGUIEX_H__
#pragma region Includes
#include "stdafx.h"
#include "ProjectSettings.h"
#include "ui_DataVisualizerGUI.h"
#include "Utilities.h"
#include "IonizationVsRadius.h"
#include "DensityVsRadius.h"
#include "TemperatureVsRadius.h"
#include "WallRadiusVsTime.h"
#include "ParticleDistributionPlot.h"
#include "CollisionEnergyPlot.h"
#include "StringResource.h"
#pragma endregion
#pragma region Graph Constants

// Default graph dimensions
const int DefaultWidth = 360;
#pragma endregion
using namespace std;
using namespace Ui;
	
// Extends the primary GUI window to have the intended items and behaviors.
class DataVisualizerGUIEX : public DataVisualizerGUIClass {
public:
	// Plots
	IonizationVsRadiusGraph IonizationVsRadiusGraph_;
	DensityVsRadiusGraph DensityVsRadiusGraph_;
	TemperatureVsRadiusGraph TemperatureVsRadiusGraph_;
    WallRadiusVsTimeGraph WallRadiusVsTimeGraph_;
    ParticleDistributionPlot ParticleDistributionPlot_;
    CollisionEnergyPlot CollisionEnergyPlot_;
        
    // Initializes the UI in this scope
    void InitializeUI(QMainWindow *parent) {
            
        // Setup UI
        this->setupUi(parent);
            
        // Setup the graphs
        this->SetupGraphs(parent);
            
        // Start labels in complex mode
		this->ChangeLabelDisplayMode(COMPLEX_DISPLAY_MODE);
            
        // Initialize graph size
        this->GraphSize_ = DefaultWidth;
    }

    // Sets up plots with all the default settings
	void SetupGraphs(QMainWindow *parent) {
		this->InitializeIonizationVsRadius(this->GraphScrollArea);
		this->InitializeDensityVsRadius(this->GraphScrollArea);
		this->InitializeTemperatureVsRadius(this->GraphScrollArea);
		this->InitializeWallRadiusVsTime(this->GraphScrollArea);
		this->ChangeGraphWidths(this->GraphSize_);

		this->GraphLayoutArea->addWidget(this->IonizationVsRadiusGraph_.GetGraph());
		this->IonizationVsRadiusGraph_.GetGraph()->setMinimumHeight(600);
		this->IonizationVsRadiusGraph_.GetGraph()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		this->GraphLayoutArea->addWidget(this->DensityVsRadiusGraph_.GetGraph());
		this->GraphLayoutArea->addWidget(this->TemperatureVsRadiusGraph_.GetGraph());
		this->GraphLayoutArea->addWidget(this->WallRadiusVsTimeGraph_.GetGraph());

        // Set the scroll area of parent widget
		//GraphAreaScroll->setBackgroundRole(QPalette::Light);
	}

	// Initializes density vs radius graph
	void InitializeDensityVsRadius(QWidget* parent) {
		this->DensityVsRadiusGraph_.GetGraph()->setParent(parent);
		this->DensityVsRadiusGraph_.InitializeGraph(QRect(),
			"Radius", "Density");
	}

	// Initializes temperature vs radius graph
	void InitializeTemperatureVsRadius(QWidget* parent) {
		this->TemperatureVsRadiusGraph_.GetGraph()->setParent(parent);
		this->TemperatureVsRadiusGraph_.InitializeGraph(QRect(),
			"Radius", "Temperature");
	}

	// Initializes ionization vs radius graph
	void InitializeIonizationVsRadius(QWidget* parent) {
		this->IonizationVsRadiusGraph_.GetGraph()->setParent(parent);
		this->IonizationVsRadiusGraph_.InitializeGraph(QRect(),
			"Radius", "Ionization %");
	}
        
    // Initialize wall radius vs time graph
    void InitializeWallRadiusVsTime(QWidget* parent) {
        this->WallRadiusVsTimeGraph_.GetGraph()->setParent(parent);
        this->WallRadiusVsTimeGraph_.InitializeGraph(QRect(),
			"Time", "Wall Radius");
    }
        
    // Change the width of all the graphs
    void ChangeGraphWidths(int width) {
        if(width < 0)
            throw "Graph width cannot be a negative number";

		int height = this->Height(width);
            
        this->DensityVsRadiusGraph_.SetGeometry(QRect(0, 0, width, height));
        this->TemperatureVsRadiusGraph_.SetGeometry(QRect(0, 0, width, height));
        this->IonizationVsRadiusGraph_.SetGeometry(QRect(0, 0, width, height));
        this->WallRadiusVsTimeGraph_.SetGeometry(QRect(0, 0, width, height));
        this->ParticleDistributionPlot_.setGeometry(QRect(0, 0, width, height));
        this->CollisionEnergyPlot_.setGeometry(QRect(0, 0, width, height));

        this->GraphSize_ = width;
    }
        
    // Changes the displayed labels depending on the user's mode choice
    void ChangeLabelDisplayMode(int mode) {
        switch(mode) {
            // Complex mode
            case COMPLEX_DISPLAY_MODE:
            {
                TimeLabel->setText(SRC_COMPLEX_TIME);
                WallRadiusLabel->setText(SRC_COMPLEX_WALL_RADIUS);
                WallVelocityLabel->setText(SRC_COMPLEX_WALL_VELOCITY);
                MaxPressureLabel->setText(SRC_COMPLEX_MAX_PRESSURE);
                AveragePressureLabel->setText(SRC_COMPLEX_AVG_PRESSURE);
                MaxTemperatureLabel->setText(SRC_COMPLEX_MAX_TEMPERATURE);
                AverageTemperatureLabel->setText(SRC_COMPLEX_AVG_TEMPERATURE);
                MaxEnergyLabel->setText(SRC_COMPLEX_MAX_ENERGY);
                AverageEnergyLabel->setText(SRC_COMPLEX_AVG_ENERGY);
                NumberOfFusionsLabel->setText(SRC_COMPLEX_NUM_OF_FUSIONS);
                MaxDensityLabel->setText(SRC_COMPLEX_MAX_DENSITY);
                AverageDensityLabel->setText(SRC_COMPLEX_AVG_DENSITY);
            }
                break;
            case SIMPLE_DISPLAY_MODE:
            {
                TimeLabel->setText(SRC_SIMPLE_TIME);
                WallRadiusLabel->setText(SRC_SIMPLE_WALL_RADIUS);
                WallVelocityLabel->setText(SRC_SIMPLE_WALL_VELOCITY);
                MaxPressureLabel->setText(SRC_SIMPLE_MAX_PRESSURE);
                AveragePressureLabel->setText(SRC_SIMPLE_AVG_PRESSURE);
                MaxTemperatureLabel->setText(SRC_SIMPLE_MAX_TEMPERATURE);
                AverageTemperatureLabel->setText(SRC_SIMPLE_AVG_TEMPERATURE);
                MaxEnergyLabel->setText(SRC_SIMPLE_MAX_ENERGY);
                AverageEnergyLabel->setText(SRC_SIMPLE_AVG_ENERGY);
                NumberOfFusionsLabel->setText(SRC_SIMPLE_NUM_OF_FUSIONS);
                MaxDensityLabel->setText(SRC_SIMPLE_MAX_DENSITY);
                AverageDensityLabel->setText(SRC_SIMPLE_AVG_DENSITY);
            }
                break;
            default:
            {
                TimeLabel->setText(SRC_COMPLEX_TIME);
                WallRadiusLabel->setText(SRC_COMPLEX_WALL_RADIUS);
                WallVelocityLabel->setText(SRC_COMPLEX_WALL_VELOCITY);
                MaxPressureLabel->setText(SRC_COMPLEX_MAX_PRESSURE);
                AveragePressureLabel->setText(SRC_COMPLEX_AVG_PRESSURE);
                MaxTemperatureLabel->setText(SRC_COMPLEX_MAX_TEMPERATURE);
                AverageTemperatureLabel->setText(SRC_COMPLEX_AVG_TEMPERATURE);
                MaxEnergyLabel->setText(SRC_COMPLEX_MAX_ENERGY);
                AverageEnergyLabel->setText(SRC_COMPLEX_AVG_ENERGY);
                NumberOfFusionsLabel->setText(SRC_COMPLEX_NUM_OF_FUSIONS);
                MaxDensityLabel->setText(SRC_COMPLEX_MAX_DENSITY);
                AverageDensityLabel->setText(SRC_COMPLEX_AVG_DENSITY);
            }
                break;
        }
    }
        
    // Returns the Current Graph Size
    int GetGraphWidth() const {
        return GraphSize_;
    }
        
private:
        
    // Calculates appropriate graph height using the width and PHI
    int Height(int width) {
        return (int) (width / Util::PHI);
    }
        
    // Stores the graph width to memory every time there is a size update
    int GraphSize_;
};

#endif // End : DataVisualizerGUIEX.h
