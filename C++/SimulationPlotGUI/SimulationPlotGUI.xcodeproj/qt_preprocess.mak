#############################################################################
# Makefile for building: SimulationPlotGUI.app/Contents/MacOS/SimulationPlotGUI
# Generated by qmake (2.01a) (Qt 4.8.3) on: Tue Nov 13 02:58:55 2012
# Project:  SimulationPlotGUI.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.8/mkspecs/macx-xcode -o SimulationPlotGUI.xcodeproj/project.pbxproj SimulationPlotGUI.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.8/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -I. -IGamma -IConstants -Iproperty_tree -IUnits -IMath -I. -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_qcustomplot.cpp ./moc_simulationplotgui.cpp ./qrc_simulationplotgui.cpp ./ui_simulationplotgui.h
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_qcustomplot.cpp moc_simulationplotgui.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_qcustomplot.cpp moc_simulationplotgui.cpp
moc_qcustomplot.cpp: qcustomplot.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ qcustomplot.h -o moc_qcustomplot.cpp

moc_simulationplotgui.cpp: ui_simulationplotgui.h \
		SimulationPlotGUI_UI.h \
		stdafx.h \
		qcustomplot.h \
		Gamma/Gamma.h \
		IonizationVsRadius.h \
		Graph.h \
		SnapshotData.h \
		ShellData.h \
		DensityVsRadius.h \
		TemperatureVsRadius.h \
		FileReader.h \
		simulationplotgui.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ simulationplotgui.h -o moc_simulationplotgui.cpp

compiler_rcc_make_all: qrc_simulationplotgui.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_simulationplotgui.cpp
qrc_simulationplotgui.cpp: simulationplotgui.qrc
	/Developer/Tools/Qt/rcc -name simulationplotgui simulationplotgui.qrc -o qrc_simulationplotgui.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_simulationplotgui.h
compiler_uic_clean:
	-$(DEL_FILE) ui_simulationplotgui.h
ui_simulationplotgui.h: simulationplotgui.ui
	/Developer/Tools/Qt/uic simulationplotgui.ui -o ui_simulationplotgui.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

