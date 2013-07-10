// MainUIClassEX.cpp - MainUIClassEX Class Implementation.
// Written By Jesse Z. Zhong
#include "stdafx.h"
#include "MainUIClassEX.h"

using namespace std;
using namespace Ui;

// Initialize widgets and their settings.
void MainUIClassEX::Init(QObject* parent) {

	// Initialize the signal graph.
	this->SignalGraph = new SignalPlot(this->centralWidget);
	this->SignalGraph->InitializeGraph(QRect(0, 0, 800, 550), "", "");

	// Added the graph to the layout.
	this->MainLayout->addWidget(this->SignalGraph->GetGraph());

	// Link up and initialize the Signals action to the menu bar.
	this->SignalsAction = new QAction(menuBar);
	this->SignalsAction->setText("Signals");
	this->menuBar->addAction(this->SignalsAction);

	// Link up and initialize the Preferences action to the menu bar.
	this->PreferencesAction = new QAction(menuBar);
	this->PreferencesAction->setText("Preferences");
	this->menuBar->addAction(this->PreferencesAction);
}






