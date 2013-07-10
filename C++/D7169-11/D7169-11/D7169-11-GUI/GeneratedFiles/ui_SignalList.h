/********************************************************************************
** Form generated from reading UI file 'SignalList.ui'
**
** Created: Mon Jul 1 08:50:18 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALLIST_H
#define UI_SIGNALLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignalList
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *AddButton;
    QPushButton *RemoveButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *ConfigureButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QTableWidget *TableWidget;

    void setupUi(QDialog *SignalList)
    {
        if (SignalList->objectName().isEmpty())
            SignalList->setObjectName(QString::fromUtf8("SignalList"));
        SignalList->resize(360, 150);
        gridLayout = new QGridLayout(SignalList);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        AddButton = new QPushButton(SignalList);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));

        horizontalLayout->addWidget(AddButton);

        RemoveButton = new QPushButton(SignalList);
        RemoveButton->setObjectName(QString::fromUtf8("RemoveButton"));

        horizontalLayout->addWidget(RemoveButton);

        horizontalSpacer = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ConfigureButton = new QPushButton(SignalList);
        ConfigureButton->setObjectName(QString::fromUtf8("ConfigureButton"));

        horizontalLayout->addWidget(ConfigureButton);


        verticalLayout->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(SignalList);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 338, 97));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        TableWidget = new QTableWidget(scrollAreaWidgetContents);
        if (TableWidget->columnCount() < 2)
            TableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        TableWidget->setObjectName(QString::fromUtf8("TableWidget"));
        TableWidget->setShowGrid(false);
        TableWidget->setGridStyle(Qt::NoPen);
        TableWidget->setWordWrap(false);
        TableWidget->setCornerButtonEnabled(true);
        TableWidget->horizontalHeader()->setStretchLastSection(false);
        TableWidget->verticalHeader()->setDefaultSectionSize(20);

        gridLayout_2->addWidget(TableWidget, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SignalList);

        QMetaObject::connectSlotsByName(SignalList);
    } // setupUi

    void retranslateUi(QDialog *SignalList)
    {
        SignalList->setWindowTitle(QApplication::translate("SignalList", "Dialog", 0, QApplication::UnicodeUTF8));
        AddButton->setText(QApplication::translate("SignalList", "Add", 0, QApplication::UnicodeUTF8));
        RemoveButton->setText(QApplication::translate("SignalList", "Remove", 0, QApplication::UnicodeUTF8));
        ConfigureButton->setText(QApplication::translate("SignalList", "Configure", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SignalList", "Sample ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SignalList", "File Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SignalList: public Ui_SignalList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALLIST_H
