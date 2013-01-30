/// CollisionEnergyData.h - Collision Energy Data Structure
/// Written By Jesse Z. Zhong

#ifndef __COLLISION_ENERGY_DATA_H__
#define __COLLISION_ENERGY_DATA_H__

#include "stdafx.h"
#include "Utilities.h"

using namespace std;

/// Stores the Data for a Single
/// Particle Collision Event
struct CollisionEnergyData {
public:
    // Constructor
    CollisionEnergyData();
    
    double Temperature;
    double X, Y, Z;
    double DeltaVelocity;
    double Energy;
    double Distance;
    int GasType1;
    int GasType2;
    
    CollisionEnergyData& ParseLine(char* line);
    
    // Compares Two Collision Energy Data Values and
    // Returns the Collision Data of the Greatest Extremes
    static void Max(CollisionEnergyData& currentMax, const CollisionEnergyData& collisionData);
    static void Min(CollisionEnergyData& currentMin, const CollisionEnergyData& collisionData);
    
};

// Out Stream Overload
ostream& operator<<(ostream& out, CollisionEnergyData& ced);

#endif 
