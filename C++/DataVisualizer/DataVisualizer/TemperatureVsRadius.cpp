/// TemperatureVsRadius.cpp - Temperature vs Radius Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "ProjectSettings.h"
#include "TemperatureVsRadius.h"

// Constructor
TemperatureVsRadiusGraph::TemperatureVsRadiusGraph(QWidget* parent) : Graph(parent) {

}

// Abstract Method for Interpreting Snapshot Data
void TemperatureVsRadiusGraph::ProcessPoints(SnapshotData &snapshotData) {
    
	// Set Number of Graphs
	NumberOfGraphs_ = snapshotData.GetNumOfGases();
    
    // Store Data Points Accordingly
    vector<QVector<double> > xPoint;
	vector<QVector<double> > yPoint;
    xPoint.resize(NumberOfGraphs_);
    yPoint.resize(NumberOfGraphs_);

    // Iterate and Store Accordingly
	for(int k = 0; k < NumberOfGraphs_; k++) {
        
        // Reserve the Space
        xPoint[k].reserve(snapshotData.Shells.size());
        yPoint[k].reserve(snapshotData.Shells.size());

		for(int i = 0, j = snapshotData.Shells.size(); i < j; i++) {

			xPoint[k].push_back((double)snapshotData.Shells[i].Radius);
			yPoint[k].push_back((double)snapshotData.Shells[i].Temperature[k]);
		}
	}
    
    xPoints_.push_back(xPoint);
    yPoints_.push_back(yPoint);
}