/// ParticleDistributionPlot.cpp - Particle Distrubution Plot Methods Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "ParticleDistributionPlot.h"

// Constructor
ParticleDistributionPlot::ParticleDistributionPlot(QWidget* parent) : Graph(parent) {
    scatterPlot_ = true;
    resizeGraph_ = false;
}

// Abstract Method for Interpreting Savepoint Data
void ParticleDistributionPlot::ProcessPoints(Savepoint& savepoint) {
    
    // Set a Single Graph
	NumberOfGraphs_ = 1;
    
    // Set Ranges
    XLower_ = savepoint.GetMin().Position.X;
    YLower_ = savepoint.GetMin().Position.Y;
    XUpper_ = savepoint.GetMax().Position.X;
    YUpper_ = savepoint.GetMax().Position.Y;
    
    // Store Data Points Accordingly
	QVector<double> xPoint;
	QVector<double> yPoint;
    
	//for(int i = 0, j = savepoint.GetSize(); i < j; i++) {
    //    xPoint.push_back(savepoint[i].Position.X);
    //    yPoint.push_back(savepoint[i].Position.Y);
    //}
    
	xPoints_.push_back(xPoint);
	yPoints_.push_back(yPoint);
}
