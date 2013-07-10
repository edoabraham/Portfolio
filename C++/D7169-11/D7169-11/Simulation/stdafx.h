// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifndef __H_STDAFX__
#define __H_STDAFX__

#include "targetver.h"

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN             

// Windows Header Files:
#include <windows.h>

// Standard C++
#include <string>
#include <vector>
#include <iostream>
#include <map>

// NetCDF
#include <ncFile.h>
#include <ncDim.h>
#include <ncVar.h>
#include <ncAtt.h>

#endif // End : __H_STDAFX__
