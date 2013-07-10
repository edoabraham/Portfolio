// stdafx.h - Precompiled Header
// Written by Jesse Z. Zhong
#ifndef __Precompiled_Header__
#define __Precompiled_Header__

// Qt
#include <QWidget>

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
#include <include/rapidjson/document.h>
#include <include/rapidjson/filereadstream.h>
#include <include/rapidjson/filewritestream.h>
#include <include/rapidjson/prettywriter.h>
#include <include/rapidjson/rapidjson.h>
#include <thirdparty/jsoncpp/include/json/value.h>

// Included for drawing plots and graphs.
#include "qcustomplot.h"

// Included for gamma and log functions.
#include "Gamma/Gamma.h"

// Undefine max
#undef max

#endif