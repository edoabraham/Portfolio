// CDFReader.cpp - CDFReader Class Implementation.
// Written By Jesse Z. Zhong
#include "stdafx.h"
#include "DataCDF.h"
#include <fstream>
#include <assert.h>
#pragma region Symbol Names
const string CDF_SampleID = "sample_id";
const string CDF_Method = "detection_method_name";
const string CDF_SamplingRate = "actual_sampling_interval";
const string CDF_XAxisTitle = "retention_unit";
const string CDF_YAxisTitle = "detector_unit";
const string CDF_DataPoints = "ordinate_values";
const string CDF_TotalPoints = "point_number";
#pragma endregion
// Parses a *.cdf file.
void DataCDF::Read(const string& fileName) {
	try {
		// Check if the file exists.
		FILE* filerPtr = fopen(fileName.c_str(), "r");
		if(filerPtr == NULL)
			return;
		fclose(filerPtr);

		// Attempt to open the file.
		NcFile file(fileName, NcFile::FileMode::read);
		this->FileStored_ = false;

		// Check if the file is open and valid.
		if(!file.isNull()) {

			// Set status to stored.
			this->DataStored_ = true;

			// Store the file name.
			this->FileName_ = fileName;

			// Localize the data.
			auto dimensions = file.getDims();
			auto variables = file.getVars();
			auto attributes = file.getAtts();
			auto varsLookup = variables.begin();
			auto attsLookup = attributes.begin();

			// Attempt to pull the sample ID.
			if((attsLookup = attributes.find(CDF_SampleID)) != attributes.end())
				attsLookup->second.getValues(this->SampleID_);

			// Attempt to pull the method.
			if((attsLookup = attributes.find(CDF_Method)) != attributes.end())
				attsLookup->second.getValues(this->Method_);

			// Attempt to pull the interval.
			if((varsLookup = variables.find(CDF_SamplingRate)) != variables.end())
				varsLookup->second.getVar(&(this->SamplingRate_));

			// Attempt to pull the x axis units.
			if((attsLookup = attributes.find(CDF_XAxisTitle)) != attributes.end())
				attsLookup->second.getValues(this->XAxisTitle_);

			// Attempt to pull the y axis units.
			if((attsLookup = attributes.find(CDF_YAxisTitle)) != attributes.end())
				attsLookup->second.getValues(this->YAxisTitle_);

			// Get the data points.
			this->TotalDataPoints_ = file.getDim(CDF_TotalPoints).getSize();
			if((varsLookup = variables.find(CDF_DataPoints)) != variables.end()) {
				double* dataPoints = new double[this->TotalDataPoints_];
				varsLookup->second.getVar(dataPoints);

				// Attempt to store data.
				this->DataPoints_.reserve(this->TotalDataPoints_);
				for(int i = 0, j = this->TotalDataPoints_; i < j; i++)
					this->DataPoints_.push_back(dataPoints[i]);

				// Delete the array.
				delete[] dataPoints;
			}

			// Change the status of storage to true.
			this->FileStored_ = true;
		}
	} catch(char* ex) {
		cout << ex << endl;
	}
}

// Writes data to a *.cdf file replacing the ordinate values.
bool DataCDF::Write(const vector<double>& xData, const vector<double>& yData) const {
	try {
		// Check if a file has been read in or not, prior.
		if(!this->DataStored_)
			return false;

		// Check that the sizes for both vectors match up.
		int size = 0;
		if((size = xData.size()) != yData.size())
			return false;

		// Check if the file still exists.
		FILE* filePtr = fopen(this->FileName_.c_str(), "r");
		if(filePtr == NULL)
			return false;

		// Close the file pointer.
		fclose(filePtr);

		// Attempt to create a new file.
		NcFile file(this->FileName_, NcFile::FileMode::write);

		// Search for the first positive index.
		int firstIndex = 0;
		for(; (firstIndex < size) && (xData[firstIndex] < 0); firstIndex++);
		firstIndex = (firstIndex > 0) ? firstIndex - 1 : 0;

		// Adjust the size for the new array.
		assert((size - firstIndex) >= 0);
		int arraySize = (size > 0) ? (size - firstIndex) : 0;

		// Localize the data handle.
		auto dataPts = file.getVar(CDF_DataPoints);

		// Check the size before attempting to write data.
		if(arraySize > 0) {

			// Localize the stored data points as a double array.
			double* data = new double[arraySize];
			for(int i = 0; (firstIndex < size) 
				&& (i < arraySize); i++, firstIndex++)
					data[i] = yData[firstIndex];

			// Replace the data.
			dataPts.putVar(data);
		}
	} catch(char* ex) {
		cout << ex << endl;
	}
	return true;
}

// Makes a copy of a file using the name passed.
void DataCDF::FileBackup(const string& backupName) {
	
	// Create pointers to the original file and a new file.
	FILE* inFile = fopen(this->FileName_.c_str(), "rb");
	FILE* outFile = fopen(backupName.c_str(), "wb");
	if((inFile == NULL) || (outFile == NULL))
		throw "Could not back up the file.";

	// Find the size of the original file.
	fseek(inFile, 0, SEEK_END);
	size_t size = ftell(inFile);
	fseek(inFile, 0, 0);

	// Create a buffer to store the original file.
	char* buffer = new char[size];

	// Store the file into the buffer.
	fread(buffer, size, 1, inFile);

	// Write the buffer to the new file.
	fwrite(buffer, size, 1, outFile);

	// Close both file pointers.
	fclose(inFile);
	fclose(outFile);
}