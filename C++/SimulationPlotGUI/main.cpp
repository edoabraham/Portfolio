/// main.cpp - Main Program Entry Point
/// Written by Jesse Z. Zhong

#include "stdafx.h"
#include "simulationplotgui.h"
#include <QtGui/QApplication>

/// Program Loop
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	SimulationPlotGUI w;
	try {
		w.show();
	} catch (std::string exception) {
        std::cout << exception;
	}
	return a.exec();
}