/********************************************************************************
** Form generated from reading UI file 'simulationgui.ui'
**
** Created: Fri Jan 18 02:10:48 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONGUI_H
#define UI_SIMULATIONGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationGUIClass
{
public:
    QAction *actionSave_Parameters_As;
    QAction *actionAbout;
    QWidget *centralWidget;
    QToolButton *LoadRecentParametersButton;
    QToolButton *LoadParametersFromFileButton;
    QToolButton *StartButton;
    QToolButton *SaveCurrentParametersButton;
    QLabel *ActionLogLabel;
    QTextBrowser *ActionLogBox;
    QLabel *EnvironmentalVariablesLabel;
    QFrame *EnvironmentalVariablesLine;
    QLabel *SimulationParameters;
    QFrame *AtomicPartsLine;
    QLabel *AtomicPartsLabel;
    QTextBrowser *SimulationDirectoryBox;
    QLabel *SimulationDirectoryLabel;
    QToolButton *ChangeDirectoryToButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *ConeAngleLabel;
    QLabel *TemperatureLabel;
    QLabel *WallTemperatureLabel;
    QLabel *EquilibriumRadiusLabel;
    QLabel *DriverPressureLabel;
    QLabel *FrequencyLabel;
    QLabel *InitialTimeLabel;
    QLabel *InitialRadiusLabel;
    QLabel *InitialVelocityLabel;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *ConeAngleLineText;
    QLineEdit *TemperatureLineText;
    QLineEdit *WallTemperatureLineText;
    QLineEdit *EquilibriumRadiusLineText;
    QLineEdit *DriverPressureLineText;
    QLineEdit *FrequencyLineText;
    QLineEdit *InitialTimeLineText;
    QLineEdit *InitialRadiusLineText;
    QLineEdit *InitialVelocityLineText;
    QVBoxLayout *verticalLayout;
    QLabel *ConeAngleUnitsLabel;
    QLabel *TemperatureUnitsLabel;
    QLabel *WallTemperatureUnitsLabel;
    QLabel *EquilibriumRadiusUnitsLabel;
    QLabel *DriverPressureUnitsLabel;
    QLabel *FrequencyUnitsLabel;
    QLabel *InitialTimeUnitsLabel;
    QLabel *InitialRadiusUnitsLabel;
    QLabel *InitialVelocityUnitsLabel;
    QComboBox *GasComboBox2;
    QComboBox *GasComboBox1;
    QTextBrowser *GUITimerBox;
    QLabel *TimerLabel;
    QLineEdit *Gas1LineText;
    QLineEdit *Gas2LineText;
    QLabel *Gas1Label;
    QLabel *Gas2Label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulationGUIClass)
    {
        if (SimulationGUIClass->objectName().isEmpty())
            SimulationGUIClass->setObjectName(QString::fromUtf8("SimulationGUIClass"));
        SimulationGUIClass->resize(1071, 680);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(238, 238, 238, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        SimulationGUIClass->setPalette(palette);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        SimulationGUIClass->setFont(font);
        SimulationGUIClass->setContextMenuPolicy(Qt::ActionsContextMenu);
        actionSave_Parameters_As = new QAction(SimulationGUIClass);
        actionSave_Parameters_As->setObjectName(QString::fromUtf8("actionSave_Parameters_As"));
        actionAbout = new QAction(SimulationGUIClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(SimulationGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        LoadRecentParametersButton = new QToolButton(centralWidget);
        LoadRecentParametersButton->setObjectName(QString::fromUtf8("LoadRecentParametersButton"));
        LoadRecentParametersButton->setGeometry(QRect(800, 470, 191, 41));
        LoadRecentParametersButton->setFont(font);
        LoadRecentParametersButton->setCursor(QCursor(Qt::PointingHandCursor));
        LoadParametersFromFileButton = new QToolButton(centralWidget);
        LoadParametersFromFileButton->setObjectName(QString::fromUtf8("LoadParametersFromFileButton"));
        LoadParametersFromFileButton->setGeometry(QRect(800, 510, 191, 41));
        LoadParametersFromFileButton->setFont(font);
        LoadParametersFromFileButton->setCursor(QCursor(Qt::PointingHandCursor));
        StartButton = new QToolButton(centralWidget);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        StartButton->setGeometry(QRect(420, 520, 211, 81));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setWeight(50);
        StartButton->setFont(font1);
        StartButton->setCursor(QCursor(Qt::PointingHandCursor));
        SaveCurrentParametersButton = new QToolButton(centralWidget);
        SaveCurrentParametersButton->setObjectName(QString::fromUtf8("SaveCurrentParametersButton"));
        SaveCurrentParametersButton->setGeometry(QRect(800, 550, 191, 41));
        SaveCurrentParametersButton->setFont(font);
        SaveCurrentParametersButton->setCursor(QCursor(Qt::PointingHandCursor));
        ActionLogLabel = new QLabel(centralWidget);
        ActionLogLabel->setObjectName(QString::fromUtf8("ActionLogLabel"));
        ActionLogLabel->setGeometry(QRect(750, 70, 81, 31));
        ActionLogBox = new QTextBrowser(centralWidget);
        ActionLogBox->setObjectName(QString::fromUtf8("ActionLogBox"));
        ActionLogBox->setGeometry(QRect(750, 110, 281, 201));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        ActionLogBox->setFont(font2);
        ActionLogBox->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        EnvironmentalVariablesLabel = new QLabel(centralWidget);
        EnvironmentalVariablesLabel->setObjectName(QString::fromUtf8("EnvironmentalVariablesLabel"));
        EnvironmentalVariablesLabel->setGeometry(QRect(70, 70, 171, 31));
        EnvironmentalVariablesLine = new QFrame(centralWidget);
        EnvironmentalVariablesLine->setObjectName(QString::fromUtf8("EnvironmentalVariablesLine"));
        EnvironmentalVariablesLine->setGeometry(QRect(70, 90, 161, 16));
        EnvironmentalVariablesLine->setFrameShape(QFrame::HLine);
        EnvironmentalVariablesLine->setFrameShadow(QFrame::Sunken);
        SimulationParameters = new QLabel(centralWidget);
        SimulationParameters->setObjectName(QString::fromUtf8("SimulationParameters"));
        SimulationParameters->setGeometry(QRect(230, 20, 271, 41));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(false);
        font3.setWeight(50);
        SimulationParameters->setFont(font3);
        AtomicPartsLine = new QFrame(centralWidget);
        AtomicPartsLine->setObjectName(QString::fromUtf8("AtomicPartsLine"));
        AtomicPartsLine->setGeometry(QRect(460, 90, 91, 16));
        AtomicPartsLine->setFrameShape(QFrame::HLine);
        AtomicPartsLine->setFrameShadow(QFrame::Sunken);
        AtomicPartsLabel = new QLabel(centralWidget);
        AtomicPartsLabel->setObjectName(QString::fromUtf8("AtomicPartsLabel"));
        AtomicPartsLabel->setGeometry(QRect(460, 70, 91, 31));
        SimulationDirectoryBox = new QTextBrowser(centralWidget);
        SimulationDirectoryBox->setObjectName(QString::fromUtf8("SimulationDirectoryBox"));
        SimulationDirectoryBox->setGeometry(QRect(750, 380, 281, 31));
        SimulationDirectoryBox->setFont(font2);
        SimulationDirectoryBox->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        SimulationDirectoryLabel = new QLabel(centralWidget);
        SimulationDirectoryLabel->setObjectName(QString::fromUtf8("SimulationDirectoryLabel"));
        SimulationDirectoryLabel->setGeometry(QRect(750, 340, 141, 31));
        ChangeDirectoryToButton = new QToolButton(centralWidget);
        ChangeDirectoryToButton->setObjectName(QString::fromUtf8("ChangeDirectoryToButton"));
        ChangeDirectoryToButton->setGeometry(QRect(750, 420, 171, 31));
        ChangeDirectoryToButton->setCursor(QCursor(Qt::PointingHandCursor));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 130, 411, 361));
        layoutWidget->setFont(font);
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        ConeAngleLabel = new QLabel(layoutWidget);
        ConeAngleLabel->setObjectName(QString::fromUtf8("ConeAngleLabel"));
        ConeAngleLabel->setFont(font);

        verticalLayout_3->addWidget(ConeAngleLabel);

        TemperatureLabel = new QLabel(layoutWidget);
        TemperatureLabel->setObjectName(QString::fromUtf8("TemperatureLabel"));
        TemperatureLabel->setFont(font);

        verticalLayout_3->addWidget(TemperatureLabel);

        WallTemperatureLabel = new QLabel(layoutWidget);
        WallTemperatureLabel->setObjectName(QString::fromUtf8("WallTemperatureLabel"));
        WallTemperatureLabel->setFont(font);

        verticalLayout_3->addWidget(WallTemperatureLabel);

        EquilibriumRadiusLabel = new QLabel(layoutWidget);
        EquilibriumRadiusLabel->setObjectName(QString::fromUtf8("EquilibriumRadiusLabel"));
        EquilibriumRadiusLabel->setFont(font);

        verticalLayout_3->addWidget(EquilibriumRadiusLabel);

        DriverPressureLabel = new QLabel(layoutWidget);
        DriverPressureLabel->setObjectName(QString::fromUtf8("DriverPressureLabel"));
        DriverPressureLabel->setFont(font);

        verticalLayout_3->addWidget(DriverPressureLabel);

        FrequencyLabel = new QLabel(layoutWidget);
        FrequencyLabel->setObjectName(QString::fromUtf8("FrequencyLabel"));
        FrequencyLabel->setFont(font);

        verticalLayout_3->addWidget(FrequencyLabel);

        InitialTimeLabel = new QLabel(layoutWidget);
        InitialTimeLabel->setObjectName(QString::fromUtf8("InitialTimeLabel"));
        InitialTimeLabel->setFont(font);

        verticalLayout_3->addWidget(InitialTimeLabel);

        InitialRadiusLabel = new QLabel(layoutWidget);
        InitialRadiusLabel->setObjectName(QString::fromUtf8("InitialRadiusLabel"));
        InitialRadiusLabel->setFont(font);

        verticalLayout_3->addWidget(InitialRadiusLabel);

        InitialVelocityLabel = new QLabel(layoutWidget);
        InitialVelocityLabel->setObjectName(QString::fromUtf8("InitialVelocityLabel"));
        InitialVelocityLabel->setFont(font);

        verticalLayout_3->addWidget(InitialVelocityLabel);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ConeAngleLineText = new QLineEdit(layoutWidget);
        ConeAngleLineText->setObjectName(QString::fromUtf8("ConeAngleLineText"));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setWeight(50);
        ConeAngleLineText->setFont(font4);
        ConeAngleLineText->setLayoutDirection(Qt::LeftToRight);
        ConeAngleLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(ConeAngleLineText);

        TemperatureLineText = new QLineEdit(layoutWidget);
        TemperatureLineText->setObjectName(QString::fromUtf8("TemperatureLineText"));
        QFont font5;
        font5.setBold(false);
        font5.setWeight(50);
        TemperatureLineText->setFont(font5);
        TemperatureLineText->setLayoutDirection(Qt::LeftToRight);
        TemperatureLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(TemperatureLineText);

        WallTemperatureLineText = new QLineEdit(layoutWidget);
        WallTemperatureLineText->setObjectName(QString::fromUtf8("WallTemperatureLineText"));
        WallTemperatureLineText->setFont(font5);
        WallTemperatureLineText->setLayoutDirection(Qt::LeftToRight);
        WallTemperatureLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(WallTemperatureLineText);

        EquilibriumRadiusLineText = new QLineEdit(layoutWidget);
        EquilibriumRadiusLineText->setObjectName(QString::fromUtf8("EquilibriumRadiusLineText"));
        EquilibriumRadiusLineText->setFont(font5);
        EquilibriumRadiusLineText->setLayoutDirection(Qt::LeftToRight);
        EquilibriumRadiusLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(EquilibriumRadiusLineText);

        DriverPressureLineText = new QLineEdit(layoutWidget);
        DriverPressureLineText->setObjectName(QString::fromUtf8("DriverPressureLineText"));
        DriverPressureLineText->setFont(font5);
        DriverPressureLineText->setLayoutDirection(Qt::LeftToRight);
        DriverPressureLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(DriverPressureLineText);

        FrequencyLineText = new QLineEdit(layoutWidget);
        FrequencyLineText->setObjectName(QString::fromUtf8("FrequencyLineText"));
        FrequencyLineText->setFont(font5);
        FrequencyLineText->setLayoutDirection(Qt::LeftToRight);
        FrequencyLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(FrequencyLineText);

        InitialTimeLineText = new QLineEdit(layoutWidget);
        InitialTimeLineText->setObjectName(QString::fromUtf8("InitialTimeLineText"));
        InitialTimeLineText->setFont(font5);
        InitialTimeLineText->setLayoutDirection(Qt::LeftToRight);
        InitialTimeLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(InitialTimeLineText);

        InitialRadiusLineText = new QLineEdit(layoutWidget);
        InitialRadiusLineText->setObjectName(QString::fromUtf8("InitialRadiusLineText"));
        InitialRadiusLineText->setFont(font5);
        InitialRadiusLineText->setLayoutDirection(Qt::LeftToRight);
        InitialRadiusLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(InitialRadiusLineText);

        InitialVelocityLineText = new QLineEdit(layoutWidget);
        InitialVelocityLineText->setObjectName(QString::fromUtf8("InitialVelocityLineText"));
        InitialVelocityLineText->setFont(font5);
        InitialVelocityLineText->setLayoutDirection(Qt::LeftToRight);
        InitialVelocityLineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(InitialVelocityLineText);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ConeAngleUnitsLabel = new QLabel(layoutWidget);
        ConeAngleUnitsLabel->setObjectName(QString::fromUtf8("ConeAngleUnitsLabel"));

        verticalLayout->addWidget(ConeAngleUnitsLabel);

        TemperatureUnitsLabel = new QLabel(layoutWidget);
        TemperatureUnitsLabel->setObjectName(QString::fromUtf8("TemperatureUnitsLabel"));

        verticalLayout->addWidget(TemperatureUnitsLabel);

        WallTemperatureUnitsLabel = new QLabel(layoutWidget);
        WallTemperatureUnitsLabel->setObjectName(QString::fromUtf8("WallTemperatureUnitsLabel"));

        verticalLayout->addWidget(WallTemperatureUnitsLabel);

        EquilibriumRadiusUnitsLabel = new QLabel(layoutWidget);
        EquilibriumRadiusUnitsLabel->setObjectName(QString::fromUtf8("EquilibriumRadiusUnitsLabel"));

        verticalLayout->addWidget(EquilibriumRadiusUnitsLabel);

        DriverPressureUnitsLabel = new QLabel(layoutWidget);
        DriverPressureUnitsLabel->setObjectName(QString::fromUtf8("DriverPressureUnitsLabel"));

        verticalLayout->addWidget(DriverPressureUnitsLabel);

        FrequencyUnitsLabel = new QLabel(layoutWidget);
        FrequencyUnitsLabel->setObjectName(QString::fromUtf8("FrequencyUnitsLabel"));

        verticalLayout->addWidget(FrequencyUnitsLabel);

        InitialTimeUnitsLabel = new QLabel(layoutWidget);
        InitialTimeUnitsLabel->setObjectName(QString::fromUtf8("InitialTimeUnitsLabel"));

        verticalLayout->addWidget(InitialTimeUnitsLabel);

        InitialRadiusUnitsLabel = new QLabel(layoutWidget);
        InitialRadiusUnitsLabel->setObjectName(QString::fromUtf8("InitialRadiusUnitsLabel"));

        verticalLayout->addWidget(InitialRadiusUnitsLabel);

        InitialVelocityUnitsLabel = new QLabel(layoutWidget);
        InitialVelocityUnitsLabel->setObjectName(QString::fromUtf8("InitialVelocityUnitsLabel"));

        verticalLayout->addWidget(InitialVelocityUnitsLabel);


        horizontalLayout->addLayout(verticalLayout);

        GasComboBox2 = new QComboBox(centralWidget);
        GasComboBox2->setObjectName(QString::fromUtf8("GasComboBox2"));
        GasComboBox2->setGeometry(QRect(460, 220, 111, 21));
        GasComboBox1 = new QComboBox(centralWidget);
        GasComboBox1->setObjectName(QString::fromUtf8("GasComboBox1"));
        GasComboBox1->setGeometry(QRect(460, 150, 111, 21));
        GUITimerBox = new QTextBrowser(centralWidget);
        GUITimerBox->setObjectName(QString::fromUtf8("GUITimerBox"));
        GUITimerBox->setGeometry(QRect(150, 560, 161, 31));
        TimerLabel = new QLabel(centralWidget);
        TimerLabel->setObjectName(QString::fromUtf8("TimerLabel"));
        TimerLabel->setGeometry(QRect(150, 530, 181, 21));
        QFont font6;
        font6.setPointSize(11);
        TimerLabel->setFont(font6);
        Gas1LineText = new QLineEdit(centralWidget);
        Gas1LineText->setObjectName(QString::fromUtf8("Gas1LineText"));
        Gas1LineText->setGeometry(QRect(580, 150, 135, 22));
        Gas1LineText->setFont(font4);
        Gas1LineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Gas2LineText = new QLineEdit(centralWidget);
        Gas2LineText->setObjectName(QString::fromUtf8("Gas2LineText"));
        Gas2LineText->setGeometry(QRect(580, 218, 135, 22));
        Gas2LineText->setFont(font4);
        Gas2LineText->setInputMethodHints(Qt::ImhNone);
        Gas2LineText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Gas2LineText->setReadOnly(true);
        Gas1Label = new QLabel(centralWidget);
        Gas1Label->setObjectName(QString::fromUtf8("Gas1Label"));
        Gas1Label->setGeometry(QRect(460, 130, 75, 16));
        Gas2Label = new QLabel(centralWidget);
        Gas2Label->setObjectName(QString::fromUtf8("Gas2Label"));
        Gas2Label->setGeometry(QRect(460, 200, 64, 16));
        SimulationGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimulationGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1071, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        SimulationGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulationGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimulationGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SimulationGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimulationGUIClass->setStatusBar(statusBar);
        QWidget::setTabOrder(ConeAngleLineText, TemperatureLineText);
        QWidget::setTabOrder(TemperatureLineText, WallTemperatureLineText);
        QWidget::setTabOrder(WallTemperatureLineText, EquilibriumRadiusLineText);
        QWidget::setTabOrder(EquilibriumRadiusLineText, DriverPressureLineText);
        QWidget::setTabOrder(DriverPressureLineText, FrequencyLineText);
        QWidget::setTabOrder(FrequencyLineText, InitialTimeLineText);
        QWidget::setTabOrder(InitialTimeLineText, InitialRadiusLineText);
        QWidget::setTabOrder(InitialRadiusLineText, InitialVelocityLineText);
        QWidget::setTabOrder(InitialVelocityLineText, GasComboBox1);
        QWidget::setTabOrder(GasComboBox1, Gas1LineText);
        QWidget::setTabOrder(Gas1LineText, GasComboBox2);
        QWidget::setTabOrder(GasComboBox2, Gas2LineText);
        QWidget::setTabOrder(Gas2LineText, StartButton);
        QWidget::setTabOrder(StartButton, ActionLogBox);
        QWidget::setTabOrder(ActionLogBox, SimulationDirectoryBox);
        QWidget::setTabOrder(SimulationDirectoryBox, ChangeDirectoryToButton);
        QWidget::setTabOrder(ChangeDirectoryToButton, LoadRecentParametersButton);
        QWidget::setTabOrder(LoadRecentParametersButton, LoadParametersFromFileButton);
        QWidget::setTabOrder(LoadParametersFromFileButton, SaveCurrentParametersButton);
        QWidget::setTabOrder(SaveCurrentParametersButton, GUITimerBox);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSave_Parameters_As);
        menuHelp->addAction(actionAbout);

        retranslateUi(SimulationGUIClass);

        QMetaObject::connectSlotsByName(SimulationGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationGUIClass)
    {
        SimulationGUIClass->setWindowTitle(QApplication::translate("SimulationGUIClass", "SimulationGUI", 0, QApplication::UnicodeUTF8));
        actionSave_Parameters_As->setText(QApplication::translate("SimulationGUIClass", "Save Parameters As...", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("SimulationGUIClass", "About..", 0, QApplication::UnicodeUTF8));
        LoadRecentParametersButton->setText(QApplication::translate("SimulationGUIClass", "Load Recent Parameters", 0, QApplication::UnicodeUTF8));
        LoadParametersFromFileButton->setText(QApplication::translate("SimulationGUIClass", "Load Parameters from File", 0, QApplication::UnicodeUTF8));
        StartButton->setText(QApplication::translate("SimulationGUIClass", "Start", 0, QApplication::UnicodeUTF8));
        SaveCurrentParametersButton->setText(QApplication::translate("SimulationGUIClass", "Save Current Parameters", 0, QApplication::UnicodeUTF8));
        ActionLogLabel->setText(QApplication::translate("SimulationGUIClass", "Action Log:", 0, QApplication::UnicodeUTF8));
        EnvironmentalVariablesLabel->setText(QApplication::translate("SimulationGUIClass", "Environmental Variables", 0, QApplication::UnicodeUTF8));
        SimulationParameters->setText(QApplication::translate("SimulationGUIClass", "Simulation Parameters", 0, QApplication::UnicodeUTF8));
        AtomicPartsLabel->setText(QApplication::translate("SimulationGUIClass", "Atomic Parts", 0, QApplication::UnicodeUTF8));
        SimulationDirectoryLabel->setText(QApplication::translate("SimulationGUIClass", "Simulation Directory:", 0, QApplication::UnicodeUTF8));
        ChangeDirectoryToButton->setText(QApplication::translate("SimulationGUIClass", "Change Directory to ..", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ConeAngleLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Cone Angle</span><span style=\" font-size:12pt; font-weight:400;\"> is the </span><span style=\" font-size:12pt;\">angularwidth </span><span style=\" font-size:12pt; font-weight:400;\">of the </span><span style=\" font-size:12pt;\">conical section</span><span style=\" font-size:12pt; font-weight:400;\"> of the </span><span style=\" font-size:12pt;\">bubble</span><span style=\" font-size:12pt; font-weight:400;\"> that is to be simulated.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ConeAngleLabel->setText(QApplication::translate("SimulationGUIClass", "Cone Angle", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        TemperatureLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Temperature</span><span style=\" font-size:12pt; font-weight:400;\"> of the bubble's surrounding </span><span style=\" font-size:12pt;\">environment</span><span style=\" font-size:12pt; font-weight:400;\">.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        TemperatureLabel->setText(QApplication::translate("SimulationGUIClass", "Temperature", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        WallTemperatureLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Wall Temperature</span><span style=\" font-size:12pt; font-weight:400;\"> is the temperature of the </span><span style=\" font-size:12pt;\">bubble's wall</span><span style=\" font-size:12pt; font-weight:400;\">.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        WallTemperatureLabel->setText(QApplication::translate("SimulationGUIClass", "Wall Temperature", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        EquilibriumRadiusLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Equilibrium Radius</span><span style=\" font-size:12pt; font-weight:400;\"> of the </span><span style=\" font-size:12pt;\">bubble</span><span style=\" font-size:12pt; font-weight:400;\">.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        EquilibriumRadiusLabel->setText(QApplication::translate("SimulationGUIClass", "Equilibrium Radius", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        DriverPressureLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Acoustic Driver Pressure.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        DriverPressureLabel->setText(QApplication::translate("SimulationGUIClass", "Driver Pressure", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        FrequencyLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Frequency</span><span style=\" font-size:12pt; font-weight:400;\">.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        FrequencyLabel->setText(QApplication::translate("SimulationGUIClass", "Frequency", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        InitialTimeLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Time Offset</span><span style=\" font-size:12pt; font-weight:400;\"> for the </span><span style=\" font-size:12pt;\">Acoustic Driver</span><span style=\" font-size:12pt; font-weight:400;\">. This will </span><span style=\" font-size:12pt;\">shift the sinusoid</span><span style=\" font-size:12pt; font-weight:400;\"> to the left or to the right.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        InitialTimeLabel->setText(QApplication::translate("SimulationGUIClass", "Initial Time", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        InitialRadiusLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Initial Radius</span><span style=\" font-size:12pt; font-weight:400;\"> of the</span><span style=\" font-size:12pt;\"> bubble</span><span style=\" font-size:12pt; font-weight:400;\">.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        InitialRadiusLabel->setText(QApplication::translate("SimulationGUIClass", "Initial Radius", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        InitialVelocityLabel->setToolTip(QApplication::translate("SimulationGUIClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:400;\">The </span><span style=\" font-size:12pt;\">Initial Velocity</span><span style=\" font-size:12pt; font-weight:400;\"> of the </span><span style=\" font-size:12pt;\">bubble wall</span><span style=\" font-size:12pt; font-weight:400;\">. A </span><span style=\" font-size:12pt;\">positive value</span><span style=\" font-size:12pt; font-weight:400;\"> indicates an </span><span style=\" font-size:12pt;\">expansion</span><span style=\" font-size:12pt; font-weight:400;\">, while a </span><span style=\" font-size:12pt;\">negative value</span><span style=\" font-size:12pt; font-weight:400;\"> indicates a </span><span style=\" font-size:12pt;\">compression</span><span style=\" font-size:12pt; font-weight:400;\">.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        InitialVelocityLabel->setText(QApplication::translate("SimulationGUIClass", "Initial Velocity", 0, QApplication::UnicodeUTF8));
        ConeAngleUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[\302\260Degrees]", 0, QApplication::UnicodeUTF8));
        TemperatureUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[\302\260Kelvin]", 0, QApplication::UnicodeUTF8));
        WallTemperatureUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[\302\260Kelvin]", 0, QApplication::UnicodeUTF8));
        EquilibriumRadiusUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[Meters]", 0, QApplication::UnicodeUTF8));
        DriverPressureUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[Bars]", 0, QApplication::UnicodeUTF8));
        FrequencyUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[Hertz]", 0, QApplication::UnicodeUTF8));
        InitialTimeUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[Seconds]", 0, QApplication::UnicodeUTF8));
        InitialRadiusUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[Meters]", 0, QApplication::UnicodeUTF8));
        InitialVelocityUnitsLabel->setText(QApplication::translate("SimulationGUIClass", "[Meters/Second]", 0, QApplication::UnicodeUTF8));
        GasComboBox2->clear();
        GasComboBox2->insertItems(0, QStringList()
         << QApplication::translate("SimulationGUIClass", "Deuterium", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Helium", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Neon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Argon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Xenon", 0, QApplication::UnicodeUTF8)
        );
        GasComboBox1->clear();
        GasComboBox1->insertItems(0, QStringList()
         << QApplication::translate("SimulationGUIClass", "Deuterium", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Helium", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Neon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Argon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationGUIClass", "Xenon", 0, QApplication::UnicodeUTF8)
        );
        GUITimerBox->setHtml(QApplication::translate("SimulationGUIClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:10pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt;\">00:00:00:000</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        TimerLabel->setText(QApplication::translate("SimulationGUIClass", "Simulation Run Time", 0, QApplication::UnicodeUTF8));
        Gas1Label->setText(QApplication::translate("SimulationGUIClass", "Gas 1", 0, QApplication::UnicodeUTF8));
        Gas2Label->setText(QApplication::translate("SimulationGUIClass", "Gas 2", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("SimulationGUIClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("SimulationGUIClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimulationGUIClass: public Ui_SimulationGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONGUI_H
