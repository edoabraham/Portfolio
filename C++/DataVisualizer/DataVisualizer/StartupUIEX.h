/// StartUpDialog_UI.h - Startup dialog prompt class.
/// Written By Jesse Z. Zhong
#ifndef __StartupUIEX_H__
#define __StartupUIEX_H__
#pragma region Includes
#include "stdafx.h"
#include "ProjectSettings.h"
#include "ui_StartupUI.h"
using namespace std;
using namespace Ui;
#pragma endregion
// Extension of the startup dialog prompt.
class StartupUIEX : public StartupUI {
public:
	// Initialize the UI elements.
    void InitializeUI(QDialog* parent) {
        this->setupUi(parent);
        this->InitializeText();
    }
    
    // Initialize text fields.
    void InitializeText() {
        this->InstructionLabel->setText(QApplication::translate("StartUpDialog", 
			"Welcome to the Simulation Data Plotter. \nPlease begin by selecting the \nsimulation directory.", 0));
    }
};


#endif
