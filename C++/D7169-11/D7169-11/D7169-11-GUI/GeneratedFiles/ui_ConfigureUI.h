/********************************************************************************
** Form generated from reading UI file 'ConfigureUI.ui'
**
** Created: Sun Jun 30 18:51:45 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREUI_H
#define UI_CONFIGUREUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigureUI
{
public:
    QGridLayout *ConfigGridLayout;
    QSplitter *MainSplitter;
    QWidget *layoutWidget;
    QFormLayout *FormLayout;
    QLabel *SampleLabel;
    QComboBox *SampleCBox;
    QLabel *OffsetsLabel;
    QSpacerItem *verticalSpacer;
    QLabel *XAxisLabel;
    QLineEdit *XAxisBox;
    QLabel *YAxisLabel;
    QLineEdit *YAxisBox;
    QLabel *CurveColorLabel;
    QHBoxLayout *horizontalLayout;
    QLineEdit *ColorDisplay;
    QToolButton *ColorButton;
    QWidget *layoutWidget1;
    QHBoxLayout *ButtonLayout;
    QSpacerItem *ButtonSpacer;
    QPushButton *OkayButton;
    QPushButton *CancelButton;
    QLabel *ConfigLabel;

    void setupUi(QDialog *ConfigureUI)
    {
        if (ConfigureUI->objectName().isEmpty())
            ConfigureUI->setObjectName(QString::fromUtf8("ConfigureUI"));
        ConfigureUI->resize(320, 400);
        ConfigGridLayout = new QGridLayout(ConfigureUI);
        ConfigGridLayout->setObjectName(QString::fromUtf8("ConfigGridLayout"));
        MainSplitter = new QSplitter(ConfigureUI);
        MainSplitter->setObjectName(QString::fromUtf8("MainSplitter"));
        MainSplitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(MainSplitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        FormLayout = new QFormLayout(layoutWidget);
        FormLayout->setObjectName(QString::fromUtf8("FormLayout"));
        FormLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        FormLayout->setHorizontalSpacing(60);
        FormLayout->setVerticalSpacing(20);
        FormLayout->setContentsMargins(20, 0, 20, 0);
        SampleLabel = new QLabel(layoutWidget);
        SampleLabel->setObjectName(QString::fromUtf8("SampleLabel"));

        FormLayout->setWidget(0, QFormLayout::LabelRole, SampleLabel);

        SampleCBox = new QComboBox(layoutWidget);
        SampleCBox->setObjectName(QString::fromUtf8("SampleCBox"));

        FormLayout->setWidget(0, QFormLayout::FieldRole, SampleCBox);

        OffsetsLabel = new QLabel(layoutWidget);
        OffsetsLabel->setObjectName(QString::fromUtf8("OffsetsLabel"));

        FormLayout->setWidget(1, QFormLayout::LabelRole, OffsetsLabel);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        FormLayout->setItem(1, QFormLayout::FieldRole, verticalSpacer);

        XAxisLabel = new QLabel(layoutWidget);
        XAxisLabel->setObjectName(QString::fromUtf8("XAxisLabel"));

        FormLayout->setWidget(2, QFormLayout::LabelRole, XAxisLabel);

        XAxisBox = new QLineEdit(layoutWidget);
        XAxisBox->setObjectName(QString::fromUtf8("XAxisBox"));
        XAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        FormLayout->setWidget(2, QFormLayout::FieldRole, XAxisBox);

        YAxisLabel = new QLabel(layoutWidget);
        YAxisLabel->setObjectName(QString::fromUtf8("YAxisLabel"));

        FormLayout->setWidget(3, QFormLayout::LabelRole, YAxisLabel);

        YAxisBox = new QLineEdit(layoutWidget);
        YAxisBox->setObjectName(QString::fromUtf8("YAxisBox"));
        YAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        FormLayout->setWidget(3, QFormLayout::FieldRole, YAxisBox);

        CurveColorLabel = new QLabel(layoutWidget);
        CurveColorLabel->setObjectName(QString::fromUtf8("CurveColorLabel"));

        FormLayout->setWidget(4, QFormLayout::LabelRole, CurveColorLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ColorDisplay = new QLineEdit(layoutWidget);
        ColorDisplay->setObjectName(QString::fromUtf8("ColorDisplay"));
        ColorDisplay->setReadOnly(true);

        horizontalLayout->addWidget(ColorDisplay);

        ColorButton = new QToolButton(layoutWidget);
        ColorButton->setObjectName(QString::fromUtf8("ColorButton"));

        horizontalLayout->addWidget(ColorButton);


        FormLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout);

        MainSplitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(MainSplitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        ButtonLayout = new QHBoxLayout(layoutWidget1);
        ButtonLayout->setSpacing(6);
        ButtonLayout->setObjectName(QString::fromUtf8("ButtonLayout"));
        ButtonLayout->setContentsMargins(0, 0, 20, 0);
        ButtonSpacer = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        ButtonLayout->addItem(ButtonSpacer);

        OkayButton = new QPushButton(layoutWidget1);
        OkayButton->setObjectName(QString::fromUtf8("OkayButton"));

        ButtonLayout->addWidget(OkayButton);

        CancelButton = new QPushButton(layoutWidget1);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        ButtonLayout->addWidget(CancelButton);

        MainSplitter->addWidget(layoutWidget1);

        ConfigGridLayout->addWidget(MainSplitter, 1, 0, 1, 1);

        ConfigLabel = new QLabel(ConfigureUI);
        ConfigLabel->setObjectName(QString::fromUtf8("ConfigLabel"));

        ConfigGridLayout->addWidget(ConfigLabel, 0, 0, 1, 1);


        retranslateUi(ConfigureUI);
        QObject::connect(OkayButton, SIGNAL(clicked()), ConfigureUI, SLOT(accept()));
        QObject::connect(CancelButton, SIGNAL(clicked()), ConfigureUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigureUI);
    } // setupUi

    void retranslateUi(QDialog *ConfigureUI)
    {
        ConfigureUI->setWindowTitle(QApplication::translate("ConfigureUI", "Dialog", 0, QApplication::UnicodeUTF8));
        SampleLabel->setText(QApplication::translate("ConfigureUI", "Sample", 0, QApplication::UnicodeUTF8));
        OffsetsLabel->setText(QApplication::translate("ConfigureUI", "<html><head/><body><p><span style=\" font-size:10pt;\">Offsets</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        XAxisLabel->setText(QApplication::translate("ConfigureUI", "X Axis", 0, QApplication::UnicodeUTF8));
        YAxisLabel->setText(QApplication::translate("ConfigureUI", "Y Axis", 0, QApplication::UnicodeUTF8));
        CurveColorLabel->setText(QApplication::translate("ConfigureUI", "Curve Color", 0, QApplication::UnicodeUTF8));
        ColorButton->setText(QApplication::translate("ConfigureUI", "...", 0, QApplication::UnicodeUTF8));
        OkayButton->setText(QApplication::translate("ConfigureUI", "OK", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("ConfigureUI", "Cancel", 0, QApplication::UnicodeUTF8));
        ConfigLabel->setText(QApplication::translate("ConfigureUI", "<html><head/><body><p><span style=\" font-size:12pt;\">Configurations</span></p><p></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigureUI: public Ui_ConfigureUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREUI_H
