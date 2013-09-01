/********************************************************************************
** Form generated from reading UI file 'StartupUI.ui'
**
** Created: Fri Aug 16 06:20:30 2013
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
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StartupUI
{
public:
    QGridLayout *gridLayout;
    QLabel *TitleLabel;
    QLabel *InstructionLabel;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *DirectoryLineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *BrowseDirectoryButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *StartupUI)
    {
        if (StartupUI->objectName().isEmpty())
            StartupUI->setObjectName(QString::fromUtf8("StartupUI"));
        StartupUI->resize(369, 181);
        gridLayout = new QGridLayout(StartupUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(20);
        gridLayout->setContentsMargins(16, -1, 16, 20);
        TitleLabel = new QLabel(StartupUI);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));

        gridLayout->addWidget(TitleLabel, 0, 0, 1, 1);

        InstructionLabel = new QLabel(StartupUI);
        InstructionLabel->setObjectName(QString::fromUtf8("InstructionLabel"));

        gridLayout->addWidget(InstructionLabel, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        DirectoryLineEdit = new QLineEdit(StartupUI);
        DirectoryLineEdit->setObjectName(QString::fromUtf8("DirectoryLineEdit"));
        DirectoryLineEdit->setReadOnly(true);

        verticalLayout->addWidget(DirectoryLineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalSpacer = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BrowseDirectoryButton = new QPushButton(StartupUI);
        BrowseDirectoryButton->setObjectName(QString::fromUtf8("BrowseDirectoryButton"));

        horizontalLayout->addWidget(BrowseDirectoryButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(StartupUI);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);


        retranslateUi(StartupUI);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartupUI, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartupUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(StartupUI);
    } // setupUi

    void retranslateUi(QDialog *StartupUI)
    {
        StartupUI->setWindowTitle(QApplication::translate("StartupUI", "Welcome", 0, QApplication::UnicodeUTF8));
        TitleLabel->setText(QApplication::translate("StartupUI", "Data Visualizer", 0, QApplication::UnicodeUTF8));
        InstructionLabel->setText(QString());
        BrowseDirectoryButton->setText(QApplication::translate("StartupUI", "Browse...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StartupUI: public Ui_StartupUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPUI_H
