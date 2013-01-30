/// SimulationController.h - Simulation Controller Class Implementation
/// Written by Jesse Z. Zhong

#include "SimulationController.h"

// Number of Parameters
const int NUM_OF_PARAMS = 12;

// Number of Gases in Simulation
const int NUM_OF_GASES = 2;

// Default Constructor
SimulationController::SimulationController() {

	// Initialize the Simulation State to False
	IsRunning_ = false;

	// Initialize Gas Ratio Vector with Size
	GasRatios_ = std::vector<double>(NUM_OF_GASES, 0.0);

	// Initialize Gas Composition Vector with Size
	GasComposition_ = std::vector<int>(NUM_OF_GASES, 0);

	// Initialize Vector of Parameters with the Number of Available Parameters
	Parameters_ = std::vector<double>((int)LAST_PARAM, 0.0);
}

// Runs the Simulation and Returns True
// if the Simulation Began Successfully
bool SimulationController::RunSimulation() {

	// Checks if the Simulation is Already Running or Not
	// Do Nothing if it is
	if(IsRunning_);
	else {





		// Set the State to True
		IsRunning_ = true;
	}



	// Return True if Everything Started Successfully
	return true;
}

// Pauses the Simulation and Returns True
// if the Simulation Actually Paused
bool SimulationController::PauseSimulation() {

	// Check if the Simulation is Actually Running
	// If so, Perform the Pause
	if(IsRunning_) {





		// Set State to False
		IsRunning_ = false;
	}


	// Return True if Paused Successfully
	return true;
}

// Stops the Simulation Completely and Returns True
// if the Simulation was Terminated Cleanly
bool SimulationController::StopSimulation() {

	// Check if the Simulation is Actually Running
	// If so, Perform the Stop
	if(IsRunning_) {





		// Set State to False
		IsRunning_ = false;
	}

	// Return True if Stopped Successfully
	return true;
}

// Parse JSON File for Parameters
bool SimulationController::ReadJSON(std::string fileName) {

#ifdef BUILD_WITH_BOOST
	// Attempt to Read the JSON File
	boost::property_tree::json_parser::read_json(fileName, ParametersTree_);
#endif
	
	// Return True if All Goes Well
	return true;
}

// Write JSON to a File
bool SimulationController::WriteJSON(std::string fileName) {

#ifdef BUILD_WITH_BOOST
	// Attempt to Write to the File
	boost::property_tree::json_parser::write_json(fileName, ParametersTree_);
#endif

	// Return True if All Goes Well
	return true;
}

// Returns the State of the Simulation
bool SimulationController::GetRunState() const {
	return IsRunning_;
}
#ifdef BUILD_WITH_BOOST
// Return the Stored Parameters
boost::property_tree::ptree SimulationController::GetData() const {
	return ParametersTree_;
}
#endif

// Set Simulation Directory
void SimulationController::SetDirectory(std::string directoryName) {
	SimulationDirectory_ = directoryName;
}

// Get Simulation Directory
std::string SimulationController::GetDirectory() const {
	return SimulationDirectory_;
}

// Set Single Parameter Value
void SimulationController::SetParameter(ParameterList paramName, double paramValue) {

	// Check if Vector is the Correct Size
	if(!(Parameters_.size() == LAST_PARAM)) {

		// Arrange and Throw Exception
		std::string error = "Exception in SimulationController::SetParameter() "\
			"std::vector<double> Parameters_ was not initialized with the correct size";
		throw error;
	}

	// Check Range in Case and Set the Value into Paramters_
	if(((int)paramName >= 0) && ((int)paramName < (int)LAST_PARAM))
		Parameters_[(int)paramName] = paramValue;

}

// Set Gas Ratio for Selected Members
void SimulationController::SetGasRatio(int index, double amount) {

	// Check if the Bounds Accessed by index are Valid
	if(CheckBounds(index, "SetGasRatio()")) {

		// Set New Value in Gas Ratio Vector
		GasRatios_[index] = amount;

		//// Check if the Total of Ratios is Equal to 1
		//double sum = 0;
		//for(int i = 0; i < NUM_OF_GASES; i++)
		//	sum += GasRatios_[i];

		//if(!(sum == 1.0)) {

		//	// Convert Double to String Stream
		//	std::stringstream s;
		//	s << sum;

		//	// Arrange and Throw and Exception
		//	std::string error = "Exception in SimulationController::SetGasRatio Gas ratios do not total 1: " + s.str();
		//	throw error;
		//}
	}
}

// Update Gas Compositions
void SimulationController::SetGasComp(int index, int comp) {

	// Check if the Bounds Accessed by index are Valid
	if(CheckBounds(index, "SetGasComp()")) {

		// Set New Value for Gas Composition Vector
		GasComposition_[index] = comp;
	}
}

// Check if Accessed Index is Within Bounds
bool SimulationController::CheckBounds(int index, std::string source) const {

	// Check if the Gas Vectors are of the Correct Size and if index is Within Range
	if(!((NUM_OF_GASES == (int)GasComposition_.size()) && (NUM_OF_GASES == (int)GasRatios_.size()))
		|| (index < 0) && (index >= NUM_OF_GASES)) {

		// Convert Number to String Stream
		std::stringstream s;
		s << NUM_OF_GASES;

		// Arrange Message and Throw It
		std::string error = "Exception in SimulationController::" + source + " has exceed the range of"\
							" 0 and " + s.str();
		throw error;

		// Return False
		return false;
	}

	// Otherwise Return True for Passing Bounds Check
	return true;
}