/// ParseSnapshot.h - Parse Snapshot File Class Method Implementations
/// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "Utilities.h"
#include "DataSnapshot.h"
#pragma endregion
#pragma region Symbol Names
const char* SS_SnapshotID = "snap_shot";
const char* SS_SimTime = "t";
const char* SS_Radius = "r";
const char* SS_Bins = "bins";
const char* SD_Radius = "r";
const char* SD_Particles = "n";
const char* SD_Density = "density";
const char* SD_Temperature = "temperature";
const char* SD_Velocity = "velocity";
const char* SD_Ionization = "ionization";
const char* SD_Percentage = "percentage";
#pragma endregion
// Parse the File
void DataSnapshot::Read(const string& fileName) {
	try {
		// Check if the file exists and load it.
		FILE* filePtr = fopen(fileName.c_str(), "r");
		if(filePtr == NULL)
			return;

		// Record the file name.
		this->FileName_ = fileName;

		// Traverse the file to find the size.
		fseek(filePtr, 0, SEEK_END);
		size_t size = ftell(filePtr);
		fseek(filePtr, 0, 0);

		// Create a character buffer for storing the file.
		char* buffer = new char[size];

		// Store the file into the buffer and close the file.
		FileReadStream readStream(filePtr, buffer, size);
		

		// Create a document object to deserialize the JSON.
		Document doc;

		// Attempt to read the JSON file and store its data.
		if(doc.ParseStream<0, UTF8<>>(readStream).HasParseError()) {

			// Throw and exception if the reading fails at any point.
			std::string exceptionMessage = "Error when Parsing file " + fileName;
			throw exceptionMessage.c_str();
		}

		// Begin pulling data from the file.
		this->SnapshotID_ = doc[SS_SnapshotID].GetInt();
		this->SimulationTime_ = doc[SS_SimTime].GetDouble();
		this->BubbleRadius_ = doc[SS_Radius].GetDouble();

		// Check if the array exists.
		assert(doc[SS_Bins].IsArray());

		// Reserve space for the shells.
		this->ShellData_.clear(); int j;
		this->ShellData_.reserve(j = doc[SS_Bins].Size());

		// Declare temporary variables for calculating metadata.
		double tempSum(0), densSum(0);

		// Parse the shell data.
		Value& data = doc[SS_Bins];
		for(int i = 0; i < j; i++) {
			// Store the shell data.
			ShellData item = this->ReadShellData(data[i]);
			this->ShellData_.push_back(item);

			// Update info from each gas type of each shell.
			for(int k = 0, l = item.GasTypes; k < l; k++) {

				// Sum up the individual temperatures.
				tempSum += item.Temperature[k];

				// Test for the max temperature.
				this->MaxTemperature_ = max(this->MaxTemperature_,
					item.Temperature[k]);

				// Test for the number of gas types.
				this->GasTypes_ = min(this->GasTypes_, item.GasTypes);
			}

			// Sum up the individual density values.
			densSum += item.Density;

			// Test for the max density.
			this->MaxDensity_ = max(this->MaxDensity_, item.Density);
		}

		// Perform calculations for averages.
		if((j != 0) && (this->GasTypes_ != 0)) {
			this->AvgDensity_ = densSum / j;
			this->AvgTemperature_ = tempSum / (j * this->GasTypes_);
		}

		// Clear the buffer.
		delete[] buffer;

		// Delete the file pointer.
		fclose(filePtr);

		// Set file read status to true.
		this->DataStored_ = true;

	} catch(char* ex) {
		cout << ex << endl;
	}
}

// Reads and parses shell data.
ShellData DataSnapshot::ReadShellData(Value& item) {
	try {
		// Create an instance of shell data.
		ShellData data = ShellData();

		// Store individual values first.
		data.Radius = item[SD_Radius].GetDouble();
		data.NumberOfParticles = item[SD_Particles].GetInt();
		data.Density = item[SD_Density].GetDouble();

		// Store the arrays from the file.
		Value& temperature = item[SD_Temperature];
		data.Temperature = Util::ParseAsArray<double>(temperature);

		Value& velocity = item[SD_Velocity];
		data.Velocity = Util::ParseAsArray<double>(velocity);

		Value& ionization = item[SD_Ionization];
		data.Ionization = Util::ParseAsArray<double>(ionization);

		Value& percent = item[SD_Percentage];
		data.Percent = Util::ParseAsArray<double>(percent);

		// Store the number of types of gases.
		data.GasTypes = (int)data.Temperature.size();

		// Check for the integrity of the file by checking sizes.
		if((data.GasTypes != data.Velocity.size())
			|| (data.GasTypes != data.Ionization.size())
			|| (data.GasTypes != data.Percent.size())) {

				// Throw an exception.
				throw "Inconsistent number of gas types found.";
		}

		// Return the data.
		return data;
	} catch (char* ex) {
		cout << ex << endl;
	}
	// In the event that an exception is caught,
	// return an empty instance of ShellData.
	return ShellData();
}

#pragma region Outstream Overloads
// Overloaded out stream for shell data.
ostream& operator<<(ostream& out, ShellData& shellData) {

	out << "Radius: " << shellData.Radius << endl;
	out << "Number of Particles: " << shellData.NumberOfParticles << endl;
	out << "Density: " << shellData.Density << endl;

	out << "Temperature: { ";
	for(int i = 0; i < shellData.GasTypes; i++) {
		out << shellData.Temperature[i];
		if(i != (shellData.GasTypes - 1)) 
			out << ", ";
	}
	out << " }\n";

	out << "Velocity: { ";
	for(int i = 0; i < shellData.GasTypes; i++) {
		out << shellData.Velocity[i];
		if(i != (shellData.GasTypes - 1)) 
			out << ", ";
	}
	out << " }\n";

	out << "Ionization: { ";
	for(int i = 0; i < shellData.GasTypes; i++) {
		out << shellData.Ionization[i];
		if(i != (shellData.GasTypes - 1)) 
			out << ", ";
	}
	out << " }\n";

	out << "Percent: { ";
	for(int i = 0; i < shellData.GasTypes; i++) {
		out << shellData.Percent[i];
		if(i != (shellData.GasTypes - 1)) 
			out << ", ";
	}
	out << " }\n";

	return out;
}

// Overloaded out stream for snapshots.
ostream& operator<<(ostream& out, DataSnapshot& data) {

	out << "Snapshot " << data.GetSnapshotID() << " {" << endl;
	out << "SimTime:     " << data.GetSimulationTime() << endl;
	out << "WallRadius:  " << data.GetBubbleRadius() << endl;

	auto shellData = data.GetShellData();
	for(int i = 0, j = shellData.size(); i < j; i++)
		out << shellData[i] << endl;

	out << "MeanVelocity: " << data.GetMeanVelocity() << endl;
	out << "MedianVelo:   " << data.GetMedianVelocity() << endl;
	out << "TotalColli:   " << data.GetTotalCollisions() << endl;
	out << "TotCellCross: " << data.GetTotalCellCrossings() << endl;
	out << "TotWallColli: " << data.GetTotalWallCollisions() << endl;
	out << "TotBoundColl: " << data.GetTotalConeBoundaryCollisions() << endl;
	out << "FusionRate:   " << data.GetFusionRate() << endl;

	return out;
}
#pragma endregion