/// SubdomainPart.cpp - Email Subdomain Parsing Class Methods Implementations
/// Written by Jesse Z. Zhong

#include "SubdomainPart.h"

/// Constructor
SubdomainPart::SubdomainPart() {

}

/// Sets the Address
SubdomainPart::SubdomainPart(const String& address) {
	Address_ = address;
}

/// Checks if the Address Follows
/// the Prescribed Rules
bool SubdomainPart::IsValid() {
	// 1. Check the Size
	int domainLength = Address_.GetLength();
	if((domainLength < MIN_DOMAIN_SIZE) || (domainLength > MAX_DOMAIN_SIZE)) 
		return false;

	// 2. Make Sure All Characters are Acceptable
	if(Address_.FindFirstNotOf(VALID_DOMAINNAME_CHARS) != NOT_FOUND) 
		return false;

	// 3. Check if Domain Name Follows the Dash and Period Rules
	if(!(CheckRule('-', Address_) && CheckRule('.', Address_))) 
		return false;

	// Return True if All Goes Well
	return true;
}
