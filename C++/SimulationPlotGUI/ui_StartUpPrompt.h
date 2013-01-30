/********************************************************************************
** Form generated from reading UI file 'StartUpPromptJ39444.ui'
**
** Created: Wed Jan 16 11:31:57 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STARTUPPROMPTJ39444_H
#define STARTUPPROMPTJ39444_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_StartUpDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *DirectoryLineEdit;
    QPushButton *BrowseDirectoryButton;
    QLabel *TitleLabel;
    QLabel *InstructionLabel;
    
    void setupUi(QDialog *StartUpDialog)
    {
        if (StartUpDialog->objectName().isEmpty())
            StartUpDialog->setObjectName(QString::fromUtf8("StartUpDialog"));
        StartUpDialog->resize(425, 227);
        buttonBox = new QDialogButtonBox(StartUpDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(300, 120, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        DirectoryLineEdit = new QLineEdit(StartUpDialog);
        DirectoryLineEdit->setObjectName(QString::fromUtf8("DirectoryLineEdit"));
        DirectoryLineEdit->setGeometry(QRect(30, 130, 241, 22));
        DirectoryLineEdit->setReadOnly(true);
        BrowseDirectoryButton = new QPushButton(StartUpDialog);
        BrowseDirectoryButton->setObjectName(QString::fromUtf8("BrowseDirectoryButton"));
        BrowseDirectoryButton->setGeometry(QRect(30, 160, 131, 21));
        TitleLabel = new QLabel(StartUpDialog);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        TitleLabel->setGeometry(QRect(30, 20, 211, 31));
        InstructionLabel = new QLabel(StartUpDialog);
        InstructionLabel->setObjectName(QString::fromUtf8("InstructionLabel"));
        InstructionLabel->setGeometry(QRect(30, 50, 261, 71));
        
        retranslateUi(StartUpDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartUpDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartUpDialog, SLOT(reject()));
        
        QMetaObject::connectSlotsByName(StartUpDialog);
    } // setupUi
    
    void retranslateUi(QDialog *StartUpDialog)
    {
        StartUpDialog->setWindowTitle(QApplication::translate("StartUpDialog", "SimulationPlotGUI", 0, QApplication::UnicodeUTF8));
        BrowseDirectoryButton->setText(QApplication::translate("StartUpDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        TitleLabel->setText(QApplication::translate("StartUpDialog", "Simulation Plot GUI", 0, QApplication::UnicodeUTF8));
        InstructionLabel->setText(QApplication::translate("StartUpDialog", "> Greeting and Instructions here <", 0, QApplication::UnicodeUTF8));
    } // retranslateUi


};

namespace Ui {
    class StartUpDialog: public Ui_StartUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STARTUPPROMPTJ39444_H
