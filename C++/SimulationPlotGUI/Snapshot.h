/// Snapshot.h - Snapshot File Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include "stdafx.h"
#include "SnapshotData.h"

using namespace std;

class Snapshot {
public:
	// Constructor
	Snapshot();
    
    // Init-Constructor
    Snapshot(const string& fileName);

	// Parse the File
	bool ParseFile(const string& fileName);

	// Return the SnapshotData
	SnapshotData& GetSnapshotData();

private:
	// Property Tree for Data
	SnapshotData SnapshotData_;
};

#endif
