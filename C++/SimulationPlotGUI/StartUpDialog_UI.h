/// StartUpDialog_UI.h - Startup Prompt Dialog Class
/// Written By Jesse Z. Zhong

#ifndef __STARTUP_DIALOG_UI__
#define __STARTUP_DIALOG_UI__

#include "ui_StartUpPrompt.h"

class StartUpDialog_UI : public Ui_StartUpDialog {
    
public:
    void InitializeUI(QDialog* parent) {
        setupUi(parent);
        InitializeText();
    }
    
    // Initialize Text Values
    void InitializeText() {
        InstructionLabel->setText(QApplication::translate("StartUpDialog", "Welcome to the Simulation Data Plotter. \nPlease begin by selecting the \nsimulation directory.", 0, QApplication::UnicodeUTF8));
    }
};


#endif
