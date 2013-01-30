/// PrecompiledHeaders.h - Precompiled Headers to Ease Compile Times
/// Written by Jesse Z. Zhong

#ifndef __PRECOMPILED_HEADERS_H__
#define __PRECOMPILED_HEADERS_H__

// Build With Debug Features
//#define DEBUG_MODE

// Qt Libraries
#include <QtGui/QMainWindow>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QScrollBar>

// C++ Libraries
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <time.h>

// JSON Parser
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/rapidjson.h"
#include "thirdparty/jsoncpp/include/json/value.h"

#endif