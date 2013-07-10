// guitest.cpp - GUI Test class implementation.
// Written by Jesse Z. Zhong
#include "stdafx.h"
#include "guitest.h"

using namespace Ui;

// Initialize test widgets.
void GUITest::InitWidgets() {

	this->ColorLineEdit(this->UI_.LE0, QColor(21, 86, 140)); // Blue
	this->ColorLineEdit(this->UI_.LE1, QColor(19, 134, 96)); // Blue-Green
	this->ColorLineEdit(this->UI_.LE2, QColor(37, 181, 59)); // Green
	this->ColorLineEdit(this->UI_.LE3, QColor(58, 200, 26)); // Light Green
	this->ColorLineEdit(this->UI_.LE4, QColor(87, 186,  8)); // Green-Yellow
	this->ColorLineEdit(this->UI_.LE5, QColor(116, 142, 4)); // Dark Yellow
	this->ColorLineEdit(this->UI_.LE6, QColor(145, 85, 18)); // Dark Orange
	this->ColorLineEdit(this->UI_.LE7, QColor(169, 33, 42)); // Dark Red
	this->ColorLineEdit(this->UI_.LE8, QColor(189, 11, 81)); // Magenta

	// Connect the color change slot to the button.
	connect(this->UI_.PushMeh, SIGNAL(clicked()), this, SLOT(ChangeButtonColor()));
}

// Changes the background color of a line edit.
void GUITest::ColorLineEdit(QLineEdit* lineEdit, const QColor& color) {
	QPalette palette = lineEdit->palette();
	palette.setColor(QPalette::Base, color);
	lineEdit->setPalette(palette);
}

// Changes the color of the button.
void GUITest::ChangeButtonColor() {
	QPalette palette = this->UI_.PushMehBox->palette();
	palette.setColor(QPalette::Base, this->ColorPicker_.Draw(ColorPicker::Random));
	this->UI_.PushMehBox->setPalette(palette);
}