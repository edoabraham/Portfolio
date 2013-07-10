/// WallRadiusVsTime.h - Wall Radius vs Time Graph 
/// Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "ProjectSettings.h"
#include "WallRadiusVsTime.h"

// Constructor
WallRadiusVsTimeGraph::WallRadiusVsTimeGraph(QWidget* parent) : Graph(parent) {
    SetAutomaticResize(false);
}

// Abstract Method for Interpreting Snapshot Data
void WallRadiusVsTimeGraph::ProcessPoints(DataRPK& RPKData) {

    NumberOfGraphs_ = 1;
    
    // Set Bounds
    XLower_ = RPKData.GetMin().Time;
    YLower_ = RPKData.GetMin().WallRadius;
    XUpper_ = RPKData.GetMax().Time;
    XUpper_ = RPKData.GetMax().WallRadius;
    
    // Store Data Points Accordingly
    vector<QVector<double> > xPoint;
	vector<QVector<double> > yPoint;
    xPoint.resize(NumberOfGraphs_);
    yPoint.resize(NumberOfGraphs_);
    
    // Reserve the Space
    xPoint[0].reserve(RPKData.GetNumOfEntries());
    yPoint[0].reserve(RPKData.GetNumOfEntries());

    for(int i = 0, j = RPKData.GetNumOfEntries(); i < j; i++) {

        xPoint[0].push_back((double)RPKData[i].Time);
        yPoint[0].push_back((double)RPKData[i].WallRadius);
    }

    xPoints_.push_back(xPoint);
    yPoints_.push_back(yPoint);
}