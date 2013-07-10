// ColorPicker.cpp - ColorPicker Class Implementation.
// Written By Jesse Z. Zhong
#include "stdafx.h"
#include "ColorPicker.h"

// Initialize the list of colors.
// NOTE: Add new colors here.
void ColorPicker::Init() {

	// Ordered list.
	this->OrderedColorList_.push_back(QColor(21, 86, 140)); // [0] Blue
	this->OrderedColorList_.push_back(QColor(19, 134, 96)); // [1] Blue-Green
	this->OrderedColorList_.push_back(QColor(37, 181, 59)); // [2] Green
	this->OrderedColorList_.push_back(QColor(58, 200, 26)); // [3] Light Green
	this->OrderedColorList_.push_back(QColor(87, 186,  8)); // [4] Green-Yellow
	this->OrderedColorList_.push_back(QColor(116, 142, 4)); // [5] Dark Yellow
	this->OrderedColorList_.push_back(QColor(145, 85, 18)); // [6] Dark Orange
	this->OrderedColorList_.push_back(QColor(169, 33, 42)); // [7] Dark Red
	this->OrderedColorList_.push_back(QColor(189, 11, 81)); // [8] Magenta

	// Preset list.
	this->PresetColorList_.push_back(QColor(169, 33, 42)); // [0] Dark Red
	this->PresetColorList_.push_back(QColor(21, 86, 140)); // [1] Blue
	this->PresetColorList_.push_back(QColor(37, 181, 59)); // [2] Green
	this->PresetColorList_.push_back(QColor(0, 0, 0));     // [3] Black
	this->PresetColorList_.push_back(QColor(116, 142, 4)); // [4] Dark Yellow
	this->PresetColorList_.push_back(QColor(145, 85, 18)); // [5] Dark Orange
}

// Draws a color from the list of colors.
QColor ColorPicker::Draw(EDrawType type) {

	// If the list is empty, return an empty color.
	if(this->OrderedColorList_.empty())
		return QColor();

	// Draw a color depending on type.
	QColor color;
	switch (type) {

	// Randomly draws a color from the list of colors.
	case ColorPicker::Random:
		return this->OrderedColorList_[rand() 
			% (int)this->OrderedColorList_.size()];
		break;

	// Draws a color according to a specified preset.
	case ColorPicker::Preset:
		color = this->PresetColorList_[this->PresetDrawIndex_
			% (int)this->PresetColorList_.size()];
		this->PresetDrawIndex_++;
		return color;
		break;

	// Draws a color in the order they were initially listed.
	case ColorPicker::Ordered:
	default:
		color = this->OrderedColorList_[this->OrderedDrawIndex_
			% (int)this->OrderedColorList_.size()];
		this->OrderedDrawIndex_++;
		return color;
		break;
	}
}