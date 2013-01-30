/********************************************************************************
** Form generated from reading UI file 'simulationplotgui.ui'
**
** Created: Wed Jan 23 03:09:51 2013
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
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationPlotGUIClass
{
public:
    QAction *actionChange_Directory;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *GraphsTab;
    QSlider *SeekSlider;
    QLabel *CurrentSnapshotLabel;
    QFrame *CurrentSnapshotLine;
    QLineEdit *CurrentSnapshotLineEdit;
    QPushButton *StartButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *TimeLabel;
    QLabel *WallRadiusLabel;
    QLabel *WallVelocityLabel;
    QLabel *MaxPressureLabel;
    QLabel *AveragePressureLabel;
    QLabel *MaxTemperatureLabel;
    QLabel *AverageTemperatureLabel;
    QLabel *MaxEnergyLabel;
    QLabel *AverageEnergyLabel;
    QLabel *NumberOfFusionsLabel;
    QLabel *MaxDensityLabel;
    QLabel *AverageDensityLabel;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *TimeLineEdit;
    QLineEdit *WallRadiusLineEdit;
    QLineEdit *WallVelocityLineEdit;
    QLineEdit *MaxPressureLineEdit;
    QLineEdit *AveragePressureLineEdit;
    QLineEdit *MaxTemperatureLineEdit;
    QLineEdit *AverageTemperatureLineEdit;
    QLineEdit *MaxEnergyLineEdit;
    QLineEdit *AverageEnergyLineEdit;
    QLineEdit *NumberOfFusionsLineEdit;
    QLineEdit *MaxDensityLineEdit;
    QLineEdit *AverageDensityLineEdit;
    QListWidget *GraphAreaWidget;
    QPushButton *EnlargeGraphButton;
    QPushButton *ShrinkGraphButton;
    QWidget *PreferencesTab;
    QLabel *ViewModeLabel;
    QComboBox *ViewModeComboBox;
    QLabel *DimensionsLabel;
    QComboBox *DimensionsComboBox;
    QLabel *RefreshIntervalLabel;
    QSlider *RefreshIntervalSlider;
    QLabel *RefreshIntervalSecondsLabel;
    QLabel *SimulationDirectoryLabel;
    QLineEdit *SimulationDirectoryLineEdit;
    QPushButton *BrowseDirectoryButton;
    QLabel *SimulationDirectoryDescLabel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulationPlotGUIClass)
    {
        if (SimulationPlotGUIClass->objectName().isEmpty())
            SimulationPlotGUIClass->setObjectName(QString::fromUtf8("SimulationPlotGUIClass"));
        SimulationPlotGUIClass->resize(1204, 700);
        SimulationPlotGUIClass->setLayoutDirection(Qt::LeftToRight);
        actionChange_Directory = new QAction(SimulationPlotGUIClass);
        actionChange_Directory->setObjectName(QString::fromUtf8("actionChange_Directory"));
        centralWidget = new QWidget(SimulationPlotGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideRight);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);
        GraphsTab = new QWidget();
        GraphsTab->setObjectName(QString::fromUtf8("GraphsTab"));
        SeekSlider = new QSlider(GraphsTab);
        SeekSlider->setObjectName(QString::fromUtf8("SeekSlider"));
        SeekSlider->setGeometry(QRect(10, 570, 561, 31));
        SeekSlider->setOrientation(Qt::Horizontal);
        CurrentSnapshotLabel = new QLabel(GraphsTab);
        CurrentSnapshotLabel->setObjectName(QString::fromUtf8("CurrentSnapshotLabel"));
        CurrentSnapshotLabel->setGeometry(QRect(10, 540, 261, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        CurrentSnapshotLabel->setFont(font);
        CurrentSnapshotLine = new QFrame(GraphsTab);
        CurrentSnapshotLine->setObjectName(QString::fromUtf8("CurrentSnapshotLine"));
        CurrentSnapshotLine->setGeometry(QRect(10, 560, 191, 16));
        CurrentSnapshotLine->setFrameShape(QFrame::HLine);
        CurrentSnapshotLine->setFrameShadow(QFrame::Sunken);
        CurrentSnapshotLineEdit = new QLineEdit(GraphsTab);
        CurrentSnapshotLineEdit->setObjectName(QString::fromUtf8("CurrentSnapshotLineEdit"));
        CurrentSnapshotLineEdit->setGeometry(QRect(210, 550, 151, 21));
        QFont font1;
        font1.setPointSize(12);
        CurrentSnapshotLineEdit->setFont(font1);
        CurrentSnapshotLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        StartButton = new QPushButton(GraphsTab);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        StartButton->setGeometry(QRect(610, 540, 231, 51));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        StartButton->setFont(font2);
        layoutWidget = new QWidget(GraphsTab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(820, 10, 194, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TimeLabel = new QLabel(layoutWidget);
        TimeLabel->setObjectName(QString::fromUtf8("TimeLabel"));

        verticalLayout->addWidget(TimeLabel);

        WallRadiusLabel = new QLabel(layoutWidget);
        WallRadiusLabel->setObjectName(QString::fromUtf8("WallRadiusLabel"));

        verticalLayout->addWidget(WallRadiusLabel);

        WallVelocityLabel = new QLabel(layoutWidget);
        WallVelocityLabel->setObjectName(QString::fromUtf8("WallVelocityLabel"));

        verticalLayout->addWidget(WallVelocityLabel);

        MaxPressureLabel = new QLabel(layoutWidget);
        MaxPressureLabel->setObjectName(QString::fromUtf8("MaxPressureLabel"));

        verticalLayout->addWidget(MaxPressureLabel);

        AveragePressureLabel = new QLabel(layoutWidget);
        AveragePressureLabel->setObjectName(QString::fromUtf8("AveragePressureLabel"));

        verticalLayout->addWidget(AveragePressureLabel);

        MaxTemperatureLabel = new QLabel(layoutWidget);
        MaxTemperatureLabel->setObjectName(QString::fromUtf8("MaxTemperatureLabel"));

        verticalLayout->addWidget(MaxTemperatureLabel);

        AverageTemperatureLabel = new QLabel(layoutWidget);
        AverageTemperatureLabel->setObjectName(QString::fromUtf8("AverageTemperatureLabel"));

        verticalLayout->addWidget(AverageTemperatureLabel);

        MaxEnergyLabel = new QLabel(layoutWidget);
        MaxEnergyLabel->setObjectName(QString::fromUtf8("MaxEnergyLabel"));

        verticalLayout->addWidget(MaxEnergyLabel);

        AverageEnergyLabel = new QLabel(layoutWidget);
        AverageEnergyLabel->setObjectName(QString::fromUtf8("AverageEnergyLabel"));

        verticalLayout->addWidget(AverageEnergyLabel);

        NumberOfFusionsLabel = new QLabel(layoutWidget);
        NumberOfFusionsLabel->setObjectName(QString::fromUtf8("NumberOfFusionsLabel"));

        verticalLayout->addWidget(NumberOfFusionsLabel);

        MaxDensityLabel = new QLabel(layoutWidget);
        MaxDensityLabel->setObjectName(QString::fromUtf8("MaxDensityLabel"));

        verticalLayout->addWidget(MaxDensityLabel);

        AverageDensityLabel = new QLabel(layoutWidget);
        AverageDensityLabel->setObjectName(QString::fromUtf8("AverageDensityLabel"));

        verticalLayout->addWidget(AverageDensityLabel);

        layoutWidget_2 = new QWidget(GraphsTab);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(1024, 10, 146, 501));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TimeLineEdit = new QLineEdit(layoutWidget_2);
        TimeLineEdit->setObjectName(QString::fromUtf8("TimeLineEdit"));
        TimeLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(TimeLineEdit);

        WallRadiusLineEdit = new QLineEdit(layoutWidget_2);
        WallRadiusLineEdit->setObjectName(QString::fromUtf8("WallRadiusLineEdit"));
        WallRadiusLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(WallRadiusLineEdit);

        WallVelocityLineEdit = new QLineEdit(layoutWidget_2);
        WallVelocityLineEdit->setObjectName(QString::fromUtf8("WallVelocityLineEdit"));
        WallVelocityLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(WallVelocityLineEdit);

        MaxPressureLineEdit = new QLineEdit(layoutWidget_2);
        MaxPressureLineEdit->setObjectName(QString::fromUtf8("MaxPressureLineEdit"));
        MaxPressureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxPressureLineEdit);

        AveragePressureLineEdit = new QLineEdit(layoutWidget_2);
        AveragePressureLineEdit->setObjectName(QString::fromUtf8("AveragePressureLineEdit"));
        AveragePressureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AveragePressureLineEdit);

        MaxTemperatureLineEdit = new QLineEdit(layoutWidget_2);
        MaxTemperatureLineEdit->setObjectName(QString::fromUtf8("MaxTemperatureLineEdit"));
        MaxTemperatureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxTemperatureLineEdit);

        AverageTemperatureLineEdit = new QLineEdit(layoutWidget_2);
        AverageTemperatureLineEdit->setObjectName(QString::fromUtf8("AverageTemperatureLineEdit"));
        AverageTemperatureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AverageTemperatureLineEdit);

        MaxEnergyLineEdit = new QLineEdit(layoutWidget_2);
        MaxEnergyLineEdit->setObjectName(QString::fromUtf8("MaxEnergyLineEdit"));
        MaxEnergyLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxEnergyLineEdit);

        AverageEnergyLineEdit = new QLineEdit(layoutWidget_2);
        AverageEnergyLineEdit->setObjectName(QString::fromUtf8("AverageEnergyLineEdit"));
        AverageEnergyLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AverageEnergyLineEdit);

        NumberOfFusionsLineEdit = new QLineEdit(layoutWidget_2);
        NumberOfFusionsLineEdit->setObjectName(QString::fromUtf8("NumberOfFusionsLineEdit"));
        NumberOfFusionsLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(NumberOfFusionsLineEdit);

        MaxDensityLineEdit = new QLineEdit(layoutWidget_2);
        MaxDensityLineEdit->setObjectName(QString::fromUtf8("MaxDensityLineEdit"));
        MaxDensityLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxDensityLineEdit);

        AverageDensityLineEdit = new QLineEdit(layoutWidget_2);
        AverageDensityLineEdit->setObjectName(QString::fromUtf8("AverageDensityLineEdit"));
        AverageDensityLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AverageDensityLineEdit);

        GraphAreaWidget = new QListWidget(GraphsTab);
        GraphAreaWidget->setObjectName(QString::fromUtf8("GraphAreaWidget"));
        GraphAreaWidget->setGeometry(QRect(5, 1, 801, 511));
        GraphAreaWidget->setFrameShape(QFrame::NoFrame);
        GraphAreaWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        GraphAreaWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        EnlargeGraphButton = new QPushButton(GraphsTab);
        EnlargeGraphButton->setObjectName(QString::fromUtf8("EnlargeGraphButton"));
        EnlargeGraphButton->setGeometry(QRect(10, 520, 31, 21));
        ShrinkGraphButton = new QPushButton(GraphsTab);
        ShrinkGraphButton->setObjectName(QString::fromUtf8("ShrinkGraphButton"));
        ShrinkGraphButton->setGeometry(QRect(50, 520, 31, 21));
        tabWidget->addTab(GraphsTab, QString());
        PreferencesTab = new QWidget();
        PreferencesTab->setObjectName(QString::fromUtf8("PreferencesTab"));
        ViewModeLabel = new QLabel(PreferencesTab);
        ViewModeLabel->setObjectName(QString::fromUtf8("ViewModeLabel"));
        ViewModeLabel->setGeometry(QRect(70, 30, 121, 31));
        ViewModeComboBox = new QComboBox(PreferencesTab);
        ViewModeComboBox->setObjectName(QString::fromUtf8("ViewModeComboBox"));
        ViewModeComboBox->setGeometry(QRect(190, 30, 161, 26));
        DimensionsLabel = new QLabel(PreferencesTab);
        DimensionsLabel->setObjectName(QString::fromUtf8("DimensionsLabel"));
        DimensionsLabel->setGeometry(QRect(70, 80, 91, 16));
        DimensionsComboBox = new QComboBox(PreferencesTab);
        DimensionsComboBox->setObjectName(QString::fromUtf8("DimensionsComboBox"));
        DimensionsComboBox->setGeometry(QRect(190, 70, 161, 26));
        RefreshIntervalLabel = new QLabel(PreferencesTab);
        RefreshIntervalLabel->setObjectName(QString::fromUtf8("RefreshIntervalLabel"));
        RefreshIntervalLabel->setGeometry(QRect(70, 120, 111, 21));
        RefreshIntervalSlider = new QSlider(PreferencesTab);
        RefreshIntervalSlider->setObjectName(QString::fromUtf8("RefreshIntervalSlider"));
        RefreshIntervalSlider->setGeometry(QRect(190, 120, 160, 22));
        RefreshIntervalSlider->setOrientation(Qt::Horizontal);
        RefreshIntervalSecondsLabel = new QLabel(PreferencesTab);
        RefreshIntervalSecondsLabel->setObjectName(QString::fromUtf8("RefreshIntervalSecondsLabel"));
        RefreshIntervalSecondsLabel->setGeometry(QRect(370, 120, 131, 16));
        SimulationDirectoryLabel = new QLabel(PreferencesTab);
        SimulationDirectoryLabel->setObjectName(QString::fromUtf8("SimulationDirectoryLabel"));
        SimulationDirectoryLabel->setGeometry(QRect(620, 20, 211, 31));
        QFont font3;
        font3.setPointSize(18);
        SimulationDirectoryLabel->setFont(font3);
        SimulationDirectoryLineEdit = new QLineEdit(PreferencesTab);
        SimulationDirectoryLineEdit->setObjectName(QString::fromUtf8("SimulationDirectoryLineEdit"));
        SimulationDirectoryLineEdit->setGeometry(QRect(620, 110, 351, 21));
        SimulationDirectoryLineEdit->setReadOnly(true);
        BrowseDirectoryButton = new QPushButton(PreferencesTab);
        BrowseDirectoryButton->setObjectName(QString::fromUtf8("BrowseDirectoryButton"));
        BrowseDirectoryButton->setGeometry(QRect(620, 140, 121, 21));
        SimulationDirectoryDescLabel = new QLabel(PreferencesTab);
        SimulationDirectoryDescLabel->setObjectName(QString::fromUtf8("SimulationDirectoryDescLabel"));
        SimulationDirectoryDescLabel->setGeometry(QRect(620, 50, 391, 51));
        tabWidget->addTab(PreferencesTab, QString());

        verticalLayout_3->addWidget(tabWidget);

        SimulationPlotGUIClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(SimulationPlotGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimulationPlotGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SimulationPlotGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimulationPlotGUIClass->setStatusBar(statusBar);

        retranslateUi(SimulationPlotGUIClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimulationPlotGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationPlotGUIClass)
    {
        SimulationPlotGUIClass->setWindowTitle(QApplication::translate("SimulationPlotGUIClass", "SimulationPlotGUI", 0, QApplication::UnicodeUTF8));
        actionChange_Directory->setText(QApplication::translate("SimulationPlotGUIClass", "Change Directory...", 0, QApplication::UnicodeUTF8));
        CurrentSnapshotLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Current Snapshot Number : ", 0, QApplication::UnicodeUTF8));
        CurrentSnapshotLineEdit->setText(QApplication::translate("SimulationPlotGUIClass", "0", 0, QApplication::UnicodeUTF8));
        StartButton->setText(QApplication::translate("SimulationPlotGUIClass", "Start", 0, QApplication::UnicodeUTF8));
        TimeLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Time ( t ) : ", 0, QApplication::UnicodeUTF8));
        WallRadiusLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Wall Radius ( R<sub>Wall</sub> ) :", 0, QApplication::UnicodeUTF8));
        WallVelocityLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Wall Velocity ( V<span style=\" vertical-align:sub;\">Wall</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        MaxPressureLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Max Pressure ( P<sub>Max</sub> ) : ", 0, QApplication::UnicodeUTF8));
        AveragePressureLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Average Pressure ( P<sub>Avg</sub> ) : ", 0, QApplication::UnicodeUTF8));
        MaxTemperatureLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Max Temperature ( T<span style=\" vertical-align:sub;\">Max</span>) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        AverageTemperatureLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Average Temperature ( T<span style=\" vertical-align:sub;\">Avg </span>) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        MaxEnergyLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Max Energy ( E<span style=\" vertical-align:sub;\">Max</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        AverageEnergyLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Average Energy ( E<span style=\" vertical-align:sub;\">Max</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        NumberOfFusionsLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Number of Fusions ( N<span style=\" vertical-align:sub;\">Fusions</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        MaxDensityLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head><meta http-equiv = \"content-type\" content = \"text/html; charset = utf-8\"></head><body>Max Density ( &#961;<sub>Max</sub> ) : </body></html>", 0, QApplication::UnicodeUTF8));
        AverageDensityLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Average Density ( \317\201<span style=\" vertical-align:sub;\">Avg</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        EnlargeGraphButton->setText(QApplication::translate("SimulationPlotGUIClass", "+", 0, QApplication::UnicodeUTF8));
        ShrinkGraphButton->setText(QApplication::translate("SimulationPlotGUIClass", "-", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(GraphsTab), QApplication::translate("SimulationPlotGUIClass", "Graphs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ViewModeLabel->setToolTip(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>Changes the Detail of Text Shown:</p><p><br/></p><p>Simple View - example : &quot; T&lt;sub&gt;Max&lt;/sub&gt;&quot;</p><p><br/></p><p>Complex View - example : &quot;Max Temperature ( T&lt;sub&gt;Max&lt;/sub&gt; )&quot;</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ViewModeLabel->setText(QApplication::translate("SimulationPlotGUIClass", "View Mode : ", 0, QApplication::UnicodeUTF8));
        ViewModeComboBox->clear();
        ViewModeComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimulationPlotGUIClass", "Complex View", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationPlotGUIClass", "Simple View", 0, QApplication::UnicodeUTF8)
        );
        DimensionsLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Dimensions : ", 0, QApplication::UnicodeUTF8));
        DimensionsComboBox->clear();
        DimensionsComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimulationPlotGUIClass", "800 x 600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationPlotGUIClass", "1024 x 768", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SimulationPlotGUIClass", "1280 x 800", 0, QApplication::UnicodeUTF8)
        );
        RefreshIntervalLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Refresh Interval : ", 0, QApplication::UnicodeUTF8));
        RefreshIntervalSecondsLabel->setText(QApplication::translate("SimulationPlotGUIClass", "100 Milliseconds", 0, QApplication::UnicodeUTF8));
        SimulationDirectoryLabel->setText(QApplication::translate("SimulationPlotGUIClass", "Simulation Directory", 0, QApplication::UnicodeUTF8));
        BrowseDirectoryButton->setText(QApplication::translate("SimulationPlotGUIClass", "Browse...", 0, QApplication::UnicodeUTF8));
        SimulationDirectoryDescLabel->setText(QApplication::translate("SimulationPlotGUIClass", "<html><head/><body><p>You can change the simulation directory here.</p><p>The data read from the directory will be loaded immediately.</p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(PreferencesTab), QApplication::translate("SimulationPlotGUIClass", "Preferences", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimulationPlotGUIClass: public Ui_SimulationPlotGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONPLOTGUI_H
