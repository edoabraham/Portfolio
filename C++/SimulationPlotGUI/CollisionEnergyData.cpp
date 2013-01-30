/// CollisionEnergyData.cpp - Collision Energy
/// Data Structure Methods Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "CollisionEnergyData.h"

#ifndef DELIMITERS
#define DELIMITERS " ,\n\0"
#endif

// Constructor
CollisionEnergyData::CollisionEnergyData() {
    Temperature = 0;
    X = 0;
    Y = 0;
    Z = 0;
    DeltaVelocity = 0;
    Energy = 0;
    Distance = 0;
    GasType1 = 0;
    GasType2 = 0;
}

CollisionEnergyData& CollisionEnergyData::ParseLine(char* line) {
    
    Temperature = atof(Utilities::TestForNull(strtok(line, DELIMITERS)));
    X = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Y = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Z = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    DeltaVelocity = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Energy = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Distance = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    GasType1 = atoi(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    GasType2 = atoi(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    
    return *this;
}

void CollisionEnergyData::Max(CollisionEnergyData& currentMax, const CollisionEnergyData& collisionData) {
    // Max Comparison
    currentMax.Temperature = (currentMax.Temperature < collisionData.Temperature) ? collisionData.Temperature : currentMax.Temperature;
    currentMax.X = (currentMax.X < collisionData.X) ? collisionData.X : currentMax.X;
    currentMax.Y = (currentMax.Y < collisionData.Y) ? collisionData.Y : currentMax.Y;
    currentMax.Z = (currentMax.Z < collisionData.Z) ? collisionData.Z : currentMax.Z;
    //currentMax.DeltaVelocity = (currentMax.DeltaVelocity < collisionData.DeltaVelocity) ? collisionData.DeltaVelocity : currentMax.DeltaVelocity;
    currentMax.Energy = (currentMax.Energy < collisionData.Energy) ? collisionData.Energy : currentMax.Energy;
}

void CollisionEnergyData::Min(CollisionEnergyData& currentMin, const CollisionEnergyData& collisionData) {
    // Min Comparison
    currentMin.Temperature = (currentMin.Temperature > collisionData.Temperature) ? collisionData.Temperature : currentMin.Temperature;
    currentMin.X = (currentMin.X > collisionData.X) ? collisionData.X : currentMin.X;
    currentMin.Y = (currentMin.Y > collisionData.Y) ? collisionData.Y : currentMin.Y;
    currentMin.Z = (currentMin.Z > collisionData.Z) ? collisionData.Z : currentMin.Z;
    //currentMin.DeltaVelocity = (currentMin.DeltaVelocity > collisionData.DeltaVelocity) ? collisionData.DeltaVelocity : currentMin.DeltaVelocity;
    currentMin.Energy = (currentMin.Energy > collisionData.Energy) ? collisionData.Energy : currentMin.Energy;
}

// Out Stream Overload
ostream& operator<<(ostream& out, CollisionEnergyData& ced) {
    out
    << ced.Temperature << ", "
    << ced.X << ", "
    << ced.Y << ", "
    << ced.Z << ", "
    << ced.DeltaVelocity << ", "
    << ced.Energy << ", "
    << ced.Distance << ", "
    << ced.GasType1 << ", "
    << ced.GasType2;
    return out;
}