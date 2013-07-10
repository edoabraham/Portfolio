// SignalPlot.h - SignalPlot Class Declaration.
// Written by Jesse Z. Zhong
#ifndef __SignalPlot_h__
#define __SignalPlot_h__
#pragma region Includes
#include "stdafx.h"
#include "Graph.h"
#include "DataFile.h"
#include "ColorPicker.h"
#pragma endregion
// Allows for the plotting of ASC data.
class SignalPlot : public Graph<DataFile> {
public:
	// Constructor
	SignalPlot(QWidget* parent = NULL) : Graph(parent) {

		// Initialize the color picker for choosing colors.
		this->ColorPicker_ = ColorPicker();
	}
private:
	// Reads, interprets, and stores data for graphing.
	virtual PlotData* ProcessPoints(DataFile& data);
#pragma region Utilities
	// Color picker utility for choosing colors.
	ColorPicker ColorPicker_;
#pragma endregion
};

#endif // End: SignalPlot