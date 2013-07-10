// Program main entry point.
// Instance of the main window is started here.
// Written by Jesse Z. Zhong
#include "stdafx.h"
#include "mainui.h"
#include <QApplication>

// Initializes the main program window.
int main(int argc, char *argv[]) {

	// Create an instance of a QApplication.
	QApplication application(argc, argv);

	// Instantiates the main window UI.
	MainUI window;

	// Begin displaying the UI.
	window.show();

	// Return the state that the application exited in.
	return application.exec();
}
