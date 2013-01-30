/// CollisionEnergy.h - Collision Energy Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __COLLISION_ENERGY_H__
#define __COLLISION_ENERGY_H__

#include "stdafx.h"
#include "CollisionEnergyData.h"

using namespace std;

/// Stores the Particle Collision
/// Data for Each Collision Event
/// in the Simulated Environment
class CollisionEnergy {
public:
    // Constructor
    CollisionEnergy();
    
    // Init-Constructor
    CollisionEnergy(const string& fileName);
    
    // Parses a Collision Energy File
    bool ReadFile(const string& fileName);
    
    // Index Operator Overload
    CollisionEnergyData& operator[](const int i);
    
    // Returns the Number of Entries in the Collection List
    int GetSize() const;
    
    // Returns the Max and Min Collision Data Values
    CollisionEnergyData GetMax() const;
    CollisionEnergyData GetMin() const;
    
private:
    // Does a Comparison for Max and Min and Updates
    // Their Values with Any Necessary Changes
    void UpdateMaxAndMin(CollisionEnergyData value);
    
    // Holds a List of All Collision Events and their
    // Data During a Certain Simulation Snapshot
    vector<CollisionEnergyData> CollisionList_;
    
    // Max and Min Data Sets
    CollisionEnergyData Max_;
    CollisionEnergyData Min_;
    
    // Number of Entries in the Collision List
    int Size_;
};

// Out Stream Overload
ostream& operator<<(ostream& out, CollisionEnergy& ce);

#endif
