// DataCollisionEnergy.h - Collision Energy Class Declaration
// Written By Jesse Z. Zhong
#ifndef __DataCollisionEnergy_H__
#define __DataCollisionEnergy_H__
#pragma region Includes
#include "stdafx.h"
#include "Vector3.h"
#include "DataFile.h"
using namespace std;
#pragma endregion
#pragma region Collision Data
// Stores particle collision data.
struct CollisionData {
	// Constructor
	CollisionData() {
		this->Temperature = 0;
		this->Position = Vector3<double>();
		this->DeltaVelocity = 0;
		this->Energy = 0;
		this->Distance = 0;
		this->Gas1Type = 0;
		this->Gas2Type = 0;
	}
	double Temperature;
	Vector3<double> Position;
	double DeltaVelocity;
	double Energy;
	double Distance;
	int Gas1Type;
	int Gas2Type;
};
#pragma endregion
// Stores a set of collision energy data.
class DataCollisionEnergy : public DataFile {
public:
#pragma region Instance
    // Constructor
    DataCollisionEnergy() {
		this->CollisionList_ = vector<CollisionData>();
		this->Min_ = CollisionData();
		this->Max_ = CollisionData();
	}
    
    // Reads and stores data from a collision energy file.
    void Read(const string& fileName);
#pragma endregion
#pragma region Accessors
	// Returns a list of collision data.
	vector<CollisionData>& GetData();

	// Returns collision data that contains the
	// overall maximum and minimum values of the data set.
    CollisionData GetMax() const;
    CollisionData GetMin() const;
#pragma endregion
private:
#pragma region Helper Methods
	// Reads and parses for collision energy data.
	CollisionData ReadCollisionData(char* item);

	// Compares a new value with the current
	// maximum and minimum and updates accordingly.
    void UpdateBounds(const CollisionData& item);
#pragma endregion
#pragma region Data Members
    // Stores a list of collision data.
    vector<CollisionData> CollisionList_;
    
	// Stores the minimum and maximum
	// individual values across all data points.
    CollisionData Max_;
    CollisionData Min_;
#pragma endregion
};

// Out stream operator overload for collision data.
ostream& operator<<(ostream& out, CollisionData& data);

// Out stream operator overload for collision energy data.
ostream& operator<<(ostream& out, DataCollisionEnergy& data);

#endif
