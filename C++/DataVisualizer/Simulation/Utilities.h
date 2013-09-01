// Utilities.h - Utility Template Functions
// Written By Jesse Z. Zhong
#ifndef __Utilities_H__
#define __Utilities_H__
#include "stdafx.h"
using namespace std;
using namespace rapidjson;

namespace Utilities {

	// Creates a map for a

    // Creates an Array Out of Non-Array 
    // Document Values from Rapid JSON
    template<typename T>
    vector<T> ParseAsArray(const Value& values) {
        
        // Create Return Vector
        vector<T> tempVector;
        
        // Iterate through the Values and Store int the Vector
        for(Value::ConstMemberIterator it = values.MemberBegin();
            it != values.MemberEnd(); it++) {
            
            // Temporary Variable for Storing Data
            T pulledData;
            
            // Check for T's Type
            
            // Double
            if((typeid(T) == typeid(double)) && it->value.IsDouble())
                tempVector.push_back(it->value.GetDouble());
            
            // Signed Integer
            else if(((typeid(T) == typeid(int)) || (typeid(T) == typeid(double))) && it->value.IsInt())
                tempVector.push_back((T)it->value.GetInt());
            
            // Unsigned Integer
            else if((typeid(T) == typeid(unsigned int)) && it->value.IsUint())
                tempVector.push_back(it->value.GetUint());
            
            // Unsigned Long Long
            else if((typeid(T) == typeid(unsigned long long)) && it->value.IsUint64())
                tempVector.push_back(it->value.GetUint64());
            
            // TODO: Add More Type Support; Type Support for Value Object
        } 
        
        // Return the Vector
        return tempVector;
    }

    // Test if a c-array is null; returns the c-array if it
	// is not null and returns a new zero array if it is null.
    static inline char* NullTest(char* cArray) {
        if(cArray != NULL)
            return cArray;
        return new char('0');
    }

}

#endif
