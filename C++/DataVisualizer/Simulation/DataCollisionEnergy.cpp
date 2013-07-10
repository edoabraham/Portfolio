// DataCollisionEnergy.cpp - Collision Energy Class Methods Implementation
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "Utilities.h"
#include "DataCollisionEnergy.h"
#pragma endregion
// Reads and stores data from a collision energy file.
void DataCollisionEnergy::Read(const string& fileName) {
	try {
		// Check if the file exists and load it.
		FILE* filePtr = fopen(fileName.c_str(), "r");
		if(filePtr == NULL)
			return;

		// Record the file name.
		this->FileName_ = fileName;

		// Clear the list of data points.
		this->CollisionList_.clear();
        
		// Traverse the file to find the size.
		fseek(filePtr,0,SEEK_END);
		size_t size = ftell(filePtr);
		fseek(filePtr, 0, 0);
        
		// Create a character buffer for storing the file.
		char* buffer = new char[size];
        
		// Store the file into the buffer.
		fread(buffer, size, 1, filePtr);
		fclose(filePtr);
        
		// Count the number of lines in the file
		// and allocate the vector with that number.
		// Note: EoF needs to be accounted for.
		//       +1 in order to make room for the EoF.
		int numOfLines = count(buffer, buffer + size, '\n');
		this->CollisionList_.reserve(numOfLines + 1);
        
		// Set pointers to the beginning and the end of a 
		// substring, where the end is marked by an end line.
		char* endOfLine = strchr(buffer, '\n');
		char* substring = buffer;
        
		// Iterate through the buffer to acquire particle data.
		if(endOfLine != NULL) {
			do {
				// Attempt to parse substring for collision data.
				CollisionData item = this->ReadCollisionData(substring);
				this->UpdateBounds(item);
				this->CollisionList_.push_back(item);
                
				substring = endOfLine + 1;
				endOfLine = strchr(substring, '\n');
                
			} while (endOfLine != NULL);
		}
    
		// Deallocate the buffer.
		delete[] buffer;

		// Set file read status to true.
		this->DataStored_ = true;
        
	} catch(char* ex) {
		cout << ex << endl;
	}
}

// Reads and parses for collision energy data.
CollisionData DataCollisionEnergy::ReadCollisionData(char* item) {
	CollisionData data = CollisionData();
	data.Temperature = atof(Util::NullTest(strtok(item, Delimiters)));
	data.Position.X = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.Position.Y = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.Position.Z = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.DeltaVelocity = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.Energy = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.Distance = atof(Util::NullTest(strtok(NULL, Delimiters)));
	data.Gas1Type = atoi(Util::NullTest(strtok(NULL, Delimiters)));
	data.Gas2Type = atoi(Util::NullTest(strtok(NULL, Delimiters)));
	return data;
}

// Returns collision data that contains the
// overall maximum and minimum values of the data set.
CollisionData DataCollisionEnergy::GetMax() const {
    return this->Max_;
}
CollisionData DataCollisionEnergy::GetMin() const {
    return this->Min_;
}

// Compares a new value with the current
// maximum and minimum and updates accordingly.
void DataCollisionEnergy::UpdateBounds(const CollisionData& item) {

	// Update maximum values.
	this->Max_.Temperature = (this->Max_.Temperature > item.Temperature)
		? this->Max_.Temperature : item.Temperature;
	this->Max_.Position.X = (this->Max_.Position.X > item.Position.X)
		? this->Max_.Position.X : item.Position.X;
	this->Max_.Position.Y = (this->Max_.Position.Y > item.Position.Y)
		? this->Max_.Position.Y : item.Position.Y;
	this->Max_.Position.Z = (this->Max_.Position.Z > item.Position.Z)
		? this->Max_.Position.Z : item.Position.Z;
	this->Max_.DeltaVelocity = (this->Max_.DeltaVelocity > item.DeltaVelocity)
		? this->Max_.DeltaVelocity : item.DeltaVelocity;
	this->Max_.Energy = (this->Max_.Energy > item.Energy)
		? this->Max_.Energy : item.Energy;
	this->Max_.Distance = (this->Max_.Distance > item.Distance)
		? this->Max_.Distance : item.Distance;

	// Update minimum values.
	this->Min_.Temperature = (this->Min_.Temperature < item.Temperature)
		? this->Min_.Temperature : item.Temperature;
	this->Min_.Position.X = (this->Min_.Position.X < item.Position.X)
		? this->Min_.Position.X : item.Position.X;
	this->Min_.Position.Y = (this->Min_.Position.Y < item.Position.Y)
		? this->Min_.Position.Y : item.Position.Y;
	this->Min_.Position.Z = (this->Min_.Position.Z < item.Position.Z)
		? this->Min_.Position.Z : item.Position.Z;
	this->Min_.DeltaVelocity = (this->Min_.DeltaVelocity < item.DeltaVelocity)
		? this->Min_.DeltaVelocity : item.DeltaVelocity;
	this->Min_.Energy = (this->Min_.Energy < item.Energy)
		? this->Min_.Energy : item.Energy;
	this->Min_.Distance = (this->Min_.Distance < item.Distance)
		? this->Min_.Distance : item.Distance;
}
#pragma region Out Stream Overloads
// Out stream operator overload for collision data.
ostream& operator<<(ostream& out, CollisionData& data) {
	out << "Temperature:   " << data.Temperature << endl;
	out << "Position { " << data.Position << " }" << endl;
	out << "DeltaVelocity: " << data.DeltaVelocity << endl;
	out << "Energy:        " << data.Energy << endl;
	out << "Distance:      " << data.Distance << endl;
	out << "Gas 1 Type:    " << data.Gas1Type << endl;
	out << "Gas 2 Type:    " << data.Gas2Type << endl;
	return out;
}

// Out stream operator overload for collision energy data.
ostream& operator<<(ostream& out, DataCollisionEnergy& data) {
	for(int i = 0, j = data.GetData().size(); i < j; i++)
		out << i << " {\n" << data.GetData()[i] << "\n}" << endl;
	return out;
}
#pragma endregion
