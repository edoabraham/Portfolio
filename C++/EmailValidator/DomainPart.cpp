/// DomainPart.cpp - Email Domain Part Parsing Class Methods Implementations
/// Written by Jesse Z. Zhong

#include "DomainPart.h"

/// Constructor
DomainPart::DomainPart() {

}

/// Sets the Email Address
void DomainPart::Set(const String& address) {
	Address_ = address;
}

/// Implements Domain Validation Rules
bool DomainPart::IsValid() {

	// Parses Address into Sub Domains and TLD's
	return Parse() && SubdomainsAreValid() &&
		TLD_.IsValid();
}

/// Parses Address into Sub Domains and TLD's
bool DomainPart::Parse() {

	// 1. Check the Size
	int domainLength = Address_.GetLength();
	if((domainLength < MIN_DOMAIN_SIZE) || (domainLength > MAX_DOMAIN_SIZE)) 
		return false;

	// 2. Find '.'
	// Extract a Substring Corresponding to Sub Domain
	// and Store in a Vector of Sub Domains
	int atIndex = 0;
	for(int i = 0, j = Address_.GetLength(); (i < j) && (atIndex != NOT_FOUND); i = atIndex + 1) {

		atIndex = Address_.Find('.', i);

		// Store All the Subdomains (Anything that Comes Before a '.')
		if(atIndex != NOT_FOUND) 
			Subdomains_.PushBack(SubdomainPart(Address_.Substring(i, atIndex - i)));

		// 3. The Last Sub Domain is Actually a TLD So it 
		// Needs to be Store in a TLD Data Member (This Comes After Any '.' (No More
		// '.' have been Found))
		else TLD_.Set(Address_.Substring(i));
	}

	return true;
}

/// Checks if Sub Domains are Valid
bool DomainPart::SubdomainsAreValid() {
	for (int i = 0, j = (int)Subdomains_.GetSize(); i < j; i++ )
		if ( !Subdomains_[i].IsValid() )
			return false;
	return true;
}
