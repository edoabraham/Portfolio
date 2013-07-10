// DataManager.h - Data Manager Class Declaration
// Written By Jesse Z. Zhong
#ifndef __DataManager_H__
#define __DataManager_H__
#pragma region Includes
#include "stdafx.h"
#include "DataSnapshot.h"
#include "DataSavepoint.h"
#include "DataCollisionEnergy.h"
#include "DataRPK.h"
#include "FileReader.h"
using namespace std;
#pragma endregion
// 
class DataManager : public FileReader {
public:
	// Constructor
	DataManager();
    
    // Init-Constructor
    DataManager(string directory);
    
    // Stores All Available Snapshots and save points
    void StoreData();

	// Return Snapshot Data of a Particular Index
	DataSnapshot& GetSnapshotData(int index);
    
    // Return Savepoint Data of a Particular Index
    DataSavepoint& GetSavepointData(int index);
    
    // Returns Collision Energy Data for a Particular Index
    DataCollisionEnergy& GetCollisionEnergyData(int index);

private:
    // Check if Index Access is Within Bounds
    bool CheckBounds(int index) const;
    
	// Collection of Snapshot Data
	vector<DataSnapshot> SnapshotCollection_;
    
    // Collection of Savepoint Data
    vector<DataSavepoint> SavepointCollection_;
    
    // Collection of Collision Energy Data
    vector<DataCollisionEnergy> CollisionEnergyCollection_;
    
    // Snapshot Ranges
    DataSnapshot SnapshotRange_;
};

#endif

