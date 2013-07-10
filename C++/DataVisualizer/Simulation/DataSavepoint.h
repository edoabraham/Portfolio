// DataSavepoint.h - DataSavepoint Class Declaration
// Written by Jesse Z. Zhong
#ifndef __DataSavepoint_H__
#define __DataSavepoint_H__
#pragma region Includes
#include "stdafx.h"
#include "Vector3.h"
#include "DataFile.h"
using namespace std;
#pragma endregion
#pragma region Particle Data
// Stores a single particle data point.
struct ParticleData {
	// Constructor
	ParticleData() {
		this->Position = Vector3<double>();
		this->Velocity = Vector3<double>();
		this->GasType = 0;
	}
	Vector3<double> Position;
	Vector3<double> Velocity;
	int GasType;
};
#pragma endregion
// Stores the data from a save point data set.
class DataSavepoint : public DataFile {
public:
#pragma region Instance
	// Constructor
	DataSavepoint() {
		this->ParticleList_ = vector<ParticleData>();
		this->Min_ = ParticleData();
		this->Max_ = ParticleData();
	}

	// Read and stores data from a save point file.
	void Read(const string& fileName);
#pragma endregion
#pragma region Accessors
	// Returns the list of particle data.
	vector<ParticleData>& GetData();

    // Returns particle points that contain the
	// overall maximum and minimum values of the data set.
    ParticleData GetMax() const;
    ParticleData GetMin() const;
#pragma endregion
private:
#pragma region Helper Methods
	// Reads and parses for particle data.
	ParticleData ReadParticleData(char* item);

	// Compares a new value with the current
	// maximum and minimum and updates accordingly.
    void UpdateBounds(const ParticleData& item);
#pragma endregion
#pragma region Data Members
	// Vector List of Particle Data
	vector<ParticleData> ParticleList_;
    
    // Max and Min Data Sets
    ParticleData Max_;
    ParticleData Min_;
#pragma endregion
};

// Out stream operator overload for particle data.
ostream& operator<<(ostream& out, ParticleData& data);

// Out stream operator overload for save point data.
ostream& operator<<(ostream& out, DataSavepoint& data);

#endif


