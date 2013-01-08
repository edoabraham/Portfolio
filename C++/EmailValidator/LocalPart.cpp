// LocalPart.cpp - Email Local Part Parsing Class Mehtods Implementations
// Written by Jesse Z. Zhong

#include "LocalPart.h"

/// Constructor
LocalPart::LocalPart() {

}

/// Sets the Address
void LocalPart::Set(const String& address) {
	Address_ = address;
}

/// Checks if the Stored Email
/// Address is Indeed Valid
bool LocalPart::IsValid() {

	// Store the Length of the Local Part
	int localPartLength = Address_.GetLength();

	// 1. Check Size
	if((localPartLength < MIN_LOCAL_PART_SIZE) || (localPartLength > MAX_LOCAL_PART_SIZE))
		return false;

	// 2. Check for Valid Characters
	if(Address_.FindFirstNotOf(VALID_LOCAL_PART_CHARS) != NOT_FOUND) 
		return false;

	// 3. Check Dash Rule and Dot Rule
	if(!(CheckRule('-', Address_) && 
		CheckRule('.', Address_)))
		return false;

	// Return True if All Goes Well
	return true;
}
