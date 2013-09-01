// G_IonizationRadius.h - Ionization vs Radius plot class implementation.
// Written By Jesse Z. Zhong
#ifndef __Ionization_vs_Radius_H__
#define __Ionization_vs_Radius_H__
#include "stdafx.h"
#include "Graph.h"
#include "ColorPicker.h"
#include "DataSnapshot.h"
using namespace std;

// Implements shell ionization levels vs
// shell radius plots using data from snapshots.
class G_IonizationRadius : public Graph<DataSnapshot> {
public:
    // Constructor
	G_IonizationRadius(QWidget* parent = NULL) 
		: Graph<DataSnapshot>(parent) {

	}

private:
    // Adds a new set of data to a plot.
	virtual void ProcessPoints(DataSnapshot& data) {
		
		// Localize the number of gas types.
		int numOfGases = data.GetGasTypes();

		// Reset color picker.
		this->ColorPicker_.Reset();

		// Perform storage for each gas type.
		for(int k = 0; k < numOfGases; k++) {

			// Create new plot data set.
			PlotData* plotData = new PlotData();

			// Select the color for the plot.
			plotData->Color = this->ColorPicker_.Draw(ColorPicker::Preset); 

			// Reserve the space in the arrays.
			int totalPoints = data.GetShellData().size();
			plotData->X.reserve(totalPoints);
			plotData->Y.reserve(totalPoints);

			// Iterate through all the points in the shell data
			// and begin storing relevant values in the graph.
			for(int i = 0; i < totalPoints; i++)
				plotData->AddPoint(data.GetShellData()[i].Radius,
					data.GetShellData()[i].Ionization[k]);

			// Register new plot data accordingly.
			this->RegisterPlot(plotData);
		}
	}
#pragma region Utilities
	// Color picker utility for choosing colors.
	ColorPicker ColorPicker_;
#pragma endregion
};

#endif