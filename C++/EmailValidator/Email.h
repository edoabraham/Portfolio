/// Email.h - Email Address Validation Class Declaration
/// Written by Jesse Z. Zhong

#ifndef __EMAIL_H__
#define __EMAIL_H__

#include "String.h"
#include "LocalPart.h"
#include "DomainPart.h"

using namespace std;

/// Global Const
#define MIN_EMAIL_SIZE 7
#define MAX_EMAIL_SIZE 254

/// Email Class that Handles Parsing
/// of a Single Email Address to Check
/// if it is In Fact Valid
class Email {
public:
	/// Constructor
	Email();

	/// Passes in Email Address
	Email(const String& address);

	/// Checks if Email Stored is Valid
	bool IsValid();

	/// Parses the Address into Local and Domain
	bool Parse();

private:
	/// Stored Email Address
	String Address_;

	/// Local Part Instance for Parsing
	/// the Address's Local Part
	LocalPart Local_;

	/// Domain Part Instance for Parsing
	/// the Address's Domain Part
	DomainPart Domain_;
};

#endif

