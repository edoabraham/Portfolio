/// ParticleDistributionPlot.h - Particle Distrubution Plot Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __PARTICLE_DISTRIBUTION_PLOT_H__
#define __PARTICLE_DISTRIBUTION_PLOT_H__

#include "stdafx.h"
#include "Graph.h"
#include "Savepoint.h"

class ParticleDistributionPlot : public Graph<Savepoint> {
public:
    // Constructor
    ParticleDistributionPlot(QWidget* parent = NULL);
    
private:
	// Abstract Method for Interpreting Savepoint Data
	virtual void ProcessPoints(Savepoint& savepoint);
};

#endif 
