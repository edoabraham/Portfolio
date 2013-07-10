# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = DataVisualizerGUI
DESTDIR = ../Win32/Debug
QT += core opengl widgets gui printsupport
CONFIG += debug console
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
LIBS += -lkernel32 \
    -luser32 \
    -lshell32 \
    -luuid \
    -lole32 \
    -ladvapi32 \
    -lws2_32 \
    -lgdi32 \
    -lcomdlg32 \
    -loleaut32 \
    -limm32 \
    -lwinmm \
    -lwinspool \
    -lopengl32 \
    -lglu32
PRECOMPILED_HEADER = stdafx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./stdafx.h \
    ./qcustomplot.h \
    ./CollisionEnergyPlot.h \
    ./DensityVsRadius.h \
    ./Graph.h \
    ./IonizationVsRadius.h \
    ./ParticleDistributionPlot.h \
    ./TemperatureVsRadius.h \
    ./WallRadiusVsTime.h \
    ./GraphGL.h \
    ./DataVisualizerGUI.h \
    ./DataVisualizerGUIEX.h \
    ./StartupUIEX.h \
    ./Configuration.h \
    ./StringResource.h
SOURCES += ./qcustomplot.cpp \
    ./stdafx.cpp \
    ./DataVisualizerGUI.cpp \
    ./DensityVsRadius.cpp \
    ./IonizationVsRadius.cpp \
    ./TemperatureVsRadius.cpp \
    ./WallRadiusVsTime.cpp \
    ./main.cpp \
    ./Configuration.cpp
FORMS += ./DataVisualizerGUI.ui \
    ./FileLoadUI.ui \
    ./StartupUI.ui
RESOURCES += DataVisualizerUI.qrc