/// TldPart.h - Email TLD Validation Class Declaration
/// Written by Jesse Z. Zhong

#ifndef __TLD_PART_H__
#define __TLD_PART_H__

#include <fstream>
#include "String.h"
#include "Vector.h"

using namespace std;

// Max Size of TLD List
#define MAX_TLD_LIST_SIZE 512

/// Handles the Checking of
/// the TLD an Email by Checking
/// the Address Against an
/// Official TLD List
class TldPart {
public:
	/// Constructor
	TldPart();

	/// Sets the Address
	void Set(const String& address);

	/// Checks if the TLD is Valid
	bool IsValid();

	// Read and Store TLD List from File
	static void PreeloadTLDs(String fileName);

private:
	/// Stored Email Address
	String Address_;

	// Valid TLD List
	static Vector<String> ValidTLDList_;
};

#endif
