/// RDK.cpp - RDK Class Method Implementations
/// Written By Jesse Z. Zhong

#include "RPK.h"

// Constructor
RPK::RPK() {
    NumOfEntries_ = 0;
}

// Parse RPK File for Data
void RPK::Parse(const string& fileName) {
    
    FILE* myFile = fopen(fileName.c_str(), "r");
    if(myFile == NULL) {
        
        std::stringstream s;
        s << "File " << fileName << " could not be opened";
        
        // Throw and Exception
        throw s.str();
        
        return;
    }
    
    fseek(myFile, 0, SEEK_END);
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
        RPKList_.push_back(RPKStruct().Parse(substring));
        
        substring = endOfLine + 1;
        endOfLine = strchr(substring, '\n');
        
    } while (endOfLine != NULL);
    
    // Deallocate Buffer
    delete[] buffer;
    
    // Update Number of Entries
    NumOfEntries_ = RPKList_.size();
}

// Index Operator
RPKStruct& RPK::operator[](int index) {
    if(CheckIndex(index)) {
        return RPKList_[index];
    }
    return *(new RPKStruct);
}

// Return the Array of Entries
vector<RPKStruct>& RPK::GetArray() {
    return RPKList_;
}

// Returns a Sub Section of the Array
vector<RPKStruct>& RPK::GetSubSection(int size) {
    CheckIndex(size - 1);
    
    vector<RPKStruct>* newRPKSub = new vector<RPKStruct>;
    
    for(int i = 0; i < size; i++) {
        newRPKSub->push_back(RPKList_[i]);
    }
    
    return *newRPKSub;
}

// Return the Number of Entries
int RPK::GetNumOfEntries() const {
    return NumOfEntries_;
}

// Check Index
bool RPK::CheckIndex(int index) const {
    if((index < 0) && (index >= NumOfEntries_)) {
        
        // Throw Exception
        string errorMessage = "Invalid Index attempt to access out of bounds in RPK";
        throw errorMessage;
        
        return false;
    }
    return true;
}