/// String.cpp - String Class Definition
/// Written By Jesse Z. Zhong

#include "String.h"

// OPTION: For Controlling which Algorithm to Use for Creating Substrings
// AMEND_FOR_SUBSTRING uses the String and Character Amend Operator (+=)
//		   to Combine Characters into an Empty String for the Result
// NO AMEND_FOR_SUBSTRING uses a Preallocated String with an Expanded Size
//		   to Accommodate for the NULL-Terminator. Iterates Through Both
//		   Strings and Copies the Original String's Characters Over to the
//		   Result
//#define AMEND_FOR_SUBSTRING

// Default Constructor
String::String() {

	// Initialize Text
	Text_ = NULL;

	// Provide an Empty C-String
	Text_ = new char[1];
	Text_[0] = '\0';
}

// Copy Constructor
String::String(const String& source) {

	// Initialize Text
	Text_ = NULL;

	// Call the Assignment Operator to Perform Deep Copy
	*this = source;
}

// Init-Constructor to Initialize this String with a C-String
String::String(const char* text) {

	// Initialize Text
	Text_ = NULL;

	// Call the Assignment Operator to Perform Deep Copy
	*this = text;
}

// Init-Constructor, Allocate this String to Hold Size CHaracters 
String::String(int size) {

	// Create New Character Array and Store in Text
	// + 1 to Account for NULL-Terminator
	Text_ = new char[size + 1];
	
	// For Safety Reasons, Add NULL-Terminator
	Text_[size] = '\0';
}

// Destructor
String::~String() {

	// Deallocate Text
	delete[] Text_;
}

// Assignment Operator to Perform Deep Copy
String& String::operator=(const String& source) {

	// Call the Other Assignment Operator to Perform Deep Copy
	*this = source.Text_;
	return *this;
}

// Assignment Operator to Assign a C-String to this Source
String& String::operator=(const char* text) {

	// Dispose of Old Text
	delete[] Text_;

	// + 1 Accounts for NULL-Terminator
	int trueLength = GetLength(text) + 1;

	// Dynamically Allocate Characters on Heap; + 1 Accounts for NULL-Terminator
	Text_ = new char[trueLength];

	// Copy All Characters from Source to Text; + 1 Accounts for NULL-Terminator
	// Should Copy NULL-Terminator
	for(int i = 0; i < trueLength; i++)
		Text_[i] = text[i];

	return *this;
}
	
// Returns a Reference to a Single Character from this String
char& String::operator[](int index) const {

	// Checks if Index Lookup is Within Bounds
	CheckBounds(index, "operator[]");

	// Returns the Character at the index if Within Bounds
	return Text_[index];
}

// Comparison Operators
bool String::operator == (const String& compareTo) const {

	// Store Length of Current String
	int thisStringLength = this->GetLength();

	// Store Length of Passed String
	int passedStringLength = compareTo.GetLength();

	// Compares if Each Character Matches 
	for(int i = 0; (i < thisStringLength) && (i < passedStringLength); i++) {
		if((*this)[i] == compareTo[i]);
		else return false;
	}

	// If the Lengths Match, Return True; Otherwise Return False
	if(thisStringLength == passedStringLength) return true;
	else return false;
}

bool String::operator != (const String& compareTo) const {

	// Return the Opposite of the Result of ==
	return !((*this) == compareTo);
}

bool String::operator > (const String& compareTo) const {

	// Store Length of Current String
	int thisStringLength = this->GetLength();

	// Store Length of Passed String
	int passedStringLength = compareTo.GetLength();

	// Compares if Each Character Matches 
	for(int i = 0; (i < thisStringLength) && (i < passedStringLength); i++) {
		if((*this)[i] == compareTo[i]);
		else if((*this)[i] > compareTo[i]) return true;
		else return false;
	}

	// If Both Strings Match Up to a Certain Point, Check for Sizes
	// If the Current is Greater in Length, Return True; Otherwise Return False
	// NOTE: If Equal in Length, Also False
	if(thisStringLength > passedStringLength) return true;
	else return false;
}

bool String::operator < (const String& compareTo) const {

	// If Current String is NOT Greater than the Passed String OR it's
	// NOT Equal to it, then the Current String Must be Less Than the 
	// Passed String
	return !(((*this) > compareTo) || ((*this) == compareTo));
}

// Concatenation Operator
String String::operator + (const String& aString) const {

	// Using the C-String Override, Amend the Two Strings
	return (*this) + aString.GetText();
}

// Concatenation Operator for C-Strings [Core of All Amend Functions]
String String::operator + (const char* aCString) const {
	
	// Store the Length of this String
	int thisStringLength = this->GetLength();

	// Store the Length of the Passed Character Array
	int passedStringLength = GetLength(aCString);

	// Total Length of the Two Strings Added Together
	int totalStringLength = thisStringLength + passedStringLength;

	// Create a Container for the New Text String; + 1 to Accomadate 
	// NULL-Terminator
	char* result = new char[totalStringLength + 1];

	// String Iterator
	int i = 0;
	
	// Copy Characters of this String Over to the New Container
	for(; i < (thisStringLength); i++)
		result[i] = this->Text_[i];

	// Next, Copy the Characters from the Second String (the C-String)
	for(; i < (totalStringLength); i++)
		result[i] = aCString[i - thisStringLength];

	// Finally, Add the NULL-Terminator (Make Sure to Check Bounds)
	if(i < (totalStringLength + 1)) result[i] = '\0';

	// Return a New String with the Result of the Amended Previous Strings
	return String(result);
}

// += for String and String
String& String::operator += (const String& aString) {
	*this = (*this) + aString;
	return *this;
}

// += for String and C-String
String& String::operator += (const char* aCString) {
	*this = (*this) + aCString;
	return *this;
}

// Returns an Index of aChar in This String Beginning the Search
// at startPosition; When aChar is not Found, the Function Returns NOT_FOUND
// Throws an Exception when startPosition is Out of Bounds
int String::Find(char aChar, int startPosition) const {

	// Checks if startPosition is Within Bounds
	CheckBounds(startPosition, "Find()");

	// Iterate Through the String Text to Find the Character
	// Return the Position of the First Located Character Match
	for(int i = startPosition, j = this->GetLength(); i < j; i++)
		if((*this)[i] == aChar) return i;

	// If the Character is Not Found, Return NOT_FOUND
	return NOT_FOUND;
}

// Returns a New String that Corresponds to a Substring of this String
// Beginning at startPostion and length chars long;
// if length = -1 (not specified) then the Substring Spans from
// startPosition until the End of This String
// Throws an Exception when startPosition is Out of Bounds
String String::Substring(int startPosition, int length) const {

	// Check if Length was Unspecified; 
	// Assign Appropriate Length if so
	if(length == UNSPECIFIED_LENGTH)
		length = this->GetLength() - startPosition;

	// Check the Bounds of the startPosition Added with the length
	CheckBounds(startPosition + length, "Substring()");

#ifdef DEBUG_MODE

	// Check if startPosition is Within Bounds as Well
	CheckBounds(startPosition);
#endif

// Concatenation Operator Implementation
// NOTE: When You have the Time, Test for Speed
#ifdef AMEND_FOR_SUBSTRING
	// Create New String With No Size
	String result("");

	// Add Characters from the Original String to Result
	for(int j = startPosition + length; startPosition < length; startPosition++)
		result += this->Text_[startPosition];

	// Add NULL-Terminator
	result += '\0';
#else
	// Create a New String With the Correct Length for the Substring
	// + 1 for the NULL-Terminator
	String result(length + 1);

	// Copy the String Portion to New String, result
	for(int i = 0; i < length; i++)
		result[i] = this->Text_[i + startPosition];

	// Set NULL-Terminator
	result[length] = '\0';
#endif

	// Return the Result
	return result;
}

// Returns the Count of Characters in this String
int String::GetLength() const {

	// Find the Length Using the Character Array Override
	return GetLength(Text_);
}

// Returns the Count of Characters in C-String; NULL-Terminator is Not Counted
int String::GetLength(const char* text) {
	
	// Counter Iterator for Going through Elements
	int i = 0;

	// Loop Search Until NULL-Terminator is Found
	while(text[i] != '\0') 
		// Iterate Forward (Upward) Counter
		i++;

	return i;
}

// Returns the Text (Read-Only)
char* String::GetText() const {

	// Return the Text of the String
	return (*this).Text_;
}

// Checks if Character is Part of the Alphabet, then Checks if it's
// Uppercase; If it is, Leave it Alone; If Not, Change it to Uppercase
char String::ToUpper(const char aChar) {

	// If the Character is Already Capitalized, Return the Character
	if((aChar >= 'A') && (aChar <= 'Z')) return aChar;

	// If the Character is Lowercase, Return the Character Plus the Offset
	// to Make it Uppercase
	else if((aChar >= 'a') && (aChar <= 'z')) return aChar + ('A' - 'a');
	
	// If Neither Lower or Uppercase (Non-Alphabetical Character) Return the Character
	else return aChar;
}

// Checks if Character is Part of the Alphabet, then Checks if it's
// Lowercase; If it is, Leave it Alone; If Not, Change it to Uppercase
char String::ToLower(const char aChar) {

	// If the Character is Already Lowercase, Leave it as is
	if((aChar >= 'a') && (aChar <= 'z')) return aChar;

	// If the Character is Uppercase, Return the Character Minus the Offset
	// to Make it Lowercase
	if((aChar >= 'A') && (aChar <= 'Z')) return aChar - ('A' - 'a');
	
	// If Neither Lower or Uppercase (Non-Alphabetical Character) Return the Character
	return aChar;
}

// Full String To Upper Overload
String String::ToUpper() const {

	// Result String to Store Original Text
	String newString(*this);

	// Go through the Whole String,
	// Capitalizing All Characters
	for(int i = 0, j = GetLength(); i < j; i++)
		newString[i] = ToUpper(newString[i]);

	// Return String
	return newString;
}

// Full String To Lower Overload
String String::ToLower() const {

	// Result String to Store Original Text
	String newString(*this);

	// Go through the Whole String,
	// Making All Characters Lowercase
	for(int i = 0, j = GetLength(); i < j; i++)
		newString[i] = ToLower(newString[i]);

	// Return String
	return newString;
}

// Finds First of Appearance of a Character that is Listed
// in the Passed String of Characters
int String::FindFirstOf(char* characterList, int startingIndex) {

	// Check index Range
	CheckBounds(startingIndex, "FindFirstOf(char* characterList, int startingIndex = 0)");

	// Iterates Through String and Searches for Matches
	for(int i = startingIndex, k = this->GetLength(); i < k; i++) {

		// Checks For NULL-Terminator in List
		for(int j = 0; characterList[j] != '\0'; j++) {

			// If a Match is Found, Return the Found Position
			if(Text_[i] == characterList[j])
				return i;
		}
	}

	// If Nothing is Found, Return NOT_FOUND
	return NOT_FOUND;
}

// Finds First Character that Does Not Have an Matches to the 
// Character List that is Being Passed
int String::FindFirstNotOf(char* characterList, int startingIndex) {

	// Check index Range
	CheckBounds(startingIndex, "FindFirstOf(char* characterList, int startingIndex = 0)");

	// Iterates Through String and Searches for Matches
	for(int i = startingIndex, k = this->GetLength(); i < k; i++) {

		// Declare Iterator
		int j = 0;

		// Checks For NULL-Terminator in List
		for(; characterList[j] != '\0'; j++) {

			// If a Match is Found, Return the Found Position
			if(Text_[i] == characterList[j]) 
				break;
		}

		// Check if the Iterator Did in Fact
		// Hit a NULL-Terminator
		if(characterList[j] == '\0')
			return i;
	}

	// If Nothing is Found, Return NOT_FOUND
	return NOT_FOUND;
}

// Checks if the String is Empty or Not
bool String::Empty() const {
	return ((GetLength() == 0) || (Text_ == NULL));
}

// Throws a String-type Exception when index goes Out of Bounds
void String::CheckBounds(int index, const char* source) const {

	// Store Length of String
	int length = GetLength();

	// Check for Valid Index
	if((index < 0) || (index >= length + 1)) {
 		stringstream error;
 		error << "String::" << source << " - Index " << index << " is out of bounds (0.." << (length - 1) << ")";
 		string errorMessage = error.str();
 		throw errorMessage;
	}
}

// Stream Output Operator to Print String to Output Stream
ostream& operator<<(ostream& out, const String& myString) {

	// Return the String Out as Character Text
	return out << myString.GetText();
}

// Stream Input Operator to Store Input Stream into a String
istream& operator>>(istream &in, String& text) {
	
	// Pass Full String
	char* cArray;
	in >> (cArray = new char);

	text = String(cArray);

	// Return the Input Operator
	return in;
}