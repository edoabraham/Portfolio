/********************************************************************************
** Form generated from reading UI file 'PreferenceUI.ui'
**
** Created: Tue Jul 2 02:23:33 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCEUI_H
#define UI_PREFERENCEUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PreferenceUI
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *BoldfaceLabel;
    QCheckBox *checkBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PreferenceUI)
    {
        if (PreferenceUI->objectName().isEmpty())
            PreferenceUI->setObjectName(QString::fromUtf8("PreferenceUI"));
        PreferenceUI->resize(329, 166);
        gridLayout = new QGridLayout(PreferenceUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(40);
        formLayout->setContentsMargins(20, 10, -1, -1);
        BoldfaceLabel = new QLabel(PreferenceUI);
        BoldfaceLabel->setObjectName(QString::fromUtf8("BoldfaceLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, BoldfaceLabel);

        checkBox = new QCheckBox(PreferenceUI);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, checkBox);


        verticalLayout->addLayout(formLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(PreferenceUI);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(PreferenceUI);
        QObject::connect(buttonBox, SIGNAL(accepted()), PreferenceUI, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PreferenceUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(PreferenceUI);
    } // setupUi

    void retranslateUi(QDialog *PreferenceUI)
    {
        PreferenceUI->setWindowTitle(QApplication::translate("PreferenceUI", "Dialog", 0, QApplication::UnicodeUTF8));
        BoldfaceLabel->setText(QApplication::translate("PreferenceUI", "<html><head/><body><p><span style=\" font-weight:600;\">Boldface Selected Plots</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PreferenceUI: public Ui_PreferenceUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCEUI_H