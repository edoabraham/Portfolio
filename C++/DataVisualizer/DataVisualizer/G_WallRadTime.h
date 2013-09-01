// G_WallRadTime.h - Wall Radius vs Time Graph plot class implementation.
// Written By Jesse Z. Zhong
#ifndef __Wall_Radius_vs_Time_H__
#define __Wall_Radius_vs_Time_H__
#include "stdafx.h"
#include "Graph.h"
#include "ColorPicker.h"
#include "DataRPK.h"
using namespace std;

// Implements the plotting of data from RPK files.
class G_WallRadTime : public Graph<DataRPK> {
public:
	// Constructor
	G_WallRadTime(QWidget* parent = NULL) 
		: Graph<DataRPK>(parent) {

	}

private:
	// Adds a new set of data to a plot.
	virtual void ProcessPoints(DataRPK& data) {

		// Create new plot data set.
		PlotData* plotData = new PlotData();

		// Select the color for the plot.
		this->ColorPicker_.Reset();
		plotData->Color = this->ColorPicker_.Draw(ColorPicker::Preset);

		// Reserve the space in the arrays.
		int totalPoints = data.GetData().size();
		plotData->X.reserve(totalPoints);
		plotData->Y.reserve(totalPoints);

		// Iterate through all the points in the shell data
		// and begin storing relevant values in the graph.
		for(int i = 0; i < totalPoints; i++)
			plotData->AddPoint(data.GetData()[i].Time,
				data.GetData()[i].WallRadius);

		// Register new plot data accordingly.
		this->RegisterPlot(plotData);
	}
#pragma region Utilities
	// Color picker utility for choosing colors.
	ColorPicker ColorPicker_;
#pragma endregion
};

#endif