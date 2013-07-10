// Program entry point.
// Written by Jesse Z. Zhong
#include "stdafx.h"
#include "guitest.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	GUITest w;
	w.show();
	return a.exec();
}
