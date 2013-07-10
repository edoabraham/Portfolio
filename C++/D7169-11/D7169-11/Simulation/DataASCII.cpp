// DataASCII.cpp - DataASCII Class Implementation.
// Written by Jesse Z. Zhong
#include "stdafx.h"
#include "DataASCII.h"
#pragma region Reading Constants
const char endline = '\n';
const char* delim = "\t\r\n";
#pragma endregion
#pragma region Symbol Names
const int NumberOfSymbols = 13;

const string ASC_Version = "Version:";
const string ASC_Maxchannels = "Maxchannels:";
const string ASC_Sample_ID = "Sample ID:";
const string ASC_Data_File = "Data File:";
const string ASC_Method = "Method:";
const string ASC_User_Name = "User Name:";
const string ASC_Acquisition_Date_and_Time = "Acquisition Date and Time:";
const string ASC_Sampling_Rate = "Sampling Rate:";
const string ASC_Total_Data_Points = "Total Data Points:";
const string ASC_X_Axis_Title = "X Axis Title:";
const string ASC_Y_Axis_Title = "Y Axis Title:";
const string ASC_X_Axis_Multiplier = "X Axis Multiplier:";
const string ASC_Y_Axis_Multiplier = "Y Axis Multiplier:";

const string ASC_Symbols[NumberOfSymbols] = {
	ASC_Version,	
	ASC_Maxchannels,
	ASC_Sample_ID,
	ASC_Data_File,
	ASC_Method,
	ASC_User_Name,
	ASC_Acquisition_Date_and_Time,
	ASC_Sampling_Rate,
	ASC_Total_Data_Points,
	ASC_X_Axis_Title,
	ASC_Y_Axis_Title,
	ASC_X_Axis_Multiplier,
	ASC_Y_Axis_Multiplier
};
#pragma endregion
// Parses a *.dat.asc file.
void DataASCII::Read(const string& fileName) {
	try {
#pragma region Open and Store File in Buffer
		// Create file pointer for storing the file.
		this->FileStored_ = false;
		FILE* file = fopen(fileName.c_str(), "r");
		if(file == NULL) {
			// Throw a "could not open" exception.
			string ex = fileName + " could not be opened.";
			throw ex;
		}

		// Traverse file to find the size.
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, 0);

		// Create a character buffer for storing the file.
		char* buffer = new char[size];

		// Store the file into the buffer and close the file.
		fread(buffer, size, 1, file);
		fclose(file);
#pragma endregion
#pragma region Parse Symbol and Values
		// Pointer to the head of the substring.
		char* head = buffer;

		// Pointer to the tail of the substring.
		char* tail = strchr(buffer, endline);

		// Create a counter for reading the symbols.
		int counter = 0;

		// Iterate through the buffer.
		do {
			// Parse the line.
			this->ParseToSymbol(head);

			// Reposition the head and tail.
			head = tail + 1;
			tail = strchr(head, endline);

			// Iterate the counter up.
			counter++;

		} while((tail != NULL) && (counter < NumberOfSymbols));

		// Get the values for symbols.
		// Specifically, get the number of data points.
		this->StoreValues();
#pragma endregion
#pragma region Read and Store Data Points
		// Clean and reserve space for the vector.
		this->DataPoints_.clear();
		this->DataPoints_.reserve(this->TotalDataPoints_);

		// Get the first line.
		head = strtok(head, delim);

		// Set counter back to zero.
		counter = 0;

		// Continue to iterate through the buffer.
		do {
			// Parse the line to a data point.
			this->ParseToDataPoint(head);

			// Reposition the head.
			head = strtok(NULL, delim);

			// Iterate the counter up.
			counter++;

		} while((head != NULL) && (this->TotalDataPoints_ > (unsigned)counter));
#pragma endregion

		// Deletes the buffer.
		delete[] buffer;

		// Correct recently stored values.
		this->CorrectValues();

		// Change the status of storage to true;
		this->FileStored_ = true;

	} catch(const string& ex) {
		// Output exception
		cout << ex << endl;
	}
}

// Stores symbols in a map to be used later.
void DataASCII::ParseToSymbol(char* line) {

	// Create a key and value.
	string key = "";
	string val = "";

	// Find the position of the first tab.
	char* tail = strtok(line, delim);

	// Store first read substring as the key.
	key = string(line);

	// Check if the tail points to null.
	if(tail != NULL) {
		
		// Update the pointers.
		line = strtok(NULL, delim);

		// Store the new substring as the value.
		val = string(line);
	}

	// Add entry to the map.
	this->SymbolToValues_.insert(pair<string, string>(key, val));
}

// Stores all the values according to symbols.
void DataASCII::StoreValues() {

	// Iterate through list of known symbols.
	for(int i = 0; i < NumberOfSymbols; i++) {

		// Try to get a value for a matching key.
		this->StoreValue(ASC_Symbols[i], this->SymbolToValues_[ASC_Symbols[i]]);
	}
}

// Stores a value according to its paired symbol.
void DataASCII::StoreValue(const string& sym, const string& val) {

	// Store value according to 
	// their respective variables.
	if(sym == ASC_Version) {
		this->Version_ = atoi(val.c_str());

	} else if(sym == ASC_Maxchannels) {
		this->Maxchannels_ = atoi(val.c_str());

	}  else if(sym == ASC_Sample_ID) {
		this->SampleID_ = val;

	} else if(sym == ASC_Data_File) {
		this->DataFile_ = val;

	} else if(sym == ASC_Method) {
		this->Method_ = val;

	} else if(sym == ASC_User_Name) {
		this->UserName_ = val;

	} else if(sym == ASC_Acquisition_Date_and_Time) {
		this->AcquisitionDateAndTime_ = val;

	} else if(sym == ASC_Sampling_Rate) {
		this->SamplingRate_ = atof(val.c_str());

	} else if(sym == ASC_Total_Data_Points) {
		int totalPoints;
		this->TotalDataPoints_ = (0 <= (totalPoints = atoi(val.c_str()))) 
			? totalPoints : 0;

	} else if(sym == ASC_X_Axis_Title) {
		this->XAxisTitle_ = val;

	} else if(sym == ASC_Y_Axis_Title) {
		this->YAxisTitle_ = val;

	} else if(sym == ASC_X_Axis_Multiplier) {
		this->XAxisMultiplier_ = (float)atof(val.c_str());

	} else if(sym == ASC_Y_Axis_Multiplier) {
		this->YAxisMultiplier_ = (float)atof(val.c_str());
	}
}

// Stores a single data point from a string.
void DataASCII::ParseToDataPoint(char* line) {
	
	// Attempt to convert and store data points.
	this->DataPoints_.push_back(atof(line) * this->YAxisMultiplier_);
}

// Corrects the certain values after everything has been read.
void DataASCII::CorrectValues() {

	// Correct the sampling rate.
	this->SamplingRate_ = (1 / this->SamplingRate_) 
		* this->XAxisMultiplier_;
}