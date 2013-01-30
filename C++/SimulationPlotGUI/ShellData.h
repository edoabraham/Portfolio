/// ShellData.h - Shell Data Structure Declaration
/// Written By Jesse Z. Zhong

#ifndef __SHELL_DATA_H__
#define __SHELL_DATA_H__

#include "stdafx.h"

using namespace std;
using namespace rapidjson;

// Defines the Construct
// Used to Store Shell Data
struct ShellData {
    
    // Data
	double Radius;
	int NumberOfParticles;
	double Density;
	vector<double> Temperature;
	vector<double> Velocity;
	vector<double> Ionization;
	vector<double> Percent;

    // Parses a Single Document Value for Shell Data
	static ShellData Parse(Value& shellData);
    
    // Number of Found Gases
    int NumOfGases;
};

// Out Stream Operatore Overload for Shell Data
ostream& operator<<(ostream& out, ShellData& shellData);

#endif
