/// SnapshotData.h - Snapshot Data Structure Declaration
/// Written By Jesse Z. Zhong

#ifndef __SNAPSHOT_DATA_H__
#define __SNAPSHOT_DATA_H__

#include "stdafx.h"
#include "ShellData.h"

using namespace std;
using namespace rapidjson;

// Enumerate Snapshot Meta Data
enum ESnapshotData {
    SSD_Time = 0,
    SSD_WallRadius,
    SSD_WallVelocity,
    SSD_MaxPressure,
    SSD_AvgPressure,
    SSD_MaxTemperature,
    SSD_AvgTemperature,
    SSD_MaxEnergy,
    SSD_AvgEnergy,
    SSD_NumOfFusions,
    SSD_MaxDensity,
    SSD_AvgDensity
};

// Construct Designed to House
// Simulation Snapshot Data
struct SnapshotData {
    
    // Constructor
    SnapshotData() {
        FoundNumOfGases_ = false;
    }

    // Snapshot Data
	int SnapShotNumber;
	double SimTime;
	double BubbleRadius;

	vector<ShellData> Shells;

	double MeanVelocity;
	double MedianVelocity;
    unsigned long long TotalCollisions;
	unsigned long long TotalCellCrossings;
	unsigned long long TotalWallCollisions;
	unsigned long long TotalConeBoundaryCollisions;
	double FusionRate;

    // Parse the Data of a RapidJSON Document
	static SnapshotData& ParseData(Document& data);
    
    // Number of Gases Read from Data
    int GetNumOfGases() const;
    
    // Get Data of a Snapshot
    double GetData(ESnapshotData value) const;
    
    // Calculate Secondary Data
    void CalculateData();

private:
    // Returns a Vector with All Parsed Shell Data
	vector<ShellData> ParseShellData(Value& shellData);
    
    // Number of Gases
    int NumOfGases_;
    
    // Number of Gases Already Found
    bool FoundNumOfGases_;
    
    ///
    /// META DATA MEMBERS
    
    // Wall Radius of the Bubble
    double WallRadius_;
    
    // Wall Velocity of the Bubble
    double WallVelocity_;
    
    // Maximum Measured Pressure of the Bubble
    double MaxPressure_;
    
    // Average Pressure of the Entire Bubble
    double AvgPressure_;
    
    // Max Temperature
    double MaxTemperature_;
    
    // Average Temperature
    double AvgTemperature_;
    
    // Maximum Collision Energy of Particles
    double MaxEnergy_;
    
    // Average Collision Energy of Particles
    double AvgEnergy_;
    
    // Maximum Density Found in
    // the Shell Layers of the Bubble
    double MaxDensity_;
    
    // Average Density Found Amongst
    // the Shells of the Bubble
    double AvgDensity_;
};

// Out Stream Overload for Snapshot Data
ostream& operator<<(ostream& out, SnapshotData& snapshotData);

#endif

