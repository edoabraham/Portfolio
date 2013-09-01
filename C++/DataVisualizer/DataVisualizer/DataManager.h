// DataManager.h - Data Manager Class Declaration
// Written By Jesse Z. Zhong
#ifndef __Data_Manager_H__
#define __Data_Manager_H__
#pragma region Includes
#include "stdafx.h"
#include "DataSnapshot.h"
#include "DataSavepoint.h"
#include "DataCollisionEnergy.h"
#include "DataRPK.h"
using namespace std;
#pragma endregion
// Used for reading and storing data.
class DataManager {
public:
	// Constructor
	DataManager(QWidget* parent = 0) {
		this->RPK_ = DataRPK();
		this->DirPath_ = QString();
		this->Snapshot_ = vector<DataSnapshot>();
		this->Savepoint_ = vector<DataSavepoint>();
		this->CollideEnergy_ = vector<DataCollisionEnergy>();
		this->Parent_ = parent;
		this->MaxSets_ = 0;
	}

	// Destructor
	~DataManager() {

	}
    
	// Reads and stores all available
	// files in a specified directory.
	void StoreData();

	// Returns a single RPK data.
	// Returns a blank RPK if no data is found.
	DataRPK& GetRPKData();

	// Returns snapshot data at a given index.
	// Returns a blank snapshot if no data is found.
	DataSnapshot& GetSnapshotData(int index);
    
	// Returns the save point data at a given index.
	// Returns a blank save point data if no data is found.
	DataSavepoint& GetSavepointData(int index);
    
	// Returns the collision energy data at a given index.
	// Returns a blank collision energy data if no data is found.
	DataCollisionEnergy& GetCollisionEnergyData(int index);

	// Returns the maximum number of files in either
	// the snapshot, save point, or collision energy lists.
	int GetMaxSets() const;

	// Gets or sets the directory path.
	QString GetDirPath() const;
	void SetDirPath(const QString& dir);
private:
    // Check if an index is within the 
	// range of a given container or array.
	template<typename T>
    bool CheckBounds(int index, vector<T> container) const;

	// Holds an RPK data set.
	DataRPK RPK_;
    
	// List of compiled snapshot data.
	vector<DataSnapshot> Snapshot_;
    
    // List of compiled save point data.
    vector<DataSavepoint> Savepoint_;
    
    // List of compiled collision energy data.
    vector<DataCollisionEnergy> CollideEnergy_;

	// Path of the file directory that the files are read from.
	QString DirPath_;

	// Records the number of files whole sets stored.
	int MaxSets_;

	// Reference to a widget that will be used
	// for any temporary UI elements created.
	QWidget* Parent_;
};

#endif

