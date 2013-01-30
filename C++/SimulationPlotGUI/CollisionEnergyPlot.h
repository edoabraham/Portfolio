/// CollisionEnergyPlot.h - Collision Energy Plot Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __COLLISION_ENERGY_PLOT_H__
#define __COLLISION_ENERGY_PLOT_H__

#include "stdafx.h"
#include "Graph.h"
#include "CollisionEnergy.h"

class CollisionEnergyPlot : public Graph<CollisionEnergy> {
public:
	// Constructor
	CollisionEnergyPlot(QWidget* parent = NULL);
    
private:
	// Abstract Method for Interpreting Collision Energy Data
	virtual void ProcessPoints(CollisionEnergy &collisionData);
};


#endif 
