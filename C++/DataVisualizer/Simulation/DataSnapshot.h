/// Snapshot.h - Snapshot File Class Declaration
/// Written By Jesse Z. Zhong
#ifndef __DataSnapshot_H__
#define __DataSnapshot_H__
#pragma region Includes
#include "stdafx.h"
#include "DataFile.h"
using namespace std;
using namespace rapidjson;
#pragma endregion
#pragma region Shell Data
// Stores the information pertaining
// to each cell layer in the simulated system.
struct ShellData {
	// Constructor
	ShellData() {
		this->Radius = 0;
		this->NumberOfParticles = 0;
		this->Density = 0;
		this->Temperature = vector<double>();
		this->Velocity = vector<double>();
		this->Ionization = vector<double>();
		this->Percent =  vector<double>();
		this->GasTypes = 0;
	}
	double Radius;
	int NumberOfParticles;
	double Density;
	vector<double> Temperature;
	vector<double> Velocity;
	vector<double> Ionization;
	vector<double> Percent;
	int GasTypes;
};
#pragma endregion
// Stores simulation snapshot data.
class DataSnapshot : public DataFile {
public:
#pragma region Instance
	// Constructor
	DataSnapshot() {

		// Initialize all field members.
		this->SnapshotID_ = 0;
		this->SimulationTime_ = 0;
		this->BubbleRadius_ = 0;
		this->MeanVelocity_ = 0;
		this->MedianVelocity_ = 0;
		this->TotalCollisions_ = 0;
		this->TotalCellCrossings_ = 0;
		this->TotalWallCollisions_ = 0;
		this->TotalConeBoundaryCollisions_ = 0;
		this->FusionRate_ = 0;
		this->ShellData_ = vector<ShellData>();
		this->GasTypes_ = 0;
		this->WallRadius_ = 0;
		this->WallVelocity_ = 0;
		this->MaxPressure_ = 0;
		this->AvgPressure_ = 0;
		this->MaxTemperature_ = 0;
		this->AvgTemperature_ = 0;
		this->MaxEnergy_ = 0;
		this->AvgEnergy_ = 0;
		this->MaxDensity_ = 0;
		this->AvgDensity_ = 0;
	}

	// Parse the File
	void Read(const string& fileName);
#pragma endregion
#pragma region Accessors
	// Return primary data fields.
	int GetSnapshotID() const { return this->SnapshotID_; }
	double GetSimulationTime() const { return this->SimulationTime_; }
	double GetBubbleRadius() const { return this->BubbleRadius_; }
	double GetMeanVelocity() const { return this->MeanVelocity_; }
	double GetMedianVelocity() const { return this->MedianVelocity_; }
	unsigned long long GetTotalCollisions() const { return this->TotalCollisions_; }
	unsigned long long GetTotalCellCrossings() const { return this->TotalCellCrossings_; }
	unsigned long long GetTotalWallCollisions() const { return this->TotalWallCollisions_; }
	unsigned long long GetTotalConeBoundaryCollisions() const { return this->TotalConeBoundaryCollisions_; }
	double GetFusionRate() const { return this->FusionRate_; }

	// Returns the list of shell data.
	vector<ShellData>& GetShellData() { return this->ShellData_; }

	// Return metadata fields.
	double GetWallRadius() const { return this->WallRadius_; }
	double GetWallVelocity() const { return this->WallVelocity_; }
	double GetMaxPressure() const { return this->MaxPressure_; }
	double GetAvgPressure() const { return this->AvgPressure_; }
	double GetMaxTemperature() const { return this->MaxTemperature_; }
	double GetAvgTemperature() const { return this->AvgTemperature_; }
	double GetMaxEnergy() const { return this->MaxEnergy_; }
	double GetAvgEnergy() const { return this->AvgEnergy_; }
	double GetMaxDensity() const { return this->MaxDensity_; }
	double GetAvgDensity() const { return this->AvgDensity_; }
#pragma endregion
private:
#pragma region Helper Methods
	// Reads and parses shell data.
	ShellData ReadShellData(Value& item);
#pragma endregion
#pragma region Data Members
	// Primary data fields.
	int SnapshotID_;
	double SimulationTime_;
	double BubbleRadius_;
	double MeanVelocity_;
	double MedianVelocity_;
	unsigned long long TotalCollisions_;
	unsigned long long TotalCellCrossings_;
	unsigned long long TotalWallCollisions_;
	unsigned long long TotalConeBoundaryCollisions_;
	double FusionRate_;
	vector<ShellData> ShellData_;
	int GasTypes_;

	// Metadata fields.
	double WallRadius_;
	double WallVelocity_;
	double MaxPressure_;
	double AvgPressure_;
	double MaxTemperature_;
	double AvgTemperature_;
	double MaxEnergy_;
	double AvgEnergy_;
	double MaxDensity_;
	double AvgDensity_;
#pragma endregion
};

// Out stream operator overload for shell data.
ostream& operator<<(ostream& out, ShellData& shellData);

// Out stream operator overload for snapshots.
ostream& operator<<(ostream& out, DataSnapshot& data);
#endif
