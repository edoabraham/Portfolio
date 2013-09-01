// PreferenceUIEX.h - PreferenceUIEX Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __PreferenceUIEX_h__
#define __PreferenceUIEX_h__
#include "stdafx.h"
#include "ui_PreferenceUI.h"

// User Interface
namespace Ui {

	// The extension of the preference form,
	// which is used for listing user app settings.
	class PreferenceUIEX : public PreferenceUI {
	public:
		// Constructor
		PreferenceUIEX() {

		}
	
		// Initialize the form's auxiliary widgets.
		void Init(QObject* parent = NULL);
	};
}

#endif // End: PreferenceUIEX