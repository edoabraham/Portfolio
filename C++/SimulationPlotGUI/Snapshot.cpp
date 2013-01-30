/// ParseSnapshot.h - Parse Snapshot File Class Method Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "Snapshot.h"

using namespace rapidjson;

const int BUFFER_SIZE = 4096;

// Constructor
Snapshot::Snapshot() {

}

// Init-Constructor
Snapshot::Snapshot(const string& fileName) {
    ParseFile(fileName);
}

// Parse the File
bool Snapshot::ParseFile(const string& fileName) {
	
    FILE* myFile = fopen(fileName.c_str(), "r");
    if(myFile == NULL) {
        
        // Throw and Exception
        std::string exceptionMessage = "File " + fileName + " could not be opened";
        throw exceptionMessage;
    }
    
    char buffer[BUFFER_SIZE];
    
    FileReadStream myFileReadStream(myFile, buffer, BUFFER_SIZE);
    
    // Create a Document for Storing the JSON Data
    Document myDocument;

	// Attempt to Parse the JSON and Store into myDocument
    if(myDocument.ParseStream<0, UTF8<> >(myFileReadStream).HasParseError()) {
        
        // Throw Exception
        std::string exceptionMessage = "Error when Parsing file " + fileName;
        throw exceptionMessage;
    }

    // Close File
    fclose(myFile);
    
    // Return the Parsed Read Data
    SnapshotData_ = SnapshotData::ParseData(myDocument);
    
    // Calculate Secondary Data
    SnapshotData_.CalculateData();
    
    return true;
}

// Return the SnapshotData
SnapshotData& Snapshot::GetSnapshotData() {
	return this->SnapshotData_;
}

const int LENGTH_OF_INT = 4;

