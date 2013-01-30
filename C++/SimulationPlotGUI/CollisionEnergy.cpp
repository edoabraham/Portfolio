/// CollisionEnergy.cpp - Collision Energy Class Methods Implementation
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "CollisionEnergy.h"

// Constructor
CollisionEnergy::CollisionEnergy() {
    Size_ = 0;
}

// Init-Constructor
CollisionEnergy::CollisionEnergy(const string& fileName) {
    ReadFile(fileName);
}

// Parses a Collision Energy File
bool CollisionEnergy::ReadFile(const string& fileName) {
    
    // Clear and Initialize Vector
    CollisionList_ = vector<CollisionEnergyData>();
    
    try {
        
        FILE* myFile = fopen(fileName.c_str(), "r");
        if(myFile == NULL) {
            
            // Throw and Exception
            std::string exceptionMessage = "File " + fileName + " could not be opened";
            throw exceptionMessage;
            return false;
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
        if(endOfLine != NULL) {
            do {
                
                // Parse and Store into Vector
                CollisionEnergyData newData = CollisionEnergyData();
                newData.ParseLine(substring);
                UpdateMaxAndMin(newData);
                CollisionList_.push_back(newData);
                
                substring = endOfLine + 1;
                endOfLine = strchr(substring, '\n');
                
            } while (endOfLine != NULL);
        }
    
        // Deallocate Buffer
        delete[] buffer;
        
	} catch(string error) {
        
		// Print Exception
		cout << error << endl;
	}
    
    // Update Size
    Size_ = CollisionList_.size();
    
    return true;
}

// Index Operator Overload
CollisionEnergyData& CollisionEnergy::operator[](const int index) {
    if((index < 0) || (index >= Size_))
        throw "Out of Bounds of Collision Energy Collection list.";
    return CollisionList_[index];
}

// Returns the Number of Entries in the Collection List
int CollisionEnergy::GetSize() const {
    return Size_;
}

// Returns the Max and Min Collision Data Values
CollisionEnergyData CollisionEnergy::GetMax() const {
    return Max_;
}
CollisionEnergyData CollisionEnergy::GetMin() const {
    return Min_;
}

// Does a Comparison for Max and Min and Updates
// Their Values with Any Necessary Changes
void CollisionEnergy::UpdateMaxAndMin(CollisionEnergyData value) {
    
    // Max Comparison
    CollisionEnergyData::Max(Max_, value);
    
    // Min Comparison
    CollisionEnergyData::Min(Min_, value);
    
}

// Out Stream Overload
ostream& operator<<(ostream& out, CollisionEnergy& ce) {
    if(ce.GetSize() > 0)
        for(int i = 0, j = ce.GetSize(); i < j; i++)
            cout << ce[i] << endl;
    return out;
}
