/// ParseSavepoint.cpp - Parse Savepoint Class Method Implementations
/// Written by Jesse Z. Zhong

#include "stdafx.h"
#include "Savepoint.h"

// Number of Consecutive Doubles
const int NUM_OF_DOUBLES = 6;

// Number of Consecutive Integers
const int NUM_OF_INTEGERS = 1;

// Size of Double
const int DOUBLE_SIZE = sizeof(double);

// Size of Integer
const int INTEGER_SIZE = sizeof(int);

// Byte Length of a Binary File Line
const int LINE_BYTE_LENGTH = NUM_OF_DOUBLES *
    DOUBLE_SIZE + NUM_OF_INTEGERS * INTEGER_SIZE;

// Constructor
Savepoint::Savepoint() {
    
}

// Init-Constructor
Savepoint::Savepoint(const string& fileName) {
    ReadFile(fileName);
}

// Read and Parse a Savepoint File
bool Savepoint::ReadFile(const string& fileName) {
    
    // Clear and Initialize Vector
    ParticleDataList_ = vector<ParticleDataStruct>();

	try {
        
        FILE* myFile = fopen(fileName.c_str(), "r");
        if(myFile == NULL) {
            
            // Throw and Exception
            std::string exceptionMessage = "File " + fileName + " could not be opened";
            throw exceptionMessage;
        }
        
        fseek(myFile,0,SEEK_END);
        size_t fileSize = ftell(myFile);
        fseek(myFile, 0, 0);
        
        char* buffer = new char[fileSize];
        
        fread(buffer, fileSize, 1, myFile);
        fclose(myFile);

        // Pointers to Beginning and End of a Substring Line
        char* endOfLine = strchr(buffer, '\n');
        char* substring = buffer;

		// Read Through the File Stream
		do {

            // Parse and Store into Vector
            ParticleDataStruct partData = ParticleDataStruct();
            partData.ParseLine(substring);
            UpdateMaxAndMin(partData);
            ParticleDataList_.push_back(partData);
            
            substring = endOfLine + 1;
            endOfLine = strchr(substring, '\n');
            
		} while (endOfLine != NULL);
        
        // Deallocate Buffer
        delete[] buffer;

	} catch(string error) {

		// Print Exception
		cout << error << endl;
	}
    
    // Update Size
    Size_ = ParticleDataList_.size();

	return true;
}

// Index Operator Overload
ParticleDataStruct& Savepoint::operator[](const int index) {
    if((index < 0) || (index >= Size_))
        throw "Out of Bounds of Savepoints Collection List.";
    return ParticleDataList_[index];
        
}

// Returns the Number of Particle Data Entries
int Savepoint::GetSize() const {
    return Size_;
}

// Returns the Max and Min Particle Data Values
ParticleDataStruct Savepoint::GetMax() const {
    return Max_;
}
ParticleDataStruct Savepoint::GetMin() const {
    return Min_;
}

// Does a Comparison for Max and Min and Updates
// Their Values with Any Necessary Changes
void Savepoint::UpdateMaxAndMin(ParticleDataStruct value) {
    
    // Update Max Values
    ParticleDataStruct::Max(Max_, value);
    
    // Update Max Values
    ParticleDataStruct::Min(Min_, value);
}