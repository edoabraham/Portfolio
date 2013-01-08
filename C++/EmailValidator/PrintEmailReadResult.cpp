/// PrintEmailReadResult.cpp - Email Validation PrintEmailReadResult() Function Implementation
/// Written by Jesse Z. Zhong

#include <iostream>
#include "String.h"

using namespace std;

// Prints the Result of the Email Validation to Screen, Given the Email Address and Result of the Validation Test
void PrintEmailReadResult(String emailAddress, bool result) {

	// The Line that is Going to Print the Result
	String printedLine = "  ";

	// Add Valid or Invalid Depending on Result (Include Numeric Value; Redundant but Provides More Clarity)
	if (result) printedLine += "1 Valid   ";
	else		printedLine += "0 Invalid ";

	// Add the Actual Email Address Tested
	printedLine += emailAddress;

	// Print the Line to Console
	cout << printedLine << endl;
}