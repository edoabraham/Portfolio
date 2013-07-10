/// ParticleDistributionPlot.h - Particle Distrubution Plot Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __PARTICLE_DISTRIBUTION_PLOT_H__
#define __PARTICLE_DISTRIBUTION_PLOT_H__

#include "stdafx.h"
#include "GraphGL.h"
#include "Savepoint.h"
#include "ProjectSettings.h"

/// Multiplier to scale down the numbers for drawing
#ifndef SP_SCALE
#define SP_SCALE 0.000008f
#endif

/// Particle Colors
#ifndef PARTICLE1_COLOR
#define PARTICLE1_COLOR QColor::fromRgb(132, 112, 255)
#endif

#ifndef PARTICLE2_COLOR
#define PARTICLE2_COLOR QColor::fromRgb(0, 201, 87)
#endif

class ParticleDistributionPlot : public GraphGL {
public:
    // Constructor
    ParticleDistributionPlot(QWidget* parent = NULL)
        : GraphGL(parent) {
        
    }
    
    // Method used for storing data for a set of points
    void StorePoints(DataSavepoint& savepoint) {
        
        #ifdef RUN_WITH_SAVEPOINTS
        
        vector<float> xPoints;
        vector<float> yPoints;
        vector<float> zPoints;
        vector<QColor> colors;
        
        int spSize = savepoint.GetSize();
        
        xPoints.reserve(spSize);
        yPoints.reserve(spSize);
        zPoints.reserve(spSize);
        
        for(int i = 0; i < spSize; i++) {
            xPoints.push_back((float)savepoint[i].Position.X * SP_SCALE);
            yPoints.push_back((float)savepoint[i].Position.Y * SP_SCALE);
            zPoints.push_back((float)savepoint[i].Position.Z * SP_SCALE);
            colors.push_back(((savepoint[i].ParticleType == 2) ? PARTICLE1_COLOR : PARTICLE2_COLOR));
        }
        
        LoadPoints(xPoints, yPoints, zPoints, colors);
        
        #endif
    }
};

#endif 
