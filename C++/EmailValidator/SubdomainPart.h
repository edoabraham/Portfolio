/// SubdomainPart.h - Email Subdomain Parsing Class Declaration
/// Written by Jesse Z. Zhong

#ifndef __SUBDOMAIN_PART_H__
#define __SUBDOMAIN_PART_H__

#include "String.h"
#include "CheckRule.h"

using namespace std;

// Global Const
#define MIN_DOMAIN_SIZE 1
#define MAX_DOMAIN_SIZE 253
#define VALID_DOMAINNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.!#%&'*+-/=?^_`"

/// This Class is in Charge of
/// Parsing through the Subdomain
/// to Ensure it Follows Valid
/// Email Rules
class SubdomainPart {
public:
	/// Constructor
	SubdomainPart();

	/// Sets the Address
	SubdomainPart(const String& address);

	/// Checks if the Address Follows
	/// the Prescribed Rules
	bool IsValid();

private:
	/// Store the Address Part
	String Address_;
};

#endif

