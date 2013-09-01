// SimulationPlotGUI_UI.h - Simulation plot GUI class expansion
// Written By Jesse Z. Zhong
#ifndef __Data_Visualizer_GUI_EX_H__
#define __Data_Visualizer_GUI_EX_H__
#pragma region Includes
#include "stdafx.h"
#include "ui_DataVisualizerGUI.h"
#include "Util.h"
#include "DataFile.h"
#include "G_DensityRadius.h"
#include "G_IonizationRadius.h"
#include "G_TempRadius.h"
#include "G_WallRadTime.h"
#include "GL_CollideEnergy.h"
#include "GL_ParticleDist.h"
#include "StringResource.h"
using namespace std;
using namespace Ui;
#pragma endregion
#pragma region Graph Constants
// The default width of individual plots.
const int DefaultWidth = 360;

// The padding used between the drawing of each plot.
const int PlotPadding = 40;

// The space between the left edge of 
// the plot area and the left most plots.
const int PlotLeftMargin = 4;

// The space between the top edge of
// the plot area and the top most plots.
const int PlotTopMargin = 4;

// Indicates how many graphs can be
// arranged in a row in the graph area.
const int PlotRowSize = 2;
#pragma endregion
// Extends the primary GUI window to have the intended items and behaviors.
class DataVisualizerGUIEX : public DataVisualizerGUIClass {
public:
	// Plots
	G_IonizationRadius* IonRadius;
	G_DensityRadius* DensityRadius;
	G_TempRadius* TempRadius;
    G_WallRadTime* WallRadTime;
    GL_ParticleDist* PartDist;
    GL_CollideEnergy* CollideEnergy;

	// Reference to all of the plots.
	vector<Graph<DataFile>*> Plots;

	// Destructor
	~DataVisualizerGUIEX() {
		delete this->IonRadius;
		delete this->DensityRadius;
		delete this->TempRadius;
		delete this->WallRadTime;
		delete this->PartDist;
		delete this->CollideEnergy;
	}
        
    // Initializes the UI in this scope
    void InitializeUI(QMainWindow *parent) {
            
        // Start labels in complex mode.
		this->ChangeLabelDisplayMode(ComplexDisplayMode);
            
        // Initialize graph size.
        this->GraphSize_ = DefaultWidth;

		// Setup the graphs.
		this->SetupGraphs(parent);
    }

    // Sets up plots with all the default settings
	void SetupGraphs(QMainWindow *parent) {

		// Initialize the plots.
		this->Plots = vector<Graph<DataFile>*>();
		this->Plots.push_back((Graph<DataFile>*)(this->IonRadius = new G_IonizationRadius(this->PlotArea)));
		this->Plots.push_back((Graph<DataFile>*)(this->DensityRadius = new G_DensityRadius(this->PlotArea)));
		this->Plots.push_back((Graph<DataFile>*)(this->TempRadius = new G_TempRadius(this->PlotArea)));
		this->Plots.push_back((Graph<DataFile>*)(this->WallRadTime = new G_WallRadTime(this->PlotArea)));

		// Initialize the plots with label names.
		this->IonRadius->InitializeGraph(QRect(), "Radius", "Ionization %");
		this->DensityRadius->InitializeGraph(QRect(), "Radius", "Density");
		this->TempRadius->InitializeGraph(QRect(), "Radius", "Temperature");
		this->WallRadTime->InitializeGraph(QRect(), "Time", "Wall Radius");

		// Initialize shared information for all of the plots.
		for(int i = 0, j = this->Plots.size(); i < j; i++) {

			// Assign the parent of all of the plots.
			this->Plots[i]->GetGraph()->setParent(this->PlotArea);

			// Change the size policy of the plots.
			this->Plots[i]->GetGraph()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		}

		// Change the widths of all the plots.
		this->ChangePlotWidths(this->GraphSize_);

		// Initialize the low level plots.
		this->PartDist = new GL_ParticleDist();
		this->CollideEnergy = new GL_CollideEnergy();
	}
        
    // Change the width of all the plots.
    void ChangePlotWidths(int width) {

		// Check if the passed width is a non negative number.
        if(width < 0)
            throw "Graph width cannot be a negative number";

		// Change the height and width of all of the plots.
		int height = this->Height(width);
		int numOfPlots = this->Plots.size();
		for(int i = 0; i < numOfPlots; i++) {

			// Calculate the indices in the plot area
			// "table" where this plot will be drawn in.
			int rowIndex = i / PlotRowSize;
			int colIndex = i % PlotRowSize;

			// Assign the newly calculated geometry.
			this->Plots[i]->GetGraph()->setGeometry(
				(PlotLeftMargin + (colIndex * (PlotPadding + width))),
				(PlotTopMargin + (rowIndex * (PlotPadding + height))), 
				width, height);
		}

		// Recalculate the dimensions of the scroll area
		// according to the number of plots in the area.
		this->PlotArea->setGeometry(0, 0,
			(PlotLeftMargin + (PlotPadding + width) * PlotRowSize),
			(PlotTopMargin + (ceil(numOfPlots / PlotRowSize)) * height + PlotPadding));

		// Assign the size shared by the plots.
        this->GraphSize_ = width;
    }
        
    // Changes the displayed labels depending on the user's mode choice
    void ChangeLabelDisplayMode(int mode) {
        switch(mode) {
            // Complex mode
            case ComplexDisplayMode:
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
            case SimpleDisplayMode:
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
        
    // Returns the width of the plots.
    int GetGraphWidth() const {
        return this->GraphSize_;
    }
        
private:
        
    // Calculates appropriate graph height using the width and PHI.
    int Height(int width = DefaultWidth) {
        return (int) (width / Util::PHI);
    }
        
    // Stores the graph width to memory every time there is a size update.
    int GraphSize_;
};

#endif // End : DataVisualizerGUIEX.h
