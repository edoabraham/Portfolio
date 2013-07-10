/********************************************************************************
** Form generated from reading UI file 'guitest.ui'
**
** Created: Fri Jun 28 08:27:35 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUITEST_H
#define UI_GUITEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUITestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLineEdit *LE0;
    QLineEdit *LE1;
    QLineEdit *LE2;
    QLineEdit *LE3;
    QLineEdit *LE4;
    QLineEdit *LE5;
    QLineEdit *LE6;
    QLineEdit *LE7;
    QLineEdit *LE8;
    QLineEdit *PushMehBox;
    QPushButton *PushMeh;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUITestClass)
    {
        if (GUITestClass->objectName().isEmpty())
            GUITestClass->setObjectName(QString::fromUtf8("GUITestClass"));
        GUITestClass->resize(600, 400);
        centralWidget = new QWidget(GUITestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        LE0 = new QLineEdit(centralWidget);
        LE0->setObjectName(QString::fromUtf8("LE0"));
        LE0->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, LE0);

        LE1 = new QLineEdit(centralWidget);
        LE1->setObjectName(QString::fromUtf8("LE1"));
        LE1->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, LE1);

        LE2 = new QLineEdit(centralWidget);
        LE2->setObjectName(QString::fromUtf8("LE2"));
        LE2->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::LabelRole, LE2);

        LE3 = new QLineEdit(centralWidget);
        LE3->setObjectName(QString::fromUtf8("LE3"));
        LE3->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::LabelRole, LE3);

        LE4 = new QLineEdit(centralWidget);
        LE4->setObjectName(QString::fromUtf8("LE4"));
        LE4->setReadOnly(true);

        formLayout->setWidget(4, QFormLayout::LabelRole, LE4);

        LE5 = new QLineEdit(centralWidget);
        LE5->setObjectName(QString::fromUtf8("LE5"));
        LE5->setReadOnly(true);

        formLayout->setWidget(5, QFormLayout::LabelRole, LE5);

        LE6 = new QLineEdit(centralWidget);
        LE6->setObjectName(QString::fromUtf8("LE6"));
        LE6->setReadOnly(true);

        formLayout->setWidget(6, QFormLayout::LabelRole, LE6);

        LE7 = new QLineEdit(centralWidget);
        LE7->setObjectName(QString::fromUtf8("LE7"));
        LE7->setReadOnly(true);

        formLayout->setWidget(7, QFormLayout::LabelRole, LE7);

        LE8 = new QLineEdit(centralWidget);
        LE8->setObjectName(QString::fromUtf8("LE8"));
        LE8->setReadOnly(true);

        formLayout->setWidget(8, QFormLayout::LabelRole, LE8);

        PushMehBox = new QLineEdit(centralWidget);
        PushMehBox->setObjectName(QString::fromUtf8("PushMehBox"));
        PushMehBox->setAlignment(Qt::AlignCenter);
        PushMehBox->setReadOnly(true);

        formLayout->setWidget(9, QFormLayout::LabelRole, PushMehBox);

        PushMeh = new QPushButton(centralWidget);
        PushMeh->setObjectName(QString::fromUtf8("PushMeh"));

        formLayout->setWidget(10, QFormLayout::LabelRole, PushMeh);


        verticalLayout->addLayout(formLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        GUITestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUITestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 20));
        GUITestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUITestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GUITestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUITestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUITestClass->setStatusBar(statusBar);

        retranslateUi(GUITestClass);

        QMetaObject::connectSlotsByName(GUITestClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUITestClass)
    {
        GUITestClass->setWindowTitle(QApplication::translate("GUITestClass", "GUITest", 0, QApplication::UnicodeUTF8));
        PushMehBox->setText(QString());
        PushMeh->setText(QApplication::translate("GUITestClass", "Push Meh!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GUITestClass: public Ui_GUITestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUITEST_H
