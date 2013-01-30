/********************************************************************************
** Form generated from reading UI file 'simulationplotgui.ui'
**
** Created: Tue Oct 30 21:36:41 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONPLOTGUI_H
#define UI_SIMULATIONPLOTGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationPlotGUIClass
{
public:
    QWidget *centralWidget;
    QSlider *SeekSlider;
    QPushButton *StartButton;
    QLabel *CurrentSnapshotLabel;
    QFrame *CurrentSnapshotLine;
    QLineEdit *CurrentSnapshotLineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulationPlotGUIClass)
    {
        if (SimulationPlotGUIClass->objectName().isEmpty())
            SimulationPlotGUIClass->setObjectName(QString::fromUtf8("SimulationPlotGUIClass"));
        SimulationPlotGUIClass->resize(1243, 907);
        SimulationPlotGUIClass->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(SimulationPlotGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SeekSlider = new QSlider(centralWidget);
        SeekSlider->setObjectName(QString::fromUtf8("SeekSlider"));
        SeekSlider->setGeometry(QRect(20, 830, 561, 31));
        SeekSlider->setOrientation(Qt::Horizontal);
        StartButton = new QPushButton(centralWidget);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        StartButton->setGeometry(QRect(680, 790, 231, 51));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        StartButton->setFont(font);
        CurrentSnapshotLabel = new QLabel(centralWidget);
        CurrentSnapshotLabel->setObjectName(QString::fromUtf8("CurrentSnapshotLabel"));
        CurrentSnapshotLabel->setGeometry(QRect(20, 780, 261, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        CurrentSnapshotLabel->setFont(font1);
        CurrentSnapshotLine = new QFrame(centralWidget);
        CurrentSnapshotLine->setObjectName(QString::fromUtf8("CurrentSnapshotLine"));
        CurrentSnapshotLine->setGeometry(QRect(20, 810, 231, 16));
        CurrentSnapshotLine->setFrameShape(QFrame::HLine);
        CurrentSnapshotLine->setFrameShadow(QFrame::Sunken);
        CurrentSnapshotLineEdit = new QLineEdit(centralWidget);
        CurrentSnapshotLineEdit->setObjectName(QString::fromUtf8("CurrentSnapshotLineEdit"));
        CurrentSnapshotLineEdit->setGeometry(QRect(260, 790, 151, 31));
        QFont font2;
        font2.setPointSize(12);
        CurrentSnapshotLineEdit->setFont(font2);
        CurrentSnapshotLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SimulationPlotGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimulationPlotGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1243, 20));
        SimulationPlotGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulationPlotGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimulationPlotGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SimulationPlotGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimulationPlotGUIClass->setStatusBar(statusBar);

        retranslateUi(SimulationPlotGUIClass);

        QMetaObject::connectSlotsByName(SimulationPlotGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationPlotGUIClass)
    {
        SimulationPlotGUIClass->setWindowTitle(QApplication::translate("SimulationPlotGUIClass", "SimulationPlotGUI", 0, QApplication::UnicodeUTF8));
        StartButton->setText(QApplication::translate("SimulationPlotGUIClass", "Start", 0, QApplication::UnicodeUTF8));
        CurrentSnapshotLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Current Snapshot Number : ", 0, QApplication::UnicodeUTF8));
        CurrentSnapshotLineEdit->setText(QApplication::translate("SimulationPlotGUIClass", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimulationPlotGUIClass: public Ui_SimulationPlotGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONPLOTGUI_H
