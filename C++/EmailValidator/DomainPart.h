/// DomainPart.h - Email Domain Part Parsing Class Declaration
/// Written by Jesse Z. Zhong

#ifndef __DOMAIN_PART_H__
#define __DOMAIN_PART_H__

#include "SubdomainPart.h"
#include "TldPart.h"
#include "String.h"
#include "Vector.h"

using namespace std;

/// Global Const
#define MIN_DOMAIN_SIZE 1
#define MAX_DOMAIN_SIZE 253

/// This Class is in Charge of Parsing
/// the Domain Part of an Email Address,
/// Ensuring that it has a Valid Sub
/// Domain and TLD
class DomainPart {
public:
	/// Constructor
	DomainPart();

	/// Sets the Email Address
	void Set(const String& address);

	// Implements Domain Validation Rules
	bool IsValid();

	/// Parses Address into Sub Domains and TLD's
	bool Parse();

	/// Checks if Sub Domains are Valid
	bool SubdomainsAreValid();

private:
	/// String for Storing Address That 
	/// is to be Parsed
	String Address_;

	/// List of Legal Sub Domains
	Vector<SubdomainPart> Subdomains_;

	/// Divided TLD Part of Address
	TldPart TLD_;
};

#endif

