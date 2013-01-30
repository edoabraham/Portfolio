/// FileReader.cpp - File Reader Class Method Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "FileReader.h"

using namespace std;

// Constructor
FileReader::FileReader() {
    NumberOfSnapshotFiles_ = 0;
    NumberOfSavepointFiles_ = 0;
    NumberOfCollisionEnergyFiles_ = 0;
    NumberOfSets_ = 0;
    Directory_ = "";
}

FileReader::FileReader(string directory) {
    Directory_ = directory;
}

// Checks the Number of Files
// that are Readable in Sequence - There are No Missing Files
int FileReader::FileCheck() {
    
    // Find All Snapshot Files
	int i = START_VALUE;
	bool lastFileFound = false;
	for(; ((FILE_NUMBER_CAP != -1) ? (bool)(i < (FILE_NUMBER_CAP + START_VALUE)) : true) && (!lastFileFound); i++) {

		// Create File with Number and See if
		// a File Stream can be Create with it
		ifstream mySnapshotFile(CreateSnapshotFileName(i).c_str());

		// Test if Exists
		if(!mySnapshotFile.is_open())
			lastFileFound = true;

		mySnapshotFile.close();
        
        #ifdef RUN_WITH_SAVEPOINTS
        // Create File with Number and See if
		// a File Stream can be Create with it
		ifstream mySavepointFile(CreateSavepointFileName(i).c_str());
        
		// Test if Exists
		if(!mySavepointFile.is_open())
			lastFileFound = true;
        
		mySavepointFile.close();
        #endif
        
        #ifdef RUN_WITH_COLLISION_ENERGY
        // Create File with Number and See if
		// a File Stream can be Create with it
		ifstream myCollisionEnergyFile(CreateCollisionEnergyFileName(i).c_str());
        
		// Test if Exists
		if(!myCollisionEnergyFile.is_open())
			lastFileFound = true;
        
		myCollisionEnergyFile.close();
        #endif
	}
    
    // Store into File Reader
    NumberOfSets_ = i - START_VALUE - 1;
    NumberOfSnapshotFiles_ = NumberOfSets_;
    #ifdef RUN_WITH_SAVEPOINTS
    NumberOfSavepointFiles_ = NumberOfSets_;
    #endif
    #ifdef RUN_WITH_COLLISION_ENERGY
    NumberOfCollisionEnergyFiles_ = NumberOfSets_;
    #endif
    
	return NumberOfSets_;
}

// Returns the Snapshot File
// Name of the Requested Index
string FileReader::SnapshotFileName(int index) const {

	// Return the Requested File Name if Within Range
	if((index >= 0) && (index < NumberOfSnapshotFiles_))
		return CreateSnapshotFileName(index + START_VALUE);

	// Else Print Error Message
	else 
		cout << "Error: Snapshot File Index is not in range; Range : 0 ~ "
			 << (NumberOfSnapshotFiles_ - 1) << endl;

	// Return Empty String
	return "";
}

// Returns the Savepoint File
// Name of the Requiested Index
string FileReader::SavepointFileName(int index) const {
    
    // Return the Requested File Name if Within Range
	if((index >= 0) && (index < NumberOfSavepointFiles_))
		return CreateSavepointFileName(index + START_VALUE);
    
	// Else Print Error Message
	else
		cout << "Error: Savepoint File Index is not in range; Range : 0 ~ "
        << (NumberOfSavepointFiles_ - 1) << endl;
    
	// Return Empty String
	return "";
}

// Returns the Collision Energy
// File Name of the Requested Index
string FileReader::CollisionEnergyFileName(int index) const {
    
    // Return the Requested File Name if Within Range
	if((index >= 0) && (index < NumberOfCollisionEnergyFiles_))
		return CreateCollisionEnergyFileName(index + START_VALUE);
    
	// Else Print Error Message
	else
		cout << "Error: Collision Energy File Index is not in range; Range : 0 ~ "
        << (NumberOfCollisionEnergyFiles_ - 1) << endl;
    
	// Return Empty String
	return "";
}

// Returns the Number of Files
int FileReader::GetMaxNumOfFiles() const {
	return NumberOfSets_;
}

// Creates a Snapshot File Name
string FileReader::CreateSnapshotFileName(int fileNumber) const {
	stringstream fileName;
	int numOfZeros = DIGIT_LENGTH_SNAPSHOTS - (int)log10((double)fileNumber) - 1;

	// Be Sure the Number of Zeros Isn't Negative
	if(NumberOfSnapshotFiles_ >= 0) {

		// Store File Keyword
		fileName << KEYWORD_SNAPSHOTS;

		// Add Zeros
		for(int i = 0; i < numOfZeros; i++)
			fileName << '0';

		// Store Number
		fileName << fileNumber;

		// Add File Extension to Tail
		fileName << FILE_EXTENSION_SNAPSHOTS;
	}

	// Return the Result
	return Directory_ + fileName.str();
}

// Creates a Savepoint File Name
string FileReader::CreateSavepointFileName(int fileNumber) const {
    stringstream fileName;
    int numOfZeros = DIGIT_LENGTH_SAVEPOINTS - 1;
    if(fileNumber !=  0)
        numOfZeros = DIGIT_LENGTH_SAVEPOINTS - (int)log10((double)fileNumber) - 1;
    
    // Be Sure the Number of Zeros Isn't Negative
	if(NumberOfSavepointFiles_ >= 0) {
        
		// Store File Keyword
		fileName << KEYWORD_SAVEPOINTS;
        
		// Add Zeros
		for(int i = 0; i < numOfZeros; i++)
			fileName << '0';
        
        // Store File Number
        fileName << fileNumber;
        
		// Add File Extension to Tail
		fileName << FILE_EXTENSION_SAVEPOINTS;
	}
    
	// Return the Result
	return Directory_ + fileName.str();
    
}

// Creates a Collision Energy File Name
string FileReader::CreateCollisionEnergyFileName(int fileNumber) const {
    stringstream fileName;
    int numOfZeros = DIGIT_LENGTH_COLLISION_ENERGY - 1;
    if(fileNumber !=  0)
        numOfZeros = DIGIT_LENGTH_COLLISION_ENERGY - (int)log10((double)fileNumber) - 1;
    
    // Be Sure the Number of Zeros Isn't Negative
	if(NumberOfCollisionEnergyFiles_ >= 0) {
        
		// Store File Keyword
		fileName << KEYWORD_COLLISION_ENERGY;
        
		// Add Zeros
		for(int i = 0; i < numOfZeros; i++)
			fileName << '0';
        
        // Store File Number
        fileName << fileNumber;
        
		// Add File Extension to Tail
		fileName << FILE_EXTENSION_COLLISION_ENERGY;
	}
    
	// Return the Result
	return Directory_ + fileName.str();
}

// File Directory
string FileReader::GetDirectory() const {
    return Directory_;
}
void FileReader::SetDirectory(string value) {
    Directory_ = value;
}