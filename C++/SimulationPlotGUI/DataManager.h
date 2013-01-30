/// DataManager.h - Data Manager Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include <QProgressDialog>

#include "stdafx.h"
#include "Snapshot.h"
#include "SnapshotData.h"
#include "Savepoint.h"
#include "ParticleDataStruct.h"
#include "CollisionEnergy.h"
#include "CollisionEnergyData.h"
#include "FileReader.h"

using namespace std;

/// In Charge of Read Storing and
/// Deallocating Collections of 
/// Snapshot and Savepoint Data
class DataManager : public FileReader {
public:
	// Constructor
	DataManager();
    
    // Init-Constructor
    DataManager(string directory);
    
    // Stores All Available Snapshots and Savepoints
    void StoreData();

	// Return Snapshot Data of a Particular Index
	SnapshotData& GetSnapshotData(int index);
    
    // Return Savepoint Data of a Particular Index
    Savepoint& GetSavepointData(int index);
    
    // Returns Collision Energy Data for a Particular Index
    CollisionEnergy& GetCollisionEnergyData(int index);

private:
    // Check if Index Access is Within Bounds
    bool CheckBounds(int index) const;
    
	// Collection of Snapshot Data
	vector<SnapshotData> SnapshotCollection_;
    
    // Collection of Savepoint Data
    vector<Savepoint> SavepointCollection_;
    
    // Collection of Collision Energy Data
    vector<CollisionEnergy> CollisionEnergyCollection_;
    
    // Snapshot Ranges
    Snapshot SnapshotRange_;
    
    // Savepoint Ranges
    ParticleDataStruct MaxParticleData_;
    ParticleDataStruct MinParticleData_;
    
    // Collision Energy Ranges
    CollisionEnergyData MaxCollisionEnergy_;
    CollisionEnergyData MinCollisionEnergy_;
};

#endif

