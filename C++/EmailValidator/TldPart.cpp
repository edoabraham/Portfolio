/// TldPart.cpp - Email TLD Validation Class Methods Implementations
/// Written by Jesse Z. Zhong

#include "TldPart.h"

/// Constructor
TldPart::TldPart() {

}

/// Sets the Address
void TldPart::Set(const String& address) {
	Address_ = address;
}

// Implements TLD validation rules
bool TldPart::IsValid() {

	// Capitalize the TLD in Question
	String potentialTLD = Address_.ToUpper();

	// Check for Matches in the Valid TLD List
	for(int i = 0, j = (int)ValidTLDList_.GetSize(); i < j; i++) 
		if((ValidTLDList_[i] != "") && (ValidTLDList_[i] == potentialTLD))
			return true;

	return false;
}

// Read and Store TLD List from File
void TldPart::PreeloadTLDs(String fileName) {

	// Open the File
	ifstream myFile(fileName.GetText());

	// Check if File Open Correctly
	if(myFile.is_open()) {

		while(!myFile.eof()) {
			// Store Each Line as Long as the Line Isn't Empty
			String line;
			myFile >> line;

			if(!line.Empty()) {

				// Store the Line (Capitalize All Characters)
				ValidTLDList_.PushBack(line.ToUpper());
			}
		}

		// Output that Reading was a Success
		cout << endl << "SUCCESS: " << fileName << " opened properly." << endl << endl
			<< ">> The Program will now use read TLDs to Validate Emails." << endl;

	} else {

		// Output a Message of Failure and Now Using Default List
		cout << endl << "ERROR: " << fileName << " failed to open properly." << endl << endl
			<< ">> Please make sure the file exists and restart the program." << endl;
	}

	// Close the File
	myFile.close();
}

// Valid TLD List
Vector<String> TldPart::ValidTLDList_;