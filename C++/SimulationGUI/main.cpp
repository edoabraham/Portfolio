/// main.cpp - Main Program Entry Point
/// Written by Jesse Z. Zhong

#include "PrecompiledHeader.h"
#include "simulationgui.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	SimulationGUI w;
	try {
		w.show();
	} catch(std::string exception) {
		qDebug() << exception.c_str();
	}
	return a.exec();
}
