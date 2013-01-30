/// stdafx.h - Precompiled Header
/// Written By Jesse Z. Zhong
/// NOTE: Include only Stable Headers that
///		  will be Used Throughout the Project
///		  and will not be Edited

#pragma once

// Qt
#include <QtGui>
#include <QDebug>

// C++
#include <map>
#include <queue>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <numeric>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>

// JSON Parser
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/rapidjson.h"
#include "thirdparty/jsoncpp/include/json/value.h"

// Project Specific
// QCustomPlot is 3rd-Party and Relatively Stable
// Do Not Make Any Unnecessary Changes
#include "qcustomplot.h"

// Gamma and Log Gamma Functions
#include "Gamma/Gamma.h"

// Un-define Max
#undef max