// SignalPlot.cpp - SignalPlot Class Implementation.
// Written By Jesse Z. Zhong
#include "stdafx.h"
#include "SignalPlot.h"
using namespace std;

// Reads, interprets, and stores data for graphing.
PlotData* SignalPlot::ProcessPoints(DataFile& data) {

	// Create a new plot data.
	PlotData* plotData = new PlotData();

	// Set the color of the plot.
	plotData->Color = this->ColorPicker_.Draw(ColorPicker::Preset);

	// Reserve space for arrays.
	int totalPoints = data.GetDataPoints().size();
	plotData->X.reserve(totalPoints);
	plotData->Y.reserve(totalPoints);

	// Initialize variables to calculate x values.
	double x = 0;
	double y = 0;
	double xIncrement = data.GetSamplingRate();

	// Iterate through all the points and
	// begin storing them in the graph.
	for(int i = 0; i < totalPoints; i++) {

		// Store new x value.
		plotData->X.push_back(x);

		// Adjust the y value.
		y = data.GetDataPoints()[i];

		// Store y value.
		plotData->Y.push_back(y);

		// Test for y max.
		plotData->SetYUpper((y > plotData->GetYUpper())
			? y : plotData->GetYUpper());

		// Test for y min.
		plotData->SetYLower((y < plotData->GetYLower())
			? y : plotData->GetYLower());

		// Increment x value up.
		x += xIncrement;
	}

	// Set the minimums and maximums.
	plotData->SetXLower(0);
	plotData->SetXUpper(x);

	// Compare range with existing range.
	this->Graph_->SetFullXLower(0);
	this->Graph_->SetFullXUpper((x > this->Graph_->GetFullXUpper()) 
		? x : this->Graph_->GetFullXUpper());
	this->Graph_->SetFullYLower((plotData->GetYLower() < this->Graph_->GetFullYLower()) 
		? plotData->GetYLower() : this->Graph_->GetFullYLower());
	this->Graph_->SetFullYUpper((plotData->GetYUpper() > this->Graph_->GetFullYUpper())
		? plotData->GetYUpper() : this->Graph_->GetFullYUpper());

	// Reset the view port with the new max and min.
	this->Graph_->ResetView();

	// Store the data into the data list.
	this->Graph_->GetData()->push_back(plotData);

	// Return the data set.
	return plotData;
}