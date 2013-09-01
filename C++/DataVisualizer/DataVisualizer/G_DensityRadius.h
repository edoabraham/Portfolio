// G_DensityRadius.h - Density vs Radius plot class implementation.
// Written By Jesse Z. Zhong
#ifndef __Density_vs_Radius_H__
#define __Density_vs_Radius_H__
#include "stdafx.h"
#include "Graph.h"
#include "ColorPicker.h"
#include "DataSnapshot.h"
using namespace std;

// Implements shell density vs shell
// radius plots using data from snapshots.
class G_DensityRadius : public Graph<DataSnapshot> {
public:
	// Constructor
	G_DensityRadius(QWidget* parent = NULL) 
		: Graph<DataSnapshot>(parent) {

	}

private:
	// Adds a new set of data to a plot.
	virtual void ProcessPoints(DataSnapshot& data) {

		// Create a new plot data set.
		PlotData* plotData = new PlotData();

		// Select the color for the plot.
		this->ColorPicker_.Reset();
		plotData->Color = this->ColorPicker_.Draw(ColorPicker::Preset);

		// Reserve space in the arrays.
		int totalPoints = data.GetShellData().size();
		plotData->X.reserve(totalPoints);
		plotData->Y.reserve(totalPoints);

		// Iterate through all the points in the shell data
		// and begin storing relevant values in the graph.
		for(int i = 0; i < totalPoints; i++)
			plotData->AddPoint(data.GetShellData()[i].Radius,
				data.GetShellData()[i].Density);

		// Register the plot accordingly.
		this->RegisterPlot(plotData);
	}
#pragma region Utilities
	// Color picker utility for choosing colors.
	ColorPicker ColorPicker_;
#pragma endregion
};

#endif