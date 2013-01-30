/// WallRadiusVsTime.h - Wall Radius vs Time Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "WallRadiusVsTime.h"

// Constructor
WallRadiusVsTimeGraph::WallRadiusVsTimeGraph(QWidget* parent) : Graph(parent) {

}

// Abstract Method for Interpreting Snapshot Data
void WallRadiusVsTimeGraph::ProcessPoints(vector<RPKStruct>& RPKData) {

    NumberOfGraphs_ = 1;
    
    // Store Data Points Accordingly
	for(int k = 0; k < NumberOfGraphs_; k++) {

		QVector<double> xPoint;
		QVector<double> yPoint;

		for(int i = 0, j = RPKData.size(); i < j; i++) {

			xPoint.push_back(RPKData[i].Time);
			yPoint.push_back(RPKData[i].WallRadius);
		}

		xPoints_.push_back(xPoint);
		yPoints_.push_back(yPoint);
	}
    
}