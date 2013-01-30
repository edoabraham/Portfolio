/// SimulationPlotGUI_UI.h - Simulation Plot GUI Ui Class Expansion
/// Written By Jesse Z. Zhong

#ifndef __SIMULATION_PLOT_GUI_UI_H__
#define __SIMULATION_PLOT_GUI_UI_H__

#include "stdafx.h"
#include "ui_simulationplotgui.h"
#include "Utilities.h"

#include "IonizationVsRadius.h"
#include "DensityVsRadius.h"
#include "TemperatureVsRadius.h"
#include "WallRadiusVsTime.h"
#include "ParticleDistributionPlot.h"
#include "CollisionEnergyPlot.h"

#include "StringResource.h"

// Graph Order
const int ORDER_IONIZATION_VS_RADIUS    = 0;
const int ORDER_DENSITY_VS_RADIUS       = 1;
const int ORDER_TEMPERATURE_VS_RADIUS   = 2;
const int ORDER_WALL_RADIUS_VS_TIME     = 3;
const int ORDER_DISTRIBUTION_PLOT       = 4;
const int ORDER_COLLISION_ENERGY_PLOT   = 5;

// Upper Ranges [Temporary]
const double RADIUS_UPPER = 4.8e-5;
const double DENSITY_UPPER = 1.0e+24;
const double TEMPERATURE_UPPER = 8100.0;
const double IONIZATION_UPPER = 100.0;

// Default Graph Dimensions
const int DEFAULT_WIDTH = 360;
const int DEFAULT_PADDING = 10;

// Margins
const int LEFT_MARGIN = 4;
const int TOP_MARGIN = 4;

// Graph Orientation Values
const int NUM_OF_COLUMNS = 2;

// Number of Graphs
const int NUM_OF_GRAPHS = 6;

using namespace std;

	namespace Ui {
	/// This Expansion is Pseudo Independent in the Sense
	/// that Changes Made to the Original Base Class
	/// will Not Destroy Any Coded Additions
	/// (The Qt Designer Periodically Overwrites the    
	/// Default UI Class; Any Additions Directly to that
	/// Class are Doomed to be Erased Sooner or Later)
	class SimulationPlotGUI_UI : public SimulationPlotGUIClass {
	public:
		// Graphs
		IonizationVsRadiusGraph IonizationVsRadiusGraph_;
		DensityVsRadiusGraph DensityVsRadiusGraph_;
		TemperatureVsRadiusGraph TemperatureVsRadiusGraph_;
        WallRadiusVsTimeGraph WallRadiusVsTimeGraph_;
        ParticleDistributionPlot ParticleDistributionPlot_;
        CollisionEnergyPlot CollisionEnergyPlot_;
        
        // Initializes the UI in this Scope
        void InitializeUI(QMainWindow *parent) {
            
            // Setup UI
            setupUi(parent);
            
            // Setup the Graphs
            SetupGraphs(parent);
            
            // Start Labels in Complex Mode
            ChangeLabelDisplayMode(COMPLEX_DISPLAY_MODE);
            
            // Initialize Graph Size
            GraphSize_ = DEFAULT_WIDTH;
        }

        // Sets Up Graphs with All the Default Settings
		void SetupGraphs(QMainWindow *parent) {
            InitializeIonizationVsRadius();
			InitializeDensityVsRadius();
			InitializeTemperatureVsRadius();
            InitializeWallRadiusVsTime();
            InitializeParticleDistributionPlot();
            InitializeCollisionEnergyPlot();
            
            // Set the Scroll Area of Parent Widget
            QScrollArea* GraphAreaScroll = new QScrollArea();
            ChangeScrollArea();
            GraphAreaScroll->setParent(GraphsTab);
            GraphAreaScroll->setGeometry(0, 0, 800, 510);
            GraphAreaScroll->setBackgroundRole(QPalette::Light);
            GraphAreaScroll->setWidget(GraphAreaWidget);
		}

		// Initializes Density Vs Radius Graph
		void InitializeDensityVsRadius() {
			DensityVsRadiusGraph_.GetGraph()->setParent(GraphAreaWidget);
			DensityVsRadiusGraph_.InitializeGraph(GenerateGeometry(ORDER_DENSITY_VS_RADIUS),
				"Radius", "Density", 0.0, RADIUS_UPPER, 0.0, DENSITY_UPPER);
			
		}

		// Initializes Temperature Vs Radius Graph
		void InitializeTemperatureVsRadius() {
			TemperatureVsRadiusGraph_.GetGraph()->setParent(GraphAreaWidget);
			TemperatureVsRadiusGraph_.InitializeGraph(GenerateGeometry(ORDER_TEMPERATURE_VS_RADIUS),
				"Radius", "Temperature", 0.0, RADIUS_UPPER, 0.0, TEMPERATURE_UPPER);
			
		}

		// Initializes Ionization Vs Radius Graph
		void InitializeIonizationVsRadius() {
			IonizationVsRadiusGraph_.GetGraph()->setParent(GraphAreaWidget);
			IonizationVsRadiusGraph_.InitializeGraph(GenerateGeometry(ORDER_IONIZATION_VS_RADIUS),
				"Radius", "Ionization %", 0.0, RADIUS_UPPER, 0.0, IONIZATION_UPPER);

		}
        
        // Initialize Wall Radius Vs Time Graph
        void InitializeWallRadiusVsTime() {
            WallRadiusVsTimeGraph_.GetGraph()->setParent(GraphAreaWidget);
            WallRadiusVsTimeGraph_.InitializeGraph(GenerateGeometry(ORDER_WALL_RADIUS_VS_TIME),
                "Time", "Wall Radius", 0.0, RADIUS_UPPER, 0.0, TEMPERATURE_UPPER);
            
        }
        
        // Initialize Particle Distribution Graph
        void InitializeParticleDistributionPlot() {
            ParticleDistributionPlot_.GetGraph()->setParent(GraphAreaWidget);
            ParticleDistributionPlot_.InitializeGraph(GenerateGeometry(ORDER_DISTRIBUTION_PLOT),
                                                      "", "", 0.0, 0.0, 0.0, 0.0);
        }
        
        // Initialize Collision Energy Plot
        void InitializeCollisionEnergyPlot() {
            CollisionEnergyPlot_.GetGraph()->setParent(GraphAreaWidget);
            CollisionEnergyPlot_.InitializeGraph(GenerateGeometry(ORDER_COLLISION_ENERGY_PLOT),
                                                 "", "", 0.0, 0.0, 0.0, 0.0);
        }
        
        // Change the Width of All the Graphs
        void ChangeGraphWidths(int width) {
            if(width < 0)
                throw "Graph width cannot be a negative number";
            
            DensityVsRadiusGraph_.SetGeometry(GenerateGeometry(ORDER_DENSITY_VS_RADIUS, width));
            TemperatureVsRadiusGraph_.SetGeometry(GenerateGeometry(ORDER_TEMPERATURE_VS_RADIUS, width));
            IonizationVsRadiusGraph_.SetGeometry(GenerateGeometry(ORDER_IONIZATION_VS_RADIUS, width));
            WallRadiusVsTimeGraph_.SetGeometry(GenerateGeometry(ORDER_WALL_RADIUS_VS_TIME, width));
            ParticleDistributionPlot_.SetGeometry(GenerateGeometry(ORDER_DISTRIBUTION_PLOT, width));
            CollisionEnergyPlot_.SetGeometry(GenerateGeometry(ORDER_COLLISION_ENERGY_PLOT, width));
            
            ChangeScrollArea(width);
            
            GraphSize_ = width;
        }
        
        // Changes the Displayed Labels Depending on the User's Mode Choice
        void ChangeLabelDisplayMode(int mode) {
            switch(mode) {
                // Complex Mode
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
        // Generates the Correctly Positioned Graph Box with the Correct Resolution
        QRect& GenerateGeometry(int graphNumber, int width = DEFAULT_WIDTH) {
            if(width < 0)
                throw "Graph width cannot be a negative number";
            
            int rowNumber = graphNumber / NUM_OF_COLUMNS;
            int colNumber = graphNumber % NUM_OF_COLUMNS;
            QRect* newRect = new QRect(LEFT_MARGIN + (colNumber * (DEFAULT_PADDING + width)),
                TOP_MARGIN + (rowNumber * (DEFAULT_PADDING + Height(width))), width, Height(width));
            
            return *newRect;
        }
        
        // Calculates Appropriate Graph Height Using the Width and PHI
        int Height(int width) {
            return (int) (width / Utilities::PHI);
        }
        
        // Changes the Scroll Area Depending on Graph Width
        void ChangeScrollArea(int width = DEFAULT_WIDTH) {
            GraphAreaWidget->setGeometry(QRect(0, 0, (LEFT_MARGIN +
                    (DEFAULT_PADDING + width) * NUM_OF_COLUMNS),
                    (TOP_MARGIN + (ceil(NUM_OF_GRAPHS / NUM_OF_COLUMNS)) *
                    (Height(width) + DEFAULT_PADDING))));
        }
        
        // Stores the Graph Width to Memory Every Time There is a Size Update
        int GraphSize_;
	};

}

#endif
