/// LocalPart.h - Email Local Part Parsing Class Declaration
/// Written by Jesse Z. Zhong

#ifndef __LOCAL_PART_H__
#define __LOCAL_PART_H__

#include "String.h"
#include "CheckRule.h"

// Global Constants
#define MIN_LOCAL_PART_SIZE 1
#define MAX_LOCAL_PART_SIZE 64
#define VALID_LOCAL_PART_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.!#%&'*+-/=?^_`"

using namespace std;

/// This Class Parses the Local
/// Part of an Email Address, 
/// Check if it has Legal Characters
class LocalPart {
public:
	/// Constructor
	LocalPart();

	/// Sets the Address
	void Set(const String& address);

	/// Checks if the Stored Email
	/// Address is Indeed Valid
	bool IsValid();

private:
	/// Stores the Email Address
	String Address_;
};

#endif
