/// IonizationVsRadius.cpp - Ionization vs Radius Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "IonizationVsRadius.h"

// Constructor
IonizationVsRadiusGraph::IonizationVsRadiusGraph(QWidget* parent) : Graph(parent) {
    
}

void IonizationVsRadiusGraph::ProcessPoints(SnapshotData &snapshotData) {
	
	// Set Number of Graphs
	NumberOfGraphs_ = snapshotData.GetNumOfGases();

    // Store Points Accordingly
	for(int k = 0; k < NumberOfGraphs_; k++) {

		QVector<double> xPoint;
		QVector<double> yPoint;

		for(int i = 0, j = snapshotData.Shells.size(); i < j; i++) {
			
			yPoint.push_back(snapshotData.Shells[i].Ionization[k]);
			xPoint.push_back(snapshotData.Shells[i].Radius);
		}

		xPoints_.push_back(xPoint);
		yPoints_.push_back(yPoint);
	}
    
}