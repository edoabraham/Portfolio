// SignalListEX.h - SignalListEX Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __SignalListEX_h__
#define __SignalListEX_h__
#include "stdafx.h"
#include "ui_SignalList.h"

// User Interface
namespace Ui {

	// The implementation of the signal box,
	// which is used for listing and editing signals.
	class SignalListEX : public SignalList {
	public:
		// Constructor
		SignalListEX() {
			
		}

		// Initialize the form's auxiliary widgets.
		void Init(QObject* parent = NULL);
	};
}

#endif // End: SignalListEX