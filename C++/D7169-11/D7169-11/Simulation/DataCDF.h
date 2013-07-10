// CDFReader.h - CDFReader Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __DataCDF_H__
#define __DataCDF_H__
#pragma region Includes
#include "stdafx.h"
#include "DataFile.h"
using namespace std;
using namespace netCDF;
#pragma endregion
// This class reads in *.cdf files
// and stores the data in a usable fashion.
class DataCDF : public DataFile {
public:
	// Constructor
	DataCDF() : DataFile() {
		// Assign the type for this data set.
		this->Type_ = EFileType::CDF;

		// Initialize fields.
		this->DataStored_ = false;
	}

	// Parses a *.cdf file.
	virtual void Read(const string& fileName);

	// Writes data to a *.cdf file.
	bool Write(const vector<double>& xData, const vector<double>& yData) const;

	// Makes a copy of a file using the name passed.
	void DataCDF::FileBackup(const string& backupName);
private:
	// Indicates if an original file was read in.
	bool DataStored_;
};

#endif // End: DataCDF