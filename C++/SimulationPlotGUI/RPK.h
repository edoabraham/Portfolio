/// RPK.h - RPK Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __RPK_H__
#define __RPK_H__

#include "stdafx.h"
#include "RPKStruct.h"

using namespace std;

class RPK {
public:
    // Constructor
    RPK();
    
    // Parse RPK File for Data
    void Parse(const string& fileName);
    
    // Index Operator
    RPKStruct& operator[](int index);
    
    // Return the Array of Entries
    vector<RPKStruct>& GetArray();
    
    // Returns a Sub Section of the Array
    // Pass the Size of the Subsection
    vector<RPKStruct>& GetSubSection(int size);
    
    // Return the Number of Entries
    int GetNumOfEntries() const;
private:
    // Check Index
    bool CheckIndex(int index) const;
    
    // RPK Data Collection
    vector<RPKStruct> RPKList_;
    
    // Number of Entries
    int NumOfEntries_;
};

#endif
