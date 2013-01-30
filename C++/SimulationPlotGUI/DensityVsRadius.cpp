/// DensityVsRadius.cpp - Density vs Radius Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "DensityVsRadius.h"

// Constructor
DensityVsRadiusGraph::DensityVsRadiusGraph(QWidget* parent) : Graph(parent) {

}

// Abstract Method for Interpreting Snapshot Data
void DensityVsRadiusGraph::ProcessPoints(SnapshotData &snapshotData) {
    
    // Set a Single Graph
	NumberOfGraphs_ = 1;
    
    // Store Data Points Accordingly
	QVector<double> xPoint;
	QVector<double> yPoint;

	for(int i = 0, j = snapshotData.Shells.size(); i < j; i++) {

		xPoint.push_back(snapshotData.Shells[i].Radius);
		yPoint.push_back(snapshotData.Shells[i].Density);
	}

	xPoints_.push_back(xPoint);
	yPoints_.push_back(yPoint);
    
}