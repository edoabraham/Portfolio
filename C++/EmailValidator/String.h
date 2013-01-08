/// String.h - String Class Declaration
/// Written By Jesse Z. Zhong

#pragma once

#include <sstream>
#include <iostream>
#include <string>

using namespace std;

#define NOT_FOUND -1
#define UNSPECIFIED_LENGTH -1

// C++ String Class that Encapsulates a ASCII C-String
class String {
public:
	// Default Constructor
	String();

	// MUST HAVE: Copy-Constructor that Performs Deep Copy
	String(const String& source);

	// Init-Constructor to Initialize this String with a C-String
	String(const char* text);

	// Init-Constructor, Allocate this String to Hold Size CHaracters 
	String(int size);

	// Destructor
	~String();

	// Assignment Operator to Perform Deep Copy
	String& operator=(const String& source);

	// Assignment Operator to Assign a C-String to this Source
	String& operator=(const char* text);
	
	// Returns a Reference to a Single Character from this String
	char& operator[](int index) const;

	// Comparison Operators
	bool operator == (const String& compareTo) const;
	bool operator != (const String& compareTo) const;
	bool operator > (const String& compareTo) const;
	bool operator < (const String& compareTo) const;

	// Concatenation Operator
	// For Both String Amending and Character and Character String Amending
	String operator + (const String& aString) const;
	String operator + (const char* aCString) const;
	String& operator += (const String& aString);
	String& operator += (const char* aCString);

	// Returns an Index of aChar in This String Beginning the Search
	// at startPosition; When aChar is not Found, the Function Returns NOT_FOUND
	// Throws an Exception when startPosition is Out of Bounds
	int Find(char aChar, int startPosition = 0) const;

	// Returns a New String that Corresponds to a Substring of this String
	// Beginning at startPostion and length chars long;
	// if length = -1 (not specified) then the Substring Spans from
	// startPosition until the End of This String
	// Throws an Exception when startPosition is Out of Bounds
	String Substring(int startPosition = 0, int length = UNSPECIFIED_LENGTH) const;

	// Returns the Count of Characters in this String; NULL-Terminator is Not Counted
	int GetLength() const;

	// Returns the Count of Characters in C-String; NULL-Terminator is Not Counted
	// Static Means that the Member Function Neither Reads Nor Writes Any of the
	// Class' Data Members
	// String::GetLength("Blah")
	static int GetLength(const char* text);

	// Returns the Text (Read-Only)
	char* GetText() const;

	// Checks if Character is Part of the Alphabet, then Checks if it's
	// Uppercase; If it is, Leave it Alone; If Not, Change it to Uppercase
	// Ignores NON-Alphabetical Characters and Return them as is
	static char ToUpper(const char aChar);

	// Checks if Character is Part of the Alphabet, then Checks if it's
	// Lowercase; If it is, Leave it Alone; If Not, Change it to Uppercase
	// Ignores NON-Alphabetical Characters and Return them as is
	static char ToLower(const char aChar);

	// Full String To Upper Overload
	String ToUpper() const;

	// Full String To Lower Overload
	String ToLower() const;

	// Finds First of Appearance of a Character that is Listed
	// in the Passed String of Characters
	int FindFirstOf(char* characterList, int startingIndex = 0);

	// Finds First Character that Does Not Have an Matches to the 
	// Character List that is Being Passed
	int FindFirstNotOf(char* characterList, int startingIndex = 0);

	// Checks if the String is Empty or Not
	bool Empty() const;

private:
	// Throws a String-type Exception when index goes Out of Bounds
	void CheckBounds(int index, const char* source) const;

	// The Encapsulated C-String
	char* Text_;
	
};

// Stream Output Operator to Print String to Output Stream
ostream& operator<<(ostream& out, const String& text);

// Stream Input Operator to Store Input Stream into a String
istream& operator>>(istream &in, String& text);