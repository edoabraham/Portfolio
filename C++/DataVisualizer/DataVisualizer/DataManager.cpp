// DataManager.cpp - Data Manager Class Method Implementations
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "DataManager.h"
#pragma endregion
#pragma region File Names and Extensions Constants
// The keys that indicate the type of file in the file name.
const char* SnapshotKey = "Snapshot";
const char* SavepointKey = "SavePoint";
const char* CollisionKey = "CollisionEnergy";

// 

#pragma endregion
// Constructor
DataManager::DataManager() : FileReader() {
    
}

// Init-Constructor
DataManager::DataManager(string directory) : FileReader(directory) {
    
}

// Stores All Available Snapshots
void DataManager::StoreData() {
    this->FileCheck();
    
    // Only Saves Available Sets
    for(int i = 0; i < NumberOfSets_; i++) {
        
        DataSnapshot newSnapshot = DataSnapshot(SnapshotFileName(i));
        SnapshotCollection_.push_back(newSnapshot.GetSnapshotData());
        
        #ifdef RUN_WITH_SAVEPOINTS
        DataSavepoint newSavepoint = DataSavepoint(SavepointFileName(i));
        SavepointCollection_.push_back(newSavepoint);
        #endif
        
        #ifdef RUN_WITH_COLLISION_ENERGY
        DataCollisionEnergy newColEnergy = DataCollisionEnergy(CollisionEnergyFileName(i));
        CollisionEnergyCollection_.push_back(newColEnergy);
        #endif
    }
}

// Return Snapshot Data of a Particular Index
SnapshotData& DataManager::GetSnapshotData(int index) {
    if(CheckBounds(index)) {
        return SnapshotCollection_[index];
    } else {
        string exceptionMessage = "Cannot get requested Snapshot from Snapshot Collections";
        throw exceptionMessage;
    }
}

// Return Savepoint Data of a Particular Index
DataSavepoint& DataManager::GetSavepointData(int index) {
    #ifdef RUN_WITH_SAVEPOINTS
    if(CheckBounds(index)) {
        return SavepointCollection_[index];
    } else {
        string exceptionMessage = "Cannot get requested Savepoint from Savepoint Collections";
        throw exceptionMessage;
    }
    #else
    // Throw a Bone
    return *(new DataSavepoint());
    #endif
}

// Returns Collision Energy Data for a Particular Index
DataCollisionEnergy& DataManager::GetCollisionEnergyData(int index) {
    #ifdef RUN_WITH_COLLISION_ENERGY
    if(CheckBounds(index)) {
        return CollisionEnergyCollection_[index];
    } else {
        string exceptionMessage = "Cannot get requested CollisionEnergy from CollisionEnergy Collections";
        throw exceptionMessage;
    }
    #else
    // Throwing Moar Bones
    return *(new DataCollisionEnergy());
    #endif
}

// Check if Index Access is Within Bounds
bool DataManager::CheckBounds(int index) const {
    if(!((index >= 0) && (index < NumberOfSets_))) {
        string exceptionMessage = "Index Access to Snapshot Collections is out of bounds";
        throw exceptionMessage;
        
        return false;
    }
    
    return true;
}
