// GL_ParticleDist.h - Particle Distrubution plot class implementation.
// Written By Jesse Z. Zhong
#ifndef __Particle_Distribution_Plot_H__
#define __Particle_Distribution_Plot_H__
#include "stdafx.h"
#include "GraphGL.h"
#include "DataSavepoint.h"

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

class GL_ParticleDist : public GraphGL {
public:
    // Constructor
    GL_ParticleDist(QWidget* parent = NULL)
        : GraphGL(parent) {
        
    }
    
    // Method used for storing data for a set of points
    void StorePoints(DataSavepoint& data) {
        
        #ifdef RUN_WITH_SAVEPOINTS
        
        vector<float> xPoints;
        vector<float> yPoints;
        vector<float> zPoints;
        vector<QColor> colors;
        
        int spSize = data.GetSize();
        
        xPoints.reserve(spSize);
        yPoints.reserve(spSize);
        zPoints.reserve(spSize);
        
        for(int i = 0; i < spSize; i++) {
            xPoints.push_back((float)data[i].Position.X * SP_SCALE);
            yPoints.push_back((float)data[i].Position.Y * SP_SCALE);
            zPoints.push_back((float)data[i].Position.Z * SP_SCALE);
            colors.push_back(((data[i].ParticleType == 2) ? PARTICLE1_COLOR : PARTICLE2_COLOR));
        }
        
        LoadPoints(xPoints, yPoints, zPoints, colors);
        
        #endif
    }
};

#endif 
