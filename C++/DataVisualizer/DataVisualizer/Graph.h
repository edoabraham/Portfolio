// Graph.h - Graph Template Class Implementation
// Written By Jesse Z. Zhong
#ifndef __Graph_H__
#define __Graph_H__
#pragma region Includes
#include "stdafx.h"
#include "QCustomPlotEX.h"
#include "DataFile.h"
using namespace std;
#pragma endregion
// Handles the basic requirements for handling
// data and drawing said data to plots and curves.
template<class T = DataFile>
class Graph {
public:
	// Constructor
	Graph(QWidget* parent) {
		this->Graph_ = new QCustomPlotEX(parent);
	}

	// Destructor
	~Graph() {
		// Delete the graph.
		if(this->Graph_ != NULL) {
			delete this->Graph_;
			this->Graph_ = NULL;
		}
	}

	// Sets up the dimensions and labels for graph and returns it.
	QCustomPlotEX* InitializeGraph(const QRect& rect,
		string xAxisLabel, string yAxisLabel) {

			// Adjust the geometry.
			this->Graph_->setGeometry(rect);

			// Set graph labels.
			this->SetXLabel(xAxisLabel);
			this->SetYLabel(yAxisLabel);

			// Redraw the graph.
			this->Refresh();

			// Return the pointer to the graph.
			return this->Graph_;
	}

	// Processes and stores points when called.
	void AddPlot(T& data) {

		// Reset the full view port bounds.
		this->Graph_->ClearFullViewport();

		// Processes data and stores them as data points.
		this->ProcessPoints(data);
	}

	// Removes a specific data set from the graph.
	void RemovePlot(PlotData* dataPoint) {

		// Remove the data set from the list of data points.
		this->Graph_->Remove(dataPoint);

		// Refresh the graph.
		this->Graph_->Refresh();
	}

	// Clears and redraws the graph.
	void Refresh() {
		this->Graph_->Refresh();
	}

#pragma region Accessors
	// Refreshes the graph and returns it.
	QCustomPlotEX* GetGraph() {
		return this->Graph_;
	}

	// Sets the labels for the x and y axis.
	void SetXLabel(string label) {
		this->Graph_->SetXLabel(label);
	}
	void SetYLabel(string label) {
		this->Graph_->SetYLabel(label);
	}

	// Set or get the ability for the graph to
	// resize itself along with changes in data.
	void SetAutomaticResize(bool automaticallyResizes) {
		this->Graph_->SetRescaleAxis(automaticallyResizes);
	}
#pragma endregion
protected:
	// Reads, interprets, and stores data for graphing and returns pointer to data.
	virtual void ProcessPoints(T& data) = 0;

	// Stores new ranges, resets the plots, and stores new data into graph list.
	void RegisterPlot(PlotData* plotData) {

		// Compare the new range with the existing range.
		this->Graph_->SetFullXUpper((plotData->GetXUpper() > this->Graph_->GetFullXUpper()) 
			? plotData->GetXUpper() : this->Graph_->GetFullXUpper());
		this->Graph_->SetFullXLower((plotData->GetXLower() < this->Graph_->GetFullXLower()) 
			? plotData->GetXLower() : this->Graph_->GetFullXLower());

		this->Graph_->SetFullYUpper((plotData->GetYUpper() > this->Graph_->GetFullYUpper()) 
			? plotData->GetYUpper() : this->Graph_->GetFullYUpper());
		this->Graph_->SetFullYLower((plotData->GetYLower() < this->Graph_->GetFullYLower()) 
			? plotData->GetYLower() : this->Graph_->GetFullYLower());

		// Reset the view port with the new max and min.
		this->Graph_->ResetView();

		// Store the data into the data list.
		this->Graph_->GetData()->push_back(plotData);
	}

	// The graph that the plots and curves are drawn to.
	QCustomPlotEX* Graph_;
};
#endif