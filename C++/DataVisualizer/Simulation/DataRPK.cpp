// DataRDK.cpp - DataRDK Class Method Implementations
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "DataRPK.h"
#include "Utilities.h"
#pragma endregion
// Reads and stores data from an RPK file.
void DataRPK::Read(const string& fileName) {
    try {
		// Check if the file exists and load it.
		FILE* filePtr = fopen(fileName.c_str(), "r");
		if(filePtr == NULL)
			return;

		// Record the file name.
		this->FileName_ = fileName;

		// Clear the list of RPK data points.
		this->RPKList_.clear();
    
		// Traverse the file to find the size.
		fseek(filePtr, 0, SEEK_END);
		size_t size = ftell(filePtr);
		fseek(filePtr, 0, 0);
    
		// Create a character buffer for storing the file.
		char* buffer = new char[size];
    
		// Store the file into the buffer.
		fread(buffer, size, 1, filePtr);
		fclose(filePtr);
    
		// Set pointers to the beginning and the end of a 
		// substring, where the end is marked by an end line.
		char* endOfLine = strchr(buffer, '\n');
		char* substring = buffer;
    
		// Iterate through the buffer to acquire RPK data.
		do {
			// Attempt to parse substring for an RPK data point.
			RpkDataPoint item = this->ReadDataPoint(substring);
			this->RPKList_.push_back(item);
			this->UpdateBounds(item);
        
			// Update pointers with the next substring.
			substring = endOfLine + 1;
			endOfLine = strchr(substring, '\n');
        
		} while (endOfLine != NULL);
    
		// Deallocate the buffer.
		delete[] buffer;

		// Set file read status to true.
		this->DataStored_ = true;

	} catch(char* ex) {
		cout << ex << endl;
	}
}

// Reads and parses for an RPK data point.
RpkDataPoint DataRPK::ReadDataPoint(char* item) {
	RpkDataPoint data = RpkDataPoint();
	data.Time = atof(Util::NullTest(strtok(item, Delimiters)));
	data.WallRadius = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.WallVelocity = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.Pressure = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.PressureToTime = atof(Util::NullTest(strtok(NULL, Delimiters)));
	return data;
}

// Compares a new value with the current
// maximum and minimum and updates accordingly.
void DataRPK::UpdateBounds(const RpkDataPoint& item) {

	// Test for maximum values.
	this->Max_.Time = (this->Max_.Time > item.Time) 
		? this->Max_.Time : item.Time;
	this->Max_.WallRadius = (this->Max_.WallRadius > item.WallRadius) 
		? this->Max_.WallRadius : item.WallRadius;
	this->Max_.WallVelocity = (this->Max_.WallVelocity > item.WallVelocity)
		? this->Max_.WallVelocity : item.WallVelocity;
	this->Max_.Pressure = (this->Max_.Pressure > item.Pressure)
		? this->Max_.Pressure : item.Pressure;
	this->Max_.PressureToTime = (this->Max_.PressureToTime > item.PressureToTime)
		? this->Max_.PressureToTime : item.PressureToTime;

	// Test for minimum values.
	this->Min_.Time = (this->Min_.Time < item.Time) 
		? this->Min_.Time : item.Time;
	this->Min_.WallRadius = (this->Min_.WallRadius < item.WallRadius) 
		? this->Min_.WallRadius : item.WallRadius;
	this->Min_.WallVelocity = (this->Min_.WallVelocity < item.WallVelocity)
		? this->Min_.WallVelocity : item.WallVelocity;
	this->Min_.Pressure = (this->Min_.Pressure < item.Pressure)
		? this->Min_.Pressure : item.Pressure;
	this->Min_.PressureToTime = (this->Min_.PressureToTime < item.PressureToTime)
		? this->Min_.PressureToTime : item.PressureToTime;
}

// Returns the list of RPK data.
vector<RpkDataPoint>& DataRPK::GetData() {
    return this->RPKList_;
}

// Stores the minimum and maximum
// individual values across all data points.
RpkDataPoint DataRPK::GetMax() const {
    return this->Max_;
}
RpkDataPoint DataRPK::GetMin() const {
    return this->Min_;
}
#pragma region Out Stream Overloads
// Out stream operator overload for RPK data points.
ostream& operator<<(ostream& out, RpkDataPoint& rpkDP) {
	out << "Time:           " << rpkDP.Time << endl;
	out << "WallRadius:     " << rpkDP.WallRadius << endl;
	out << "WallVelocity:   " << rpkDP.WallVelocity << endl;
	out << "Pressure:       " << rpkDP.Pressure << endl;
	out << "PressureToTime: " << rpkDP.PressureToTime << endl;
	return out;
}

// Out stream operator overload for an RPK data set.
ostream& operator<<(ostream& out, DataRPK& data) {
	for(int i = 0, j = data.GetData().size(); i < j; i++)
		out << i << " {\n" << data.GetData()[i] << "\n}" << endl;
	return out;
}
#pragma endregion