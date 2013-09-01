/********************************************************************************
** Form generated from reading UI file 'DataVisualizerGUI.ui'
**
** Created: Fri Aug 16 06:20:30 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAVISUALIZERGUI_H
#define UI_DATAVISUALIZERGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataVisualizerGUIClass
{
public:
    QAction *actionChange_Directory;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *GraphsTab;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_7;
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
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *EnlargeGraphButton;
    QPushButton *ShrinkGraphButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *CurrentSnapshotLabel;
    QLineEdit *CurrentSnapshotLineEdit;
    QSpacerItem *horizontalSpacer;
    QSlider *SeekSlider;
    QPushButton *StartButton;
    QScrollArea *GraphScrollArea;
    QWidget *PlotArea;
    QWidget *PreferencesTab;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *ViewModeLabel;
    QLabel *RefreshIntervalMSLabel;
    QComboBox *ViewModeComboBox;
    QLabel *RefreshIntervalLabel;
    QSlider *RefreshIntervalSlider;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *SimulationDirectoryLabel;
    QLabel *SimulationDirectoryDescLabel;
    QLineEdit *SimulationDirectoryLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *BrowseDirectoryButton;
    QPushButton *DirLoadButton;
    QSpacerItem *verticalSpacer_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DataVisualizerGUIClass)
    {
        if (DataVisualizerGUIClass->objectName().isEmpty())
            DataVisualizerGUIClass->setObjectName(QString::fromUtf8("DataVisualizerGUIClass"));
        DataVisualizerGUIClass->resize(1204, 700);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(252, 252, 252, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        DataVisualizerGUIClass->setPalette(palette);
        DataVisualizerGUIClass->setLayoutDirection(Qt::LeftToRight);
        actionChange_Directory = new QAction(DataVisualizerGUIClass);
        actionChange_Directory->setObjectName(QString::fromUtf8("actionChange_Directory"));
        centralWidget = new QWidget(DataVisualizerGUIClass);
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
        gridLayout_6 = new QGridLayout(GraphsTab);
        gridLayout_6->setSpacing(15);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        TimeLabel = new QLabel(GraphsTab);
        TimeLabel->setObjectName(QString::fromUtf8("TimeLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TimeLabel->sizePolicy().hasHeightForWidth());
        TimeLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(TimeLabel);

        WallRadiusLabel = new QLabel(GraphsTab);
        WallRadiusLabel->setObjectName(QString::fromUtf8("WallRadiusLabel"));
        sizePolicy.setHeightForWidth(WallRadiusLabel->sizePolicy().hasHeightForWidth());
        WallRadiusLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(WallRadiusLabel);

        WallVelocityLabel = new QLabel(GraphsTab);
        WallVelocityLabel->setObjectName(QString::fromUtf8("WallVelocityLabel"));
        sizePolicy.setHeightForWidth(WallVelocityLabel->sizePolicy().hasHeightForWidth());
        WallVelocityLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(WallVelocityLabel);

        MaxPressureLabel = new QLabel(GraphsTab);
        MaxPressureLabel->setObjectName(QString::fromUtf8("MaxPressureLabel"));
        sizePolicy.setHeightForWidth(MaxPressureLabel->sizePolicy().hasHeightForWidth());
        MaxPressureLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(MaxPressureLabel);

        AveragePressureLabel = new QLabel(GraphsTab);
        AveragePressureLabel->setObjectName(QString::fromUtf8("AveragePressureLabel"));
        sizePolicy.setHeightForWidth(AveragePressureLabel->sizePolicy().hasHeightForWidth());
        AveragePressureLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(AveragePressureLabel);

        MaxTemperatureLabel = new QLabel(GraphsTab);
        MaxTemperatureLabel->setObjectName(QString::fromUtf8("MaxTemperatureLabel"));
        sizePolicy.setHeightForWidth(MaxTemperatureLabel->sizePolicy().hasHeightForWidth());
        MaxTemperatureLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(MaxTemperatureLabel);

        AverageTemperatureLabel = new QLabel(GraphsTab);
        AverageTemperatureLabel->setObjectName(QString::fromUtf8("AverageTemperatureLabel"));
        sizePolicy.setHeightForWidth(AverageTemperatureLabel->sizePolicy().hasHeightForWidth());
        AverageTemperatureLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(AverageTemperatureLabel);

        MaxEnergyLabel = new QLabel(GraphsTab);
        MaxEnergyLabel->setObjectName(QString::fromUtf8("MaxEnergyLabel"));
        sizePolicy.setHeightForWidth(MaxEnergyLabel->sizePolicy().hasHeightForWidth());
        MaxEnergyLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(MaxEnergyLabel);

        AverageEnergyLabel = new QLabel(GraphsTab);
        AverageEnergyLabel->setObjectName(QString::fromUtf8("AverageEnergyLabel"));
        sizePolicy.setHeightForWidth(AverageEnergyLabel->sizePolicy().hasHeightForWidth());
        AverageEnergyLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(AverageEnergyLabel);

        NumberOfFusionsLabel = new QLabel(GraphsTab);
        NumberOfFusionsLabel->setObjectName(QString::fromUtf8("NumberOfFusionsLabel"));
        sizePolicy.setHeightForWidth(NumberOfFusionsLabel->sizePolicy().hasHeightForWidth());
        NumberOfFusionsLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(NumberOfFusionsLabel);

        MaxDensityLabel = new QLabel(GraphsTab);
        MaxDensityLabel->setObjectName(QString::fromUtf8("MaxDensityLabel"));
        sizePolicy.setHeightForWidth(MaxDensityLabel->sizePolicy().hasHeightForWidth());
        MaxDensityLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(MaxDensityLabel);

        AverageDensityLabel = new QLabel(GraphsTab);
        AverageDensityLabel->setObjectName(QString::fromUtf8("AverageDensityLabel"));
        sizePolicy.setHeightForWidth(AverageDensityLabel->sizePolicy().hasHeightForWidth());
        AverageDensityLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(AverageDensityLabel);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        TimeLineEdit = new QLineEdit(GraphsTab);
        TimeLineEdit->setObjectName(QString::fromUtf8("TimeLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TimeLineEdit->sizePolicy().hasHeightForWidth());
        TimeLineEdit->setSizePolicy(sizePolicy1);
        TimeLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(TimeLineEdit);

        WallRadiusLineEdit = new QLineEdit(GraphsTab);
        WallRadiusLineEdit->setObjectName(QString::fromUtf8("WallRadiusLineEdit"));
        sizePolicy1.setHeightForWidth(WallRadiusLineEdit->sizePolicy().hasHeightForWidth());
        WallRadiusLineEdit->setSizePolicy(sizePolicy1);
        WallRadiusLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(WallRadiusLineEdit);

        WallVelocityLineEdit = new QLineEdit(GraphsTab);
        WallVelocityLineEdit->setObjectName(QString::fromUtf8("WallVelocityLineEdit"));
        sizePolicy1.setHeightForWidth(WallVelocityLineEdit->sizePolicy().hasHeightForWidth());
        WallVelocityLineEdit->setSizePolicy(sizePolicy1);
        WallVelocityLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(WallVelocityLineEdit);

        MaxPressureLineEdit = new QLineEdit(GraphsTab);
        MaxPressureLineEdit->setObjectName(QString::fromUtf8("MaxPressureLineEdit"));
        sizePolicy1.setHeightForWidth(MaxPressureLineEdit->sizePolicy().hasHeightForWidth());
        MaxPressureLineEdit->setSizePolicy(sizePolicy1);
        MaxPressureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxPressureLineEdit);

        AveragePressureLineEdit = new QLineEdit(GraphsTab);
        AveragePressureLineEdit->setObjectName(QString::fromUtf8("AveragePressureLineEdit"));
        sizePolicy1.setHeightForWidth(AveragePressureLineEdit->sizePolicy().hasHeightForWidth());
        AveragePressureLineEdit->setSizePolicy(sizePolicy1);
        AveragePressureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AveragePressureLineEdit);

        MaxTemperatureLineEdit = new QLineEdit(GraphsTab);
        MaxTemperatureLineEdit->setObjectName(QString::fromUtf8("MaxTemperatureLineEdit"));
        sizePolicy1.setHeightForWidth(MaxTemperatureLineEdit->sizePolicy().hasHeightForWidth());
        MaxTemperatureLineEdit->setSizePolicy(sizePolicy1);
        MaxTemperatureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxTemperatureLineEdit);

        AverageTemperatureLineEdit = new QLineEdit(GraphsTab);
        AverageTemperatureLineEdit->setObjectName(QString::fromUtf8("AverageTemperatureLineEdit"));
        sizePolicy1.setHeightForWidth(AverageTemperatureLineEdit->sizePolicy().hasHeightForWidth());
        AverageTemperatureLineEdit->setSizePolicy(sizePolicy1);
        AverageTemperatureLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AverageTemperatureLineEdit);

        MaxEnergyLineEdit = new QLineEdit(GraphsTab);
        MaxEnergyLineEdit->setObjectName(QString::fromUtf8("MaxEnergyLineEdit"));
        sizePolicy1.setHeightForWidth(MaxEnergyLineEdit->sizePolicy().hasHeightForWidth());
        MaxEnergyLineEdit->setSizePolicy(sizePolicy1);
        MaxEnergyLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxEnergyLineEdit);

        AverageEnergyLineEdit = new QLineEdit(GraphsTab);
        AverageEnergyLineEdit->setObjectName(QString::fromUtf8("AverageEnergyLineEdit"));
        sizePolicy1.setHeightForWidth(AverageEnergyLineEdit->sizePolicy().hasHeightForWidth());
        AverageEnergyLineEdit->setSizePolicy(sizePolicy1);
        AverageEnergyLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AverageEnergyLineEdit);

        NumberOfFusionsLineEdit = new QLineEdit(GraphsTab);
        NumberOfFusionsLineEdit->setObjectName(QString::fromUtf8("NumberOfFusionsLineEdit"));
        sizePolicy1.setHeightForWidth(NumberOfFusionsLineEdit->sizePolicy().hasHeightForWidth());
        NumberOfFusionsLineEdit->setSizePolicy(sizePolicy1);
        NumberOfFusionsLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(NumberOfFusionsLineEdit);

        MaxDensityLineEdit = new QLineEdit(GraphsTab);
        MaxDensityLineEdit->setObjectName(QString::fromUtf8("MaxDensityLineEdit"));
        sizePolicy1.setHeightForWidth(MaxDensityLineEdit->sizePolicy().hasHeightForWidth());
        MaxDensityLineEdit->setSizePolicy(sizePolicy1);
        MaxDensityLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(MaxDensityLineEdit);

        AverageDensityLineEdit = new QLineEdit(GraphsTab);
        AverageDensityLineEdit->setObjectName(QString::fromUtf8("AverageDensityLineEdit"));
        sizePolicy1.setHeightForWidth(AverageDensityLineEdit->sizePolicy().hasHeightForWidth());
        AverageDensityLineEdit->setSizePolicy(sizePolicy1);
        AverageDensityLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(AverageDensityLineEdit);


        horizontalLayout_7->addLayout(verticalLayout_2);


        gridLayout_6->addLayout(horizontalLayout_7, 0, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        EnlargeGraphButton = new QPushButton(GraphsTab);
        EnlargeGraphButton->setObjectName(QString::fromUtf8("EnlargeGraphButton"));
        sizePolicy1.setHeightForWidth(EnlargeGraphButton->sizePolicy().hasHeightForWidth());
        EnlargeGraphButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(EnlargeGraphButton);

        ShrinkGraphButton = new QPushButton(GraphsTab);
        ShrinkGraphButton->setObjectName(QString::fromUtf8("ShrinkGraphButton"));
        sizePolicy1.setHeightForWidth(ShrinkGraphButton->sizePolicy().hasHeightForWidth());
        ShrinkGraphButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(ShrinkGraphButton);

        horizontalSpacer_2 = new QSpacerItem(458, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        CurrentSnapshotLabel = new QLabel(GraphsTab);
        CurrentSnapshotLabel->setObjectName(QString::fromUtf8("CurrentSnapshotLabel"));
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        CurrentSnapshotLabel->setFont(font);

        horizontalLayout->addWidget(CurrentSnapshotLabel);

        CurrentSnapshotLineEdit = new QLineEdit(GraphsTab);
        CurrentSnapshotLineEdit->setObjectName(QString::fromUtf8("CurrentSnapshotLineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(CurrentSnapshotLineEdit->sizePolicy().hasHeightForWidth());
        CurrentSnapshotLineEdit->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(12);
        CurrentSnapshotLineEdit->setFont(font1);
        CurrentSnapshotLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(CurrentSnapshotLineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        SeekSlider = new QSlider(GraphsTab);
        SeekSlider->setObjectName(QString::fromUtf8("SeekSlider"));
        SeekSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(SeekSlider);


        gridLayout_6->addLayout(verticalLayout_4, 1, 0, 1, 1);

        StartButton = new QPushButton(GraphsTab);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        StartButton->setFont(font2);

        gridLayout_6->addWidget(StartButton, 1, 1, 1, 1);

        GraphScrollArea = new QScrollArea(GraphsTab);
        GraphScrollArea->setObjectName(QString::fromUtf8("GraphScrollArea"));
        GraphScrollArea->setFocusPolicy(Qt::ClickFocus);
        GraphScrollArea->setLayoutDirection(Qt::LeftToRight);
        GraphScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        GraphScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        GraphScrollArea->setWidgetResizable(false);
        PlotArea = new QWidget();
        PlotArea->setObjectName(QString::fromUtf8("PlotArea"));
        PlotArea->setGeometry(QRect(0, 0, 850, 498));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(PlotArea->sizePolicy().hasHeightForWidth());
        PlotArea->setSizePolicy(sizePolicy4);
        GraphScrollArea->setWidget(PlotArea);

        gridLayout_6->addWidget(GraphScrollArea, 0, 0, 1, 1);

        tabWidget->addTab(GraphsTab, QString());
        PreferencesTab = new QWidget();
        PreferencesTab->setObjectName(QString::fromUtf8("PreferencesTab"));
        gridLayout_3 = new QGridLayout(PreferencesTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(10, 30, 10, -1);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        ViewModeLabel = new QLabel(PreferencesTab);
        ViewModeLabel->setObjectName(QString::fromUtf8("ViewModeLabel"));

        gridLayout_2->addWidget(ViewModeLabel, 1, 0, 1, 1);

        RefreshIntervalMSLabel = new QLabel(PreferencesTab);
        RefreshIntervalMSLabel->setObjectName(QString::fromUtf8("RefreshIntervalMSLabel"));

        gridLayout_2->addWidget(RefreshIntervalMSLabel, 2, 2, 1, 1);

        ViewModeComboBox = new QComboBox(PreferencesTab);
        ViewModeComboBox->setObjectName(QString::fromUtf8("ViewModeComboBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(ViewModeComboBox->sizePolicy().hasHeightForWidth());
        ViewModeComboBox->setSizePolicy(sizePolicy5);

        gridLayout_2->addWidget(ViewModeComboBox, 1, 1, 1, 1);

        RefreshIntervalLabel = new QLabel(PreferencesTab);
        RefreshIntervalLabel->setObjectName(QString::fromUtf8("RefreshIntervalLabel"));

        gridLayout_2->addWidget(RefreshIntervalLabel, 2, 0, 1, 1);

        RefreshIntervalSlider = new QSlider(PreferencesTab);
        RefreshIntervalSlider->setObjectName(QString::fromUtf8("RefreshIntervalSlider"));
        RefreshIntervalSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(RefreshIntervalSlider, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(380, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 298, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 298, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 1, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(20);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        SimulationDirectoryLabel = new QLabel(PreferencesTab);
        SimulationDirectoryLabel->setObjectName(QString::fromUtf8("SimulationDirectoryLabel"));
        sizePolicy5.setHeightForWidth(SimulationDirectoryLabel->sizePolicy().hasHeightForWidth());
        SimulationDirectoryLabel->setSizePolicy(sizePolicy5);
        QFont font3;
        font3.setPointSize(18);
        SimulationDirectoryLabel->setFont(font3);

        verticalLayout_5->addWidget(SimulationDirectoryLabel);

        SimulationDirectoryDescLabel = new QLabel(PreferencesTab);
        SimulationDirectoryDescLabel->setObjectName(QString::fromUtf8("SimulationDirectoryDescLabel"));
        sizePolicy5.setHeightForWidth(SimulationDirectoryDescLabel->sizePolicy().hasHeightForWidth());
        SimulationDirectoryDescLabel->setSizePolicy(sizePolicy5);

        verticalLayout_5->addWidget(SimulationDirectoryDescLabel);

        SimulationDirectoryLineEdit = new QLineEdit(PreferencesTab);
        SimulationDirectoryLineEdit->setObjectName(QString::fromUtf8("SimulationDirectoryLineEdit"));
        SimulationDirectoryLineEdit->setReadOnly(true);

        verticalLayout_5->addWidget(SimulationDirectoryLineEdit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, -1, -1, -1);
        horizontalSpacer_4 = new QSpacerItem(198, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        BrowseDirectoryButton = new QPushButton(PreferencesTab);
        BrowseDirectoryButton->setObjectName(QString::fromUtf8("BrowseDirectoryButton"));

        horizontalLayout_4->addWidget(BrowseDirectoryButton);

        DirLoadButton = new QPushButton(PreferencesTab);
        DirLoadButton->setObjectName(QString::fromUtf8("DirLoadButton"));

        horizontalLayout_4->addWidget(DirLoadButton);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);


        gridLayout_3->addLayout(verticalLayout_5, 0, 1, 1, 1);

        tabWidget->addTab(PreferencesTab, QString());

        verticalLayout_3->addWidget(tabWidget);

        DataVisualizerGUIClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(DataVisualizerGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DataVisualizerGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DataVisualizerGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DataVisualizerGUIClass->setStatusBar(statusBar);

        retranslateUi(DataVisualizerGUIClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DataVisualizerGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *DataVisualizerGUIClass)
    {
        DataVisualizerGUIClass->setWindowTitle(QApplication::translate("DataVisualizerGUIClass", "DataVisualizer", 0, QApplication::UnicodeUTF8));
        actionChange_Directory->setText(QApplication::translate("DataVisualizerGUIClass", "Change Directory...", 0, QApplication::UnicodeUTF8));
        TimeLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Time ( t ) : ", 0, QApplication::UnicodeUTF8));
        WallRadiusLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Wall Radius ( R<sub>Wall</sub> ) :", 0, QApplication::UnicodeUTF8));
        WallVelocityLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Wall Velocity ( V<span style=\" vertical-align:sub;\">Wall</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        MaxPressureLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Max Pressure ( P<sub>Max</sub> ) : ", 0, QApplication::UnicodeUTF8));
        AveragePressureLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Average Pressure ( P<sub>Avg</sub> ) : ", 0, QApplication::UnicodeUTF8));
        MaxTemperatureLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Max Temperature ( T<span style=\" vertical-align:sub;\">Max</span>) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        AverageTemperatureLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Average Temperature ( T<span style=\" vertical-align:sub;\">Avg </span>) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        MaxEnergyLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Max Energy ( E<span style=\" vertical-align:sub;\">Max</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        AverageEnergyLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Average Energy ( E<span style=\" vertical-align:sub;\">Max</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        NumberOfFusionsLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Number of Fusions ( N<span style=\" vertical-align:sub;\">Fusions</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        MaxDensityLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head><meta http-equiv = \"content-type\" content = \"text/html; charset = utf-8\"></head><body>Max Density ( &#961;<sub>Max</sub> ) : </body></html>", 0, QApplication::UnicodeUTF8));
        AverageDensityLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Average Density ( \317\201<span style=\" vertical-align:sub;\">Avg</span> ) : </p></body></html>", 0, QApplication::UnicodeUTF8));
        EnlargeGraphButton->setText(QApplication::translate("DataVisualizerGUIClass", "+", 0, QApplication::UnicodeUTF8));
        ShrinkGraphButton->setText(QApplication::translate("DataVisualizerGUIClass", "-", 0, QApplication::UnicodeUTF8));
        CurrentSnapshotLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Current Data Set : ", 0, QApplication::UnicodeUTF8));
        CurrentSnapshotLineEdit->setText(QString());
        StartButton->setText(QApplication::translate("DataVisualizerGUIClass", "Start", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(GraphsTab), QApplication::translate("DataVisualizerGUIClass", "Graphs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ViewModeLabel->setToolTip(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>Changes the Detail of Text Shown:</p><p><br/></p><p>Simple View - example : &quot; T&lt;sub&gt;Max&lt;/sub&gt;&quot;</p><p><br/></p><p>Complex View - example : &quot;Max Temperature ( T&lt;sub&gt;Max&lt;/sub&gt; )&quot;</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ViewModeLabel->setText(QApplication::translate("DataVisualizerGUIClass", "View Mode : ", 0, QApplication::UnicodeUTF8));
        RefreshIntervalMSLabel->setText(QApplication::translate("DataVisualizerGUIClass", "100 Milliseconds", 0, QApplication::UnicodeUTF8));
        ViewModeComboBox->clear();
        ViewModeComboBox->insertItems(0, QStringList()
         << QApplication::translate("DataVisualizerGUIClass", "Complex View", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataVisualizerGUIClass", "Simple View", 0, QApplication::UnicodeUTF8)
        );
        RefreshIntervalLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Refresh Interval : ", 0, QApplication::UnicodeUTF8));
        SimulationDirectoryLabel->setText(QApplication::translate("DataVisualizerGUIClass", "Simulation Directory", 0, QApplication::UnicodeUTF8));
        SimulationDirectoryDescLabel->setText(QApplication::translate("DataVisualizerGUIClass", "<html><head/><body><p>You can change the simulation directory here.</p><p>The data read from the directory will be loaded immediately.</p></body></html>", 0, QApplication::UnicodeUTF8));
        BrowseDirectoryButton->setText(QApplication::translate("DataVisualizerGUIClass", "Browse...", 0, QApplication::UnicodeUTF8));
        DirLoadButton->setText(QApplication::translate("DataVisualizerGUIClass", "Load", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(PreferencesTab), QApplication::translate("DataVisualizerGUIClass", "Preferences", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DataVisualizerGUIClass: public Ui_DataVisualizerGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAVISUALIZERGUI_H
