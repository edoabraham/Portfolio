// ColorPicker.h - ColorPicker Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __ColorPicker_h__
#define __ColorPicker_h__
#include "stdafx.h"
using namespace std;

// Allows the drawing of a
// color from a list of presets.
class ColorPicker {
public:
#pragma region Instance
	// Constructor
	ColorPicker() {
		this->OrderedColorList_ = vector<QColor>();
		this->PresetColorList_ = vector<QColor>();
		this->OrderedDrawIndex_ = 0;
		this->PresetDrawIndex_ = 0;
		this->Init();
	}

	// Destructor
	~ColorPicker() {
		// Clear the color lists.
		this->OrderedColorList_.clear();
		this->PresetColorList_.clear();
	}
#pragma endregion
	// Type of color drawing.
	enum EDrawType {
		Random = 0,
		Ordered,
		Preset
	};

	// Draws a color from the list of colors.
	QColor Draw(EDrawType type);
private:
	// Initialize the list of colors.
	void Init();

	// List of ordered colors.
	vector<QColor> OrderedColorList_;

	// List of preset colors.
	vector<QColor> PresetColorList_;

	// Index that keeps track of the next color
	// to draw with the next call of an ordered draw.
	int OrderedDrawIndex_;

	// Index that keeps track of the next color
	// to draw with the next call of a preset draw.
	int PresetDrawIndex_;
};

#endif // End: ColorPicker