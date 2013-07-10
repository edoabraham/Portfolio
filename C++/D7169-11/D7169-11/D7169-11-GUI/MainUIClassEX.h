// MainUIClassEX.h - MainUIClassEX Class Declaration.
// Written by Jesse Z. Zhong
#ifndef __MainUIClassEX_h__
#define __MainUIClassEX_h__

#include "stdafx.h"
#include "ui_mainui.h"
#include "DataASCII.h"
#include "SignalPlot.h"

// User Interface
namespace Ui {

	// Extension of the main UI class.
	class MainUIClassEX : public MainUIClass {
	public:
		// Constructor
		MainUIClassEX() {
			
		}

		// Initialize widgets and their settings.
		void Init(QObject* parent = NULL);

		// Main graphing window for plotting signals.
		SignalPlot* SignalGraph;

		// Signals button for starting the signals dialog.
		QAction* SignalsAction;

		// Preferences button for starting the preference dialog.
		QAction* PreferencesAction;
	};
}

#endif // End: MainUIClassEX