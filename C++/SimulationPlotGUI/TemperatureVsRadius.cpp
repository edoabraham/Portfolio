/// TemperatureVsRadius.cpp - Temperature vs Radius Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "TemperatureVsRadius.h"

// Constructor
TemperatureVsRadiusGraph::TemperatureVsRadiusGraph(QWidget* parent) : Graph(parent) {

}

// Abstract Method for Interpreting Snapshot Data
void TemperatureVsRadiusGraph::ProcessPoints(SnapshotData &snapshotData) {
    
	// Set Number of Graphs
	NumberOfGraphs_ = snapshotData.GetNumOfGases();

    // Iterate and Store Accordingly
	for(int k = 0; k < NumberOfGraphs_; k++) {

		QVector<double> xPoint;
		QVector<double> yPoint;

		for(int i = 0, j = snapshotData.Shells.size(); i < j; i++) {

			xPoint.push_back(snapshotData.Shells[i].Radius);
			yPoint.push_back(snapshotData.Shells[i].Temperature[k]);
		}

		xPoints_.push_back(xPoint);
		yPoints_.push_back(yPoint);
	}
    
}