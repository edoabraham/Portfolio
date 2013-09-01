/// main.cpp - Main Program Entry Point
/// Written by Jesse Z. Zhong

#include "stdafx.h"
#include "DataVisualizer.h"
#include <QApplication>

/// Program Loop
int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	DataVisualizer mainWindow;
	try {
        // Test if the window takes up
        // all of the screen space or not
        int desktopArea = QApplication::desktop()->width() *
                          QApplication::desktop()->height();
        int widgetArea = mainWindow.width() * mainWindow.height();
        if (((float)widgetArea / (float)desktopArea) < 0.75f)
            mainWindow.show();
        else
            mainWindow.showMaximized();
	} catch (std::string exception) {
        std::cout << exception;
	}
	return application.exec();
}