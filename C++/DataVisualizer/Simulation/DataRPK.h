// DataRPK.h - DataRPK Class Declaration
// Written By Jesse Z. Zhong
#ifndef __Data_RPK_H__
#define __Data_RPK_H__
#pragma region Includes
#include "stdafx.h"
#include "DataFile.h"
using namespace std;
#pragma endregion
#pragma region RPK Data Point
// Stores a single data point 
// of an RPK set of values.
struct RpkDataPoint {
	// Constructor
	RpkDataPoint() {
		this->Time = 0;
		this->WallRadius = 0;
		this->WallVelocity = 0;
		this->Pressure = 0;
		this->PressureToTime = 0;
	}
	double Time;
	double WallRadius;
	double WallVelocity;
	double Pressure;
	double PressureToTime;
};
#pragma endregion
// Stores a set of RPK data points.
class DataRPK : public DataFile {
public:
#pragma region Instance
    // Constructor
    DataRPK() {
		this->RPKList_ = vector<RpkDataPoint>();
		this->Min_ = RpkDataPoint();
		this->Max_ = RpkDataPoint();
	}

	// Init-Constructor
	DataRPK(const string& fileName) 
		: DataFile(fileName) {
			this->Read(fileName);
	}
    
    // Reads and stores data from an RPK file.
    virtual void Read(const string& fileName);
#pragma endregion
#pragma region Accessors
    // Returns the list of RPK data.
    vector<RpkDataPoint>& GetData();
    
    // Returns RPK points containing
	// members with the maximum and
	// minimum values of the data points.
    RpkDataPoint GetMax() const;
    RpkDataPoint GetMin() const;
#pragma endregion
private:
#pragma region Helper Methods
	// Reads and parses for an RPK data point.
	RpkDataPoint ReadDataPoint(char* item);

	// Compares a new value with the current
	// maximum and minimum and updates accordingly.
	void UpdateBounds(const RpkDataPoint& item);
#pragma endregion
#pragma region Data Members
    // Stores a list of RPK data points.
    vector<RpkDataPoint> RPKList_;
    
    // Stores the minimum and maximum
	// individual values across all data points.
    RpkDataPoint Max_;
    RpkDataPoint Min_;
#pragma endregion
};

// Out stream operator overload for RPK data points.
ostream& operator<<(ostream& out, RpkDataPoint& rpkDP);

// Out stream operator overload for an RPK data set.
ostream& operator<<(ostream& out, DataRPK& data);

#endif
