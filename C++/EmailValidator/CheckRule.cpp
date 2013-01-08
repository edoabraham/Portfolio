/// CheckRule.cpp - Email Validation CheckRule() Function Definition
/// Written by Jesse Z. Zhong

#include "CheckRule.h"

// Checks if the Symbol Passed Follows the Rules of Email Validation for Symbols
// Rules: Symbol must only appear once in the local portion of the string
//		  in order to qualify as a valid email address.
//		  Symbol cannot appear at the beginning nor the end of the local part.
//		  Email is also valid if there multiple instances of symbols are consecutively
//		  placed in sequence.
// Returns True if All The Rules are Followed
bool CheckRule(char symbol, String part) {

	// Saves the Position of a Discovered Symbol
	int symbolPosition(0);

	// Search for the First Appearance of the Symbol
	symbolPosition = part.Find(symbol, symbolPosition);
	if(symbolPosition != string::npos) {

		// Checks if the Position is the First Character; Returns False if This is the Case
		if(symbolPosition == 0) 
			return false;
		
		// Check if There Exists Other Instances of the Symbol and if They Follow Right After Previous Instance; Return False if This Occurs
		while(symbolPosition != string::npos && (symbolPosition != (part.GetLength() - 1))) {
			if(part[symbolPosition + 1] == symbol) return false;
			symbolPosition = part.Find(symbol, symbolPosition + 1);
		}

		// Checks if the Position is the Last Character; Returns False if This is the Case
		symbolPosition = part.Find(symbol);
		if(symbolPosition == (part.GetLength() - 1))
			return false;

		// Return True if All Checks Are Passed
		return true;

	} else

		// Return True if There is No Instance of the Symbol
		return true;

}