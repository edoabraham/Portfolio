/// LoadProgressForm_UI.h - LoadProgressForm Class
/// Written By Jesse Z. Zhong

#ifndef __Load_PROGRESS_FORM_UI__
#define __Load_PROGRESS_FORM_UI__

#include "ui_StartUpPrompt.h"

class LoadProgressForm_UI : public Ui_LoadingForm {
    
public:
    void InitializeUI(QWidget* parent) {
        setupUi(parent);
        InitializeText();
    }
    
    // Initialize Text Values
    void InitializeText() {
        FileNameLabel->setText(QApplication::translate("FileNameLabel", "", 0, QApplication::UnicodeUTF8));
        LoadProgressBar->setValue(0);
    }
};


#endif
