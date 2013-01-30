/// DataManager.cpp - Data Manager Class Method Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "DataManager.h"

// Constructor
DataManager::DataManager() : FileReader() {
    
}

// Init-Constructor
DataManager::DataManager(string directory) : FileReader(directory) {
    
}

// Stores All Available Snapshots
void DataManager::StoreData() {
    FileCheck();
    
    // Create a Progress Dialog with No Cancel Button
    QProgressDialog progress(QString().setNum(NumberOfSets_) + QString(" Files Found. Loading Files..."), QString(), 0, NumberOfSets_);
    progress.setWindowModality(Qt::WindowModal);
    
    
    // Only Saves Available Sets
    for(int i = 0; i < NumberOfSets_; i++) {
        
        // Update Progress Bar
        progress.setValue(i);
        //if(progress.wasCanceled())
        //    break;
        
        Snapshot newSnapshot = Snapshot(SnapshotFileName(i));
        SnapshotCollection_.push_back(newSnapshot.GetSnapshotData());
        
        #ifdef RUN_WITH_SAVEPOINTS
        Savepoint newSavepoint = Savepoint(SavepointFileName(i));
        SavepointCollection_.push_back(newSavepoint);
        #endif
        
        #ifdef RUN_WITH_COLLISION_ENERGY
        CollisionEnergy newColEnergy = CollisionEnergy(CollisionEnergyFileName(i));
        CollisionEnergyCollection_.push_back(newColEnergy);
        #endif
    }
    
    // Update Again When Max Reached
    progress.setValue(NumberOfSets_);
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
Savepoint& DataManager::GetSavepointData(int index) {
    #ifdef RUN_WITH_SAVEPOINTS
    if(CheckBounds(index)) {
        return SavepointCollection_[index];
    } else {
        string exceptionMessage = "Cannot get requested Savepoint from Savepoint Collections";
        throw exceptionMessage;
    }
    #else
    // Throw a Bone
    return *(new Savepoint());
    #endif
}

// Returns Collision Energy Data for a Particular Index
CollisionEnergy& DataManager::GetCollisionEnergyData(int index) {
    #ifdef RUN_WITH_COLLISION_ENERGY
    if(CheckBounds(index)) {
        return CollisionEnergyCollection_[index];
    } else {
        string exceptionMessage = "Cannot get requested CollisionEnergy from CollisionEnergy Collections";
        throw exceptionMessage;
    }
    #else
    // Throwing Moar Bones
    return *(new CollisionEnergy());
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
