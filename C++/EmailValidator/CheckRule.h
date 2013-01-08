/// CheckRule.h - Email Validation CheckRule() Function Declaration
/// Written by Jesse Z. Zhong

#ifndef __CHECK_RULE_FUNCTION__
#define __CHECK_RULE_FUNCTION__

#include <iostream>
#include "String.h"

using namespace std;

// Checks if the Symbol Passed Follows the Rules of Email Validation for Symbols
// Rules: Symbol must only appear once in the local portion of the string
//		  in order to qualify as a valid email address.
//		  Symbol cannot appear at the beginning nor the end of the local part.
//		  Email is also valid if there multiple instances of symbols are consecutively
//		  placed in sequence.
// Returns True if All The Rules are Followed
bool CheckRule(char symbol, String part);

#endif
