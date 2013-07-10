/// DensityVsRadius.cpp - Density vs Radius Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "ProjectSettings.h"
#include "DensityVsRadius.h"

// Constructor
DensityVsRadiusGraph::DensityVsRadiusGraph(QWidget* parent) : Graph(parent) {

}

// Abstract Method for Interpreting Snapshot Data
void DensityVsRadiusGraph::ProcessPoints(SnapshotData &snapshotData) {
    
    // Set a Single Graph
	NumberOfGraphs_ = 1;
    
    // Store Data Points Accordingly
    vector<QVector<double> > xPoint;
	vector<QVector<double> > yPoint;
    xPoint.resize(NumberOfGraphs_);
    yPoint.resize(NumberOfGraphs_);
    
    // Reserve the Space
    xPoint[0].reserve(snapshotData.Shells.size());
    yPoint[0].reserve(snapshotData.Shells.size());

	for(int i = 0, j = snapshotData.Shells.size(); i < j; i++) {

		xPoint[0].push_back((double)snapshotData.Shells[i].Radius);
		yPoint[0].push_back((double)snapshotData.Shells[i].Density);
	}
    
	xPoints_.push_back(xPoint);
	yPoints_.push_back(yPoint);
    
}