/// RPKStruct.h - RPK Instance Structure Implementation
/// Written By Jesse Z. Zhong

#ifndef __RPK_STRUCT_H__
#define __RPK_STRUCT_H__

#include "stdafx.h"
#include "Utilities.h"

#define RPK_DELIMITERS " ,\n"

struct RPKStruct {
    
    double Time;
    double WallRadius;
    double WallVelocity;
    double Pressure;
    double PressureToTime;
    
    RPKStruct& Parse(char* line) {
        Time = atof(Utilities::TestForNull(strtok(line, RPK_DELIMITERS)));
        WallRadius = atof(Utilities::TestForNull(strtok(NULL, RPK_DELIMITERS)));
        WallVelocity = atof(Utilities::TestForNull(strtok(NULL, RPK_DELIMITERS)));
        Pressure = atof(Utilities::TestForNull(strtok(NULL, RPK_DELIMITERS)));
        PressureToTime = atof(Utilities::TestForNull(strtok(NULL, RPK_DELIMITERS)));
        return *this;
    }
};

#endif
