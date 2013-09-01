/// StartUpDialog_UI.h - Startup dialog prompt class.
/// Written By Jesse Z. Zhong
#ifndef __Startup_UI_EX_H__
#define __Startup_UI_EX_H__
#pragma region Includes
#include "stdafx.h"
#include "ui_StartupUI.h"
using namespace std;
using namespace Ui;
#pragma endregion
// Extension of the startup dialog prompt.
class StartupUIEX : public StartupUI {
public:
	// Initialize the UI elements.
    void InitializeUI(QDialog* parent) {
        this->InitializeText();
    }
    
    // Initialize text fields.
    void InitializeText() {
        this->InstructionLabel->setText(QApplication::translate("StartUpDialog", 
			"Welcome to the Simulation Data Plotter. \nPlease begin by selecting the simulation directory.", 0));
    }
};


#endif
