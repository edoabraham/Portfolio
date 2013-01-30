/// Utilities.h - Utility Template Functions
/// Written By Jesse Z. Zhong

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "stdafx.h"

using namespace std;
using namespace rapidjson;

namespace Utilities {

    ///
    /// CONSTANTS
    ///

    // Golden Ratio
    const double PHI = 1.6180339887;

    // Pi
    const double PI = 3.14159265359;

    ///
    /// FUNCTIONS
    ///

    // Creates an Array Out of Non-Array 
    // Document Values from Rapid JSON
    template<typename T>
    vector<T> ParseAsArray(const Value& values) {
        
        // Create Return Vector
        vector<T> tempVector;
        
        // Iterate through the Values and Store int the Vector
        for(Value::MemberIterator myIterator = (Value::MemberIterator) values.MemberBegin();
            myIterator != values.MemberEnd(); myIterator++) {
            
            // Temporary Variable for Storing Data
            T pulledData;
            
            // Check for T's Type
            
            // Double
            if((typeid(T) == typeid(double)) && myIterator->value.IsDouble())
                pulledData = myIterator->value.GetDouble();
            
            // Signed Integer
            if((typeid(T) == typeid(int)) && myIterator->value.IsInt())
                pulledData = myIterator->value.GetInt();
            
            // Unsigned Integer
            if((typeid(T) == typeid(unsigned int)) && myIterator->value.IsUint())
                pulledData = myIterator->value.GetUint();
            
            // Unsigned Long Long
            if((typeid(T) == typeid(unsigned long long)) && myIterator->value.IsUint())
                pulledData = myIterator->value.GetUint64();
            
            // TODO: Add More Type Support; Type Support for Value Object
            
            // Push Data into Vector
            tempVector.push_back(pulledData);
        }
                
        
        // Return the Vector
        return tempVector;
    }

    // Finds a NULL Reference in a C-Array
    static inline char* TestForNull(char* cArray) {
        if(cArray != NULL)
            return cArray;
        return new char('0');
    }

}

#endif
