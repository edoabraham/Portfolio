/// CollisionEnergyPlot.cpp - Collision Energy Plot Class Methods Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "CollisionEnergyPlot.h"

// Constructor
CollisionEnergyPlot::CollisionEnergyPlot(QWidget* parent) : Graph(parent) {
    scatterPlot_ = true;
    resizeGraph_ = false;
}

// Abstract Method for Interpreting Collision Energy Data
void CollisionEnergyPlot::ProcessPoints(CollisionEnergy &collisionData) {
    
    // Set a Single Graph
	NumberOfGraphs_ = 1;
    
    // Set Ranges
    XLower_ = collisionData.GetMin().X;
    YLower_ = collisionData.GetMin().Z;
    XUpper_ = collisionData.GetMax().X;
    YUpper_ = collisionData.GetMax().Z;
    
    // Store Data Points Accordingly
	QVector<double> xPoint;
	QVector<double> yPoint;
    
	for(int i = 0, j = collisionData.GetSize(); i < j; i++) {
        xPoint.push_back(collisionData[i].X);
        yPoint.push_back(collisionData[i].Z);
    }
    
	xPoints_.push_back(xPoint);
	yPoints_.push_back(yPoint);
    
}