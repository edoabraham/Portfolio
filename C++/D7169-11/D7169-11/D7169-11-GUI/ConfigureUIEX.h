// ConfigureUIEX.h - ConfigureUIEX Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __ConfigureUIEX_h__
#define __ConfigureUIEX_h__
#include "stdafx.h"
#include "ui_ConfigureUI.h"

// User Interface
namespace Ui {

	// The implementation of the configure box,
	// with settings to change a signal display.
	class ConfigureUIEX : public ConfigureUI {
	public:
		// Constructor
		ConfigureUIEX() {
			
		}

		// Initialize widget settings.
		void Init(QObject* parent = NULL);
	};
}

#endif // End: ConfigureUIEX