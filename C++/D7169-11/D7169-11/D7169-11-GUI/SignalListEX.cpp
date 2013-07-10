// SignalListEX.cpp - SignalListEX Class Implementation.
// Written By Jesse Z. Zhong
#include "stdafx.h"
#include "SignalListEX.h"
using namespace Ui;

// Initialize the forms auxiliary widgets.
void SignalListEX::Init(QObject* parent) {
	this->RemoveButton->setEnabled(false);
	this->ConfigureButton->setEnabled(false);
	this->TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->TableWidget->verticalHeader()->setVisible(false);
	this->TableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
}