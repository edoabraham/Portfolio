/// Savepoint.h - Savepoint Class Declaration
/// Written by Jesse Z. Zhong

#ifndef __PARSE_SAVEPOINT_H__
#define __PARSE_SAVEPOINT_H__

#include "stdafx.h"
#include "ParticleDataStruct.h"

using namespace std;

#define READ_IN_BINARY_MODE

/// Parses and Stores Data for a Single Savepoint
class Savepoint {
public:
	// Default Constructor
	Savepoint();
    
    // Init-Constructor
    Savepoint(const string& fileName);

	// Read and Parse a Savepoint File
	bool ReadFile(const string& fileName);
    
    // Index Operator Overload
    ParticleDataStruct& operator[](const int i);
    
    // Returns the Number of Savepoints
    int GetSize() const;
    
    // Returns the Max and Min Particle Data Values
    ParticleDataStruct GetMax() const;
    ParticleDataStruct GetMin() const;
    
private:
    // Does a Comparison for Max and Min and Updates
    // Their Values with Any Necessary Changes
    void UpdateMaxAndMin(ParticleDataStruct value);
    
	// Vector List of Particle Data
	vector<ParticleDataStruct> ParticleDataList_;
    
    // Max and Min Data Sets
    ParticleDataStruct Max_;
    ParticleDataStruct Min_;
    
    // Number of Entries of Savepoints
    int Size_;
};

#endif


