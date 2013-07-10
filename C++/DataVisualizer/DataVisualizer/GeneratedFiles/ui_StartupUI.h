/********************************************************************************
** Form generated from reading UI file 'StartupUI.ui'
**
** Created: Tue Jul 2 19:31:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUPUI_H
#define UI_STARTUPUI_H

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

class Ui_StartupUI
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *DirectoryLineEdit;
    QPushButton *BrowseDirectoryButton;
    QLabel *TitleLabel;
    QLabel *InstructionLabel;

    void setupUi(QDialog *StartupUI)
    {
        if (StartupUI->objectName().isEmpty())
            StartupUI->setObjectName(QString::fromUtf8("StartupUI"));
        StartupUI->resize(425, 227);
        buttonBox = new QDialogButtonBox(StartupUI);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(300, 120, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        DirectoryLineEdit = new QLineEdit(StartupUI);
        DirectoryLineEdit->setObjectName(QString::fromUtf8("DirectoryLineEdit"));
        DirectoryLineEdit->setGeometry(QRect(30, 130, 241, 22));
        DirectoryLineEdit->setReadOnly(true);
        BrowseDirectoryButton = new QPushButton(StartupUI);
        BrowseDirectoryButton->setObjectName(QString::fromUtf8("BrowseDirectoryButton"));
        BrowseDirectoryButton->setGeometry(QRect(30, 160, 131, 21));
        TitleLabel = new QLabel(StartupUI);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        TitleLabel->setGeometry(QRect(30, 20, 211, 31));
        InstructionLabel = new QLabel(StartupUI);
        InstructionLabel->setObjectName(QString::fromUtf8("InstructionLabel"));
        InstructionLabel->setGeometry(QRect(30, 50, 261, 71));

        retranslateUi(StartupUI);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartupUI, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartupUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(StartupUI);
    } // setupUi

    void retranslateUi(QDialog *StartupUI)
    {
        StartupUI->setWindowTitle(QApplication::translate("StartupUI", "Welcome", 0, QApplication::UnicodeUTF8));
        BrowseDirectoryButton->setText(QApplication::translate("StartupUI", "Browse...", 0, QApplication::UnicodeUTF8));
        TitleLabel->setText(QApplication::translate("StartupUI", "Data Visualizer", 0, QApplication::UnicodeUTF8));
        InstructionLabel->setText(QApplication::translate("StartupUI", "> Greeting and Instructions here <", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StartupUI: public Ui_StartupUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPUI_H
