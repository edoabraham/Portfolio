/// Email.cpp - Email Address Validation Class Methods Implementations
/// Written by Jesse Z. Zhong

#include "Email.h"

/// Constructor
Email::Email() {
	
}

/// Passes in Email Address
Email::Email(const String& address) {
	Address_ = address;
}

/// Checks if Email Stored is Valid
bool Email::IsValid() {

	// Parses the Address into Local and Domain
	return Parse() && Local_.IsValid() &&
		Domain_.IsValid();
}

/// Parses the Address into Local and Domain
bool Email::Parse() {

	// For Performance Sake
	int emailLength = Address_.GetLength();

	// 1. Check the Size: Must be Equal or More than 7 and Equal or Less than 255 (Inverted)
	if((emailLength < MIN_EMAIL_SIZE) || (emailLength > MAX_EMAIL_SIZE)) 
		return false;

	// 2. Find the @ Symbol
	int atIndex = Address_.Find('@');
	if(atIndex == NOT_FOUND) 
		return false;

	// 3. Store Local Part
	Local_.Set(Address_.Substring(0, atIndex));

	// 4. Store Domain Part
	Domain_.Set(Address_.Substring(atIndex + 1));

	// Return True if All Goes Well
	return true;
}