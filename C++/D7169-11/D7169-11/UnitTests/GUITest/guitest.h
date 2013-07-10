// guitest.h - GUI Test class declaration.
// Written by Jesse Z. Zhong
#ifndef GUITEST_H
#define GUITEST_H
#include <QMainWindow>
#include "ui_guitest.h"
#include "ColorPicker.h"

class GUITest : public QMainWindow {
	Q_OBJECT
public:
#pragma region Instance
	GUITest(QWidget *parent = 0) {
		this->UI_.setupUi(this);
		this->InitWidgets();
		this->ColorPicker_ = ColorPicker();
	}
	~GUITest() {

	}
#pragma endregion
private slots:
	// Changes the color of the button.
	void ChangeButtonColor();
private:
	// Initialize test widgets.
	void InitWidgets();

	// Changes the background color of a line edit.
	void ColorLineEdit(QLineEdit* lineEdit, const QColor& color);

	// User form.
	Ui::GUITestClass UI_;

	// Color picker.
	ColorPicker ColorPicker_;
};

#endif // GUITEST_H
