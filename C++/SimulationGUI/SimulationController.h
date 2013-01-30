/// SimulationController.h - Simulation Controller Class Implementation
/// Written by Jesse Z. Zhong

#ifndef ___SIMULATION_CONTROLLER__
#define ___SIMULATION_CONTROLLER__

// Precompiled Header
#include "PrecompiledHeader.h"

// Parameter Structure
#include "ParameterList.h"

// Number of Parameters
extern const int NUM_OF_PARAMS;

// Number of Gases in Simulation
extern const int NUM_OF_GASES;


// Handles All of the Necessary Requirements to
// Setup and Run the Simulation through the GUI
class SimulationController {
public:
	// Default Constructor
	SimulationController();

	// Runs the Simulation and Returns True
	// if the Simulation Began Successfully
	bool RunSimulation();

	// Pauses the Simulation and Returns True
	// if the Simulation Actually Paused
	bool PauseSimulation();

	// Stops the Simulation Completely and Returns True
	// if the Simulation was Terminated Cleanly
	bool StopSimulation();

	// Returns the State of the Simulation
	bool GetRunState() const;

	// Parse JSON File for Parameters
	bool ReadJSON(std::string fileName);

	// Write JSON to a File
	bool WriteJSON(std::string fileName);

	#ifdef BUILD_WITH_BOOST
	// Return the Stored Parameters
	boost::property_tree::ptree GetData() const;
	#endif

	// Set Simulation Directory
	void SetDirectory(std::string directoryName);

	// Get Simulation Directory
	std::string GetDirectory() const;

	// Set Single Parameter Value
	void SetParameter(ParameterList paramName, double paramValue);

	// Set Gas Ratio for Selected Members
	void SetGasRatio(int index, double amount);

	// Set Gas Composition
	void SetGasComp(int index, int comp);

	#ifdef DEBUG_MODE
	// [DEBUG] Prints Parameters
	std::string PrintParams() const {
		std::stringstream s;

		s << "\nParameters\n";
		for(int i = 0, j = Parameters_.size(); i < j; i++)
			s << "[" << i << "] " << Parameters_[i] << '\n';

		return s.str();
	}
	#endif

private:
	// Check if Accessed Index is Within Bounds
	bool CheckBounds(int index, std::string source) const;

	// State of the Simulation
	bool IsRunning_;

	// Store the Simulation Directory
	std::string SimulationDirectory_;

	// List of Parameter Variables
	std::vector<double> Parameters_;

	// Store the Gas Ratios
	std::vector<double> GasRatios_;

	// Store the Gas Compositions
	std::vector<int> GasComposition_;

	#ifdef BUILD_WITH_BOOST
	// Container for Storing Parameters
	boost::property_tree::ptree ParametersTree_;
	#endif

};


#endif