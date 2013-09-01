// DataSavepoint.cpp - DataSavepoint Class Method Implementations
// Written by Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "Utilities.h"
#include "DataSavepoint.h"
#pragma endregion
// Read and stores data from a save point file.
void DataSavepoint::Read(const string& fileName) {
	try {
		// Check if the file exists and load it.
		FILE* filePtr = fopen(fileName.c_str(), "r");
		if(filePtr == NULL) 
			return;

		// Record the file name.
		this->FileName_ = fileName;

		// Clear the list of data points.
		this->ParticleList_.clear();
        
		// Traverse the file to find the size.
		fseek(filePtr, 0, SEEK_END);
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
		this->ParticleList_.reserve(numOfLines + 1);

		// Set pointers to the beginning and the end of a 
		// substring, where the end is marked by an end line.
		char* endOfLine = strchr(buffer, '\n');
		char* substring = buffer;

		// Iterate through the buffer to acquire particle data.
		do {
			// Attempt to parse substring for particle data.
			ParticleData item = this->ReadParticleData(substring);
			this->UpdateBounds(item);
			this->ParticleList_.push_back(item);
            
			// Update pointers with the next substring.
			substring = endOfLine + 1;
			endOfLine = strchr(substring, '\n');
            
		} while (endOfLine != NULL);
        
		// Deallocate the buffer.
		delete[] buffer;

		// Set file read status to true.
		this->DataStored_ = true;

	} catch(const string& error) {
		cout << error << endl;
	}
}

// Reads and parses for particle data.
ParticleData DataSavepoint::ReadParticleData(char* item) {
	ParticleData data = ParticleData();
	data.Position.X = atof(Utilities::NullTest(strtok(item, Delimiters)));
	data.Position.Y = atof(Utilities::NullTest(strtok(NULL, Delimiters)));
	data.Position.Z = atof(Utilities::NullTest(strtok(NULL, Delimiters)));
	data.Velocity.X = atof(Utilities::NullTest(strtok(NULL, Delimiters)));
	data.Velocity.Y = atof(Utilities::NullTest(strtok(NULL, Delimiters)));
	data.Velocity.Z = atof(Utilities::NullTest(strtok(NULL, Delimiters)));
	data.GasType = atoi(Utilities::NullTest(strtok(NULL, Delimiters)));
	return data;
}

// Compares a new value with the current
// maximum and minimum and updates accordingly.
void DataSavepoint::UpdateBounds(const ParticleData& item) {

	// Update maximum values.
	this->Max_.Position.X = (this->Max_.Position.X > item.Position.X) 
		? this->Max_.Position.X : item.Position.X;
	this->Max_.Position.Y = (this->Max_.Position.Y > item.Position.Y) 
		? this->Max_.Position.Y : item.Position.Y;
	this->Max_.Position.Z = (this->Max_.Position.Z > item.Position.Z) 
		? this->Max_.Position.Z : item.Position.Z;
	this->Max_.Velocity.X = (this->Max_.Velocity.X > item.Velocity.X) 
		? this->Max_.Velocity.X : item.Velocity.X;
	this->Max_.Velocity.Y = (this->Max_.Velocity.Y > item.Velocity.Y) 
		? this->Max_.Velocity.Y : item.Velocity.Y;
	this->Max_.Velocity.Z = (this->Max_.Velocity.Z > item.Velocity.Z) 
		? this->Max_.Velocity.Z : item.Velocity.Z;

	// Update minimum values.
	this->Min_.Position.X = (this->Min_.Position.X < item.Position.X) 
		? this->Min_.Position.X : item.Position.X;
	this->Min_.Position.Y = (this->Min_.Position.Y < item.Position.Y) 
		? this->Min_.Position.Y : item.Position.Y;
	this->Min_.Position.Z = (this->Min_.Position.Z < item.Position.Z) 
		? this->Min_.Position.Z : item.Position.Z;
	this->Min_.Velocity.X = (this->Min_.Velocity.X < item.Velocity.X) 
		? this->Min_.Velocity.X : item.Velocity.X;
	this->Min_.Velocity.Y = (this->Min_.Velocity.Y < item.Velocity.Y) 
		? this->Min_.Velocity.Y : item.Velocity.Y;
	this->Min_.Velocity.Z = (this->Min_.Velocity.Z < item.Velocity.Z) 
		? this->Min_.Velocity.Z : item.Velocity.Z;
}

// Returns the list of particle data.
vector<ParticleData>& DataSavepoint::GetData() {
	return this->ParticleList_;
}

// Returns the Max and Min Particle Data Values
ParticleData DataSavepoint::GetMax() const {
    return this->Max_;
}
ParticleData DataSavepoint::GetMin() const {
    return this->Min_;
}
#pragma region Out Stream Overloads
// Out stream operator overload for particle data.
ostream& operator<<(ostream& out, ParticleData& data) {
	out << "Position { " << data.Position << " }" << endl;
	out << "Velocity { " << data.Velocity << " }" << endl;
	out << "Gas Type: " << data.GasType << endl;
	return out;
}

// Out stream operator overload for save point data.
ostream& operator<<(ostream& out, DataSavepoint& data) {
	for(int i = 0, j = data.GetData().size(); i < j; i++)
		out << i << " {\n" << data.GetData()[i] << "\n}" << endl;
	return out;
}
#pragma endregion