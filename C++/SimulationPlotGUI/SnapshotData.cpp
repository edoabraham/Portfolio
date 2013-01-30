/// SnapshotData.cpp - Snapshot Data Structure Method Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "SnapshotData.h"

// Parses the Data from a RapidJson Document
SnapshotData& SnapshotData::ParseData(Document& data) {
    
    // Declare a Temporary Instance
    SnapshotData* temp = new SnapshotData();
    
    // Data
    temp->SnapShotNumber = data["snap_shot"].GetInt();
    temp->SimTime = data["t"].GetDouble();
    temp->BubbleRadius = data["r"].GetDouble();
    
    // Check if Array Exists
    assert(data["bins"].IsArray());
    
    // Parse for Shell Data With Reference
    Value& shellData = data["bins"];
    temp->Shells = temp->ParseShellData(shellData);
    
    // Calculated Data
    //temp->MeanVelocity = data["mean_velocity"].GetDouble();
    //temp->MedianVelocity = data["median_velocity"].GetDouble();
    //temp->TotalCollisions = data["TotalCollisions"].GetUint64();
    //temp->TotalCellCrossings = data["TotalCellCrossings"].GetUint64();
    //temp->TotalWallCollisions = data["TotalWallCollisions"].GetUint64();
    //temp->TotalConeBoundaryCollisions = data["TotalConeBoundaryCollisions"].GetUint64();
    //temp->FusionRate = data["FusionRate"].GetDouble();
    
    // Return This Instance
    return *temp;
}

// Number of Gases Read from Data
int SnapshotData::GetNumOfGases() const {
    return NumOfGases_;
}

// Parses Shell Data into a Vector of ShellData
vector<ShellData> SnapshotData::ParseShellData(Value& shellData) {

    // Store into a Temporary Array
    vector<ShellData> temp;
    for(SizeType i = 0, j = shellData.Size(); i < j; i++) {
        temp.push_back(ShellData::Parse(shellData[i]));
        
        // Check if Number of Gases has been Set
        if(FoundNumOfGases_) {
            
            // Check for Consistency
            if(NumOfGases_ != temp[i].NumOfGases) {
                
                // Throw Exception
                std::string exceptionMessage = "Inconsistent Number of Gases within Snapshot";
                throw exceptionMessage;
            }
            
        // Set the Gas Number
        } else {
            NumOfGases_ = temp[i].NumOfGases;
            FoundNumOfGases_ = true;
        }
    }
    
    // Return the Vector
	return temp;
}

// Calculate Secondary Data
void SnapshotData::CalculateData() {
    // Temperature
    double temperatureSum = 0;
    double temperatureMax = 0;
    
    // Density
    double densitySum = 0;
    double densityMax = 0;
    
    // Iterate Through for Subs and Max Comparisons
    int j = Shells.size();
    int numOfGases = 0;
    for(int i = 0; i < j; i++) {
        
        // Individual Gases in Shells
        for(int k = 0, l = Shells[i].NumOfGases; k < l; k++) {
            
            // Temperature Sum
            temperatureSum += Shells[i].Temperature[k];
            
            // Find Temperature Max
            temperatureMax = max(temperatureMax, Shells[i].Temperature[k]);
            
            // Update Number of Gases (NOTE: This needs to be changed.)
            numOfGases = Shells[i].NumOfGases;
        }
        
        // Shells
        // Density Sum
        densitySum += Shells[i].Density;
        
        // Find Density Max
        densityMax = max(densityMax, Shells[i].Density);
    }
    AvgDensity_ = densitySum / j;
    MaxDensity_ = densityMax;
    AvgTemperature_ = temperatureSum / (j * numOfGases);
    MaxTemperature_ = temperatureMax;
}

// Get Data of a Snapshot
double SnapshotData::GetData(ESnapshotData value) const {
    switch(value) {
        case SSD_Time:
            return SimTime;
            break;
            
        case SSD_WallRadius:
            return WallRadius_;
            break;
            
        case SSD_WallVelocity:
            return WallVelocity_;
            break;
            
        case SSD_MaxPressure:
            return MaxPressure_;
            break;
            
        case SSD_AvgPressure:
            return AvgPressure_;
            break;
            
        case SSD_MaxTemperature:
            return MaxTemperature_;
            break;
            
        case SSD_AvgTemperature:
            return AvgTemperature_;
            break;
            
        case SSD_MaxEnergy:
            return MaxEnergy_;
            break;
            
        case SSD_AvgEnergy:
            return AvgEnergy_;
            break;
            
        case SSD_MaxDensity:
            return MaxDensity_;
            break;
            
        case SSD_AvgDensity:
            return AvgDensity_;
            break;
            
            default:
            return 0;
            break;
    }
    return 0;
}

// Out Stream Overload
ostream& operator<<(ostream& out, SnapshotData& snapshotData) {

	out << snapshotData.SnapShotNumber << endl;
	out << snapshotData.SimTime << endl;
	out << snapshotData.BubbleRadius << endl;

	for(int i = 0, j = snapshotData.Shells.size(); i < j; i++)
		out << snapshotData.Shells[i] << endl;

	out << snapshotData.MeanVelocity << endl;
	out << snapshotData.MedianVelocity << endl;
	out << snapshotData.TotalCollisions << endl;
	out << snapshotData.TotalCellCrossings << endl;
	out << snapshotData.TotalWallCollisions << endl;
	out << snapshotData.TotalConeBoundaryCollisions << endl;
	out << snapshotData.FusionRate << endl;

	return out;
}