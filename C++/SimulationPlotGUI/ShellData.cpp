/// ShellData.cpp - Shell Data Structure Method Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "ShellData.h"
#include "Utilities.h"

// Parses a Single Document Value for Shell Data
ShellData ShellData::Parse(Value& shellData) {

    // Declares a Temporary Instance for Storing
	ShellData temp;

    // Store Single Data
	temp.Radius = shellData["r"].GetDouble();
	temp.NumberOfParticles = shellData["n"].GetInt();
	temp.Density = shellData["density"].GetDouble();
    
    // Store Each Array into Shell Data Vectors
    // Note: References Made for Better Possible Future Management
    
    // Temperature
    Value& temperature = shellData["temperature"];
    //for(SizeType i = 0, j = temperature.Size(); i < j; i++)
    //    temp.Temperature.push_back(temperature[i].GetDouble());
    temp.Temperature = Utilities::ParseAsArray<double>(temperature);
    
    // Velocity
    Value& velocity = shellData["velocity"];
    temp.Velocity = Utilities::ParseAsArray<double>(velocity);
    
    // Ionization
    Value& ionization = shellData["ionization"];
    temp.Ionization = Utilities::ParseAsArray<double>(ionization);
    
    // Percent of Gases; Gas Ratios
    Value& percent = shellData["percentage"];
    temp.Percent = Utilities::ParseAsArray<double>(percent);
    
    // Store the Number of Gases
    temp.NumOfGases = (int)temp.Temperature.size();
    
    // Check if the Number of Gases is Consistent
    if(!((temp.NumOfGases == (int)temp.Velocity.size())
         && (temp.NumOfGases == (int)temp.Ionization.size())
         && (temp.NumOfGases == (int)temp.Percent.size()))) {
        
        // Throw Exception
        std::string exceptionMessage = "Inconsistent Number of Gases found";
        throw exceptionMessage;
    }
    
    // Return
	return temp;
}

// Out Stream Overload for Shell Data
ostream& operator<<(ostream& out, ShellData& shellData) {

	out << "Radius: " << shellData.Radius << endl;
	out << "Number of Particles: " << shellData.NumberOfParticles << endl;
	out << "Density: " << shellData.Density << endl;

	out << "Temperature: { ";
	for(int i = 0; i < shellData.NumOfGases; i++) {
		out << shellData.Temperature[i];
		if(i != (shellData.NumOfGases - 1)) 
			out << ", ";
	}
	out << " }\n";

	out << "Velocity: { ";
	for(int i = 0; i < shellData.NumOfGases; i++) {
		out << shellData.Velocity[i];
		if(i != (shellData.NumOfGases - 1)) 
			out << ", ";
	}
	out << " }\n";

	out << "Ionization: { ";
	for(int i = 0; i < shellData.NumOfGases; i++) {
		out << shellData.Ionization[i];
		if(i != (shellData.NumOfGases - 1)) 
			out << ", ";
	}
	out << " }\n";

	out << "Percent: { ";
	for(int i = 0; i < shellData.NumOfGases; i++) {
		out << shellData.Percent[i];
		if(i != (shellData.NumOfGases - 1)) 
			out << ", ";
	}
	out << " }\n";

	return out;
}