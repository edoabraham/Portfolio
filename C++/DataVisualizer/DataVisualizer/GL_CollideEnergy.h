// GL_CollideEnergy.h - Collision Energy plot class implementation.
// Written By Jesse Z. Zhong
#ifndef __Collision_Energy_Plot_H__
#define __Collision_Energy_Plot_H__
#include "stdafx.h"
#include "GraphGL.h"
#include "DataCollisionEnergy.h"

// Multiplier to scale down the numbers for drawing.
#ifndef SCALE
#define SCALE 15000
#endif

//
const double ENERGY_UPPER_LIMIT = 1.0e-19;
const double ENERGY_LOWER_LIMIT = 1.0e-21;
const double ENERGY_RANGE = ENERGY_UPPER_LIMIT - ENERGY_LOWER_LIMIT;

//
const QColor ENERGY_UPPER_LIMIT_COLOR = QColor::fromRgb(255, 0, 0);
const QColor ENERGY_LOWER_LIMIT_COLOR = QColor::fromRgb(0, 0, 255);

// Offset
const double COLOR_OFFSET = 0.25;

class GL_CollideEnergy : public GraphGL {
public:
	// Constructor
	GL_CollideEnergy(QWidget* parent = NULL)
		: GraphGL(parent) {
        
	}
    
    // Method used for storing data for a set of points
    void StorePoints(DataCollisionEnergy &data) {
        
        vector<float> xPoints;
        vector<float> yPoints;
        vector<float> zPoints;
        vector<QColor> colors;
        
        int colliSize = data.GetData().size();
        
        xPoints.reserve(colliSize);
        yPoints.reserve(colliSize);
        zPoints.reserve(colliSize);
        
        for(int i = 0; i < colliSize; i++) {
            xPoints.push_back(data.GetData()[i].Position.X * SCALE);
            yPoints.push_back(data.GetData()[i].Position.Y * SCALE);
            zPoints.push_back(data.GetData()[i].Position.Z * SCALE);
            colors.push_back(ProduceColor(data.GetData()[i].Energy));
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
