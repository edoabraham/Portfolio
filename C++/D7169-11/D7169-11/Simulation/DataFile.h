// DataFile.h - DataFile Interface class.
// Written By Jesse Z. Zhong
#ifndef __DataFile_H__
#define __DataFile_H__
#include "stdafx.h"
using namespace std;

// Base class for storing signal data.
class DataFile {
public:
#pragma region Instance
	// Constructor
	DataFile() {
		this->SampleID_ = "";
		this->Method_ = "";
		this->SamplingRate_ = 0.0f;
		this->TotalDataPoints_ = 0;
		this->XAxisTitle_ = "";
		this->YAxisTitle_ = "";
		this->DataPoints_ = vector<double>();
		this->FileStored_ = false;
		this->FileName_ = "";
	}

	// Lists the type of data files there are.
	enum EFileType {
		ASCII = 0,
		CDF
	};

	// Parses a file according to 
	// a derived class implementation.
	virtual void Read(const string& fileName) = 0;
#pragma endregion
#pragma region Accessors
	// Returns the file name of the data set.
	string GetFileName() const { return this->FileName_; }
	EFileType GetType() const { return this->Type_; }
	string GetSampleID() const { return this->SampleID_; }
	string GetMethod() const { return this->Method_; }
	string GetXAxisTitle() const { return this->XAxisTitle_; }
	string GetYAxisTitle() const { return this->YAxisTitle_; }
	double GetSamplingRate() const { return this->SamplingRate_; }
	vector<double>& GetDataPoints() { return this->DataPoints_; }
	unsigned int GetTotalDataPoints() const { return this->TotalDataPoints_; }
	bool GetFileStored() const { return this->FileStored_; }
#pragma endregion
protected:
	// The ID used to identify this signal.
	string SampleID_;

	// The detection method used.
	string Method_;

	// The sampling rate or interval
	// at which data was acquired.
	double SamplingRate_;

	// The units for each axis data.
	string XAxisTitle_;
	string YAxisTitle_;

	// Vector for storing data points.
	vector<double> DataPoints_;

	// Total number of data points in the file.
	unsigned int TotalDataPoints_;

	// The type of data file this is.
	EFileType Type_;

	// Indicates that a file was successfully read in.
	bool FileStored_;

	// The name of the file that was read.
	string FileName_;
};

#endif // End : __DataFile_H__
