/// Homework 3 : Object-Oriented Implementation
/// main.cpp - Email Validation Program Main Entry
/// Written by Jesse Z. Zhong

/// Standard Includes
#include <iostream>
#include <fstream>
#include <string>

/// Project Includes
#include "Email.h"
#include "TLDPart.h"
#include "String.h"

using namespace std;

// Prints the Console Program Title Header
void PrintHeader();

// Prints the Result of the Email Validation to Screen, 
// Given the Email Address and Result of the Validation Test
void PrintEmailReadResult(String emailAddress, bool result);

void main() {

	try {

		// Print Introduction Header
		PrintHeader();

		// Attempt to Store TLD List
		TldPart::PreeloadTLDs("ValidTLDs.txt");

		// 1. Open Input File Email.txt
		ifstream in("Email.txt");

		// 2. Open the Output File Result.txt
		ofstream out("Result.txt");

		// Check if Files are Open or Not
		if(in.is_open() && out.is_open()) {

			// Tell User File Read and Creations were Successful
			cout << endl << "SUCCESS: Files were successfully opened." << endl << endl;
			cout << ">> Beginning to Process Files for Valid Emails..." << endl << endl;


		// 3. Repeat While Not at the End of the Input File
		while (!in.eof()) {

			// Use STL String for getline()
			string emailAddress;

			// 4. Read an Email Address (Entire Line) From the Input File
			getline(in, emailAddress);

			// 4a. Check for Empty Lines; Continues Email Validation if Not Empty; Skips if True
			if(!emailAddress.empty()) {

				// Email is the Email Address Validation Class
				Email email(emailAddress.c_str());

				// 5. Validate the Email Address
				bool isValid = email.IsValid();

				// 6. If the Email Address is Valid Write 1 to the Output File
				// else Write Zero
				out << isValid << "\t" << emailAddress << endl;

				// Print the Results to Screen
				PrintEmailReadResult(emailAddress.c_str(), isValid);
			}
		}
			// Tell User that the Run was Successful and All Emails were Read
			cout << endl << ">> Process Finished! Files were successfully scanned." << endl << endl;
			cout << ">> You may now close the program." << endl << endl;

		} else {
			// Tell User that Files can't be Opened
			cout << endl << "ERROR: The Program could not open/find Email.txt or Result.txt." << endl;
			cout <<			"       Please make sure you have Email.txt and make sure both of " << endl
				<<			"       the files are not Read-Only or already opened." << endl << endl;
		}

		// 7. Close the Files (will be Closed Automatically)
		in.close();
		out.close();

	} catch (std::string exceptions) {
		cout << exceptions;
	}

	system("pause");
}