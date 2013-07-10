/// CollisionEnergyPlot.h - Collision Energy Plot Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __COLLISION_ENERGY_PLOT_H__
#define __COLLISION_ENERGY_PLOT_H__

#include "stdafx.h"
#include "GraphGL.h"
#include "CollisionEnergy.h"
#include "ProjectSettings.h"

/// Multiplier to scale down the numbers for drawing
#ifndef SCALE
#define SCALE 15000
#endif

/// 
const double ENERGY_UPPER_LIMIT = 1.0e-19;
const double ENERGY_LOWER_LIMIT = 1.0e-21;
const double ENERGY_RANGE = ENERGY_UPPER_LIMIT - ENERGY_LOWER_LIMIT;

///
const QColor ENERGY_UPPER_LIMIT_COLOR = QColor::fromRgb(255, 0, 0);
const QColor ENERGY_LOWER_LIMIT_COLOR = QColor::fromRgb(0, 0, 255);

/// Offset
const double COLOR_OFFSET = 0.25;

class CollisionEnergyPlot : public GraphGL {
public:
	// Constructor
	CollisionEnergyPlot(QWidget* parent = NULL)
    : GraphGL(parent) {
        
    }
    
    // Method used for storing data for a set of points
    void StorePoints(DataCollisionEnergy &collisionData) {
        
        vector<float> xPoints;
        vector<float> yPoints;
        vector<float> zPoints;
        vector<QColor> colors;
        
        int colliSize = collisionData.GetSize();
        
        xPoints.reserve(colliSize);
        yPoints.reserve(colliSize);
        zPoints.reserve(colliSize);
        
        for(int i = 0; i < colliSize; i++) {
            xPoints.push_back(collisionData[i].X * SCALE);
            yPoints.push_back(collisionData[i].Y * SCALE);
            zPoints.push_back(collisionData[i].Z * SCALE);
            colors.push_back(ProduceColor(collisionData[i].Energy));
        }
        
        LoadPoints(xPoints, yPoints, zPoints, colors);
    }
    
    QColor ProduceColor(double value) {
        if(value <= ENERGY_LOWER_LIMIT)
            return ENERGY_LOWER_LIMIT_COLOR;
        else if(value >= ENERGY_UPPER_LIMIT)
            return ENERGY_UPPER_LIMIT_COLOR;
        else {
            double ratio = (value - ENERGY_LOWER_LIMIT) / ENERGY_RANGE;
            return QColor::fromRgbF(((ratio < COLOR_OFFSET) ? ratio * 2 : 0),
            0,
            ((ratio >= COLOR_OFFSET) ? (1 - (ratio - COLOR_OFFSET)) : 1));
        }
    }
};


#endif 
