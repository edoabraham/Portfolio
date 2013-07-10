// DataASCII.h - DataASCII Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __DataASCII_h__
#define __DataASCII_h__
#pragma region Includes
#include "stdafx.h"
#include "DataFile.h"
using namespace std;
#pragma endregion
// This class reads in *dat.asc files
// and stores the data in a usable fashion.
class DataASCII : public DataFile {
public:
#pragma region Instance
	// Constructor
	DataASCII() : DataFile() {
		// Assign the type for this data set.
		this->Type_ = EFileType::ASCII;

		// Initialize fields.
		this->Version_ = 0;
		this->Maxchannels_ = 0;
		this->DataFile_ = "";
		this->UserName_ = "";
		this->AcquisitionDateAndTime_ = "";
		this->XAxisMultiplier_ = 0.0f;
		this->YAxisMultiplier_ = 0.0f;
		this->SymbolToValues_ = map<string, string>();
	}

	// Parses a *.dat.asc file.
	virtual void Read(const string& fileName);
#pragma endregion
#pragma region Accessors
	int GetVersion() const { return this->Version_; }
	int GetMaxchannels() const { return this->Maxchannels_; }
	string GetDataFile() const { return this->DataFile_; }
	string GetUserName() const { return this->UserName_; }
	string GetAcquisitionDataAndTime() const { return this->AcquisitionDateAndTime_; }
#pragma endregion
private:
	// Stores symbols in a map to be used later.
	void ParseToSymbol(char* line);

	// Stores all the values according to symbols.
	void StoreValues();

	// Corrects the certain values after everything has been read.
	void CorrectValues();

	// Stores a value according to its paired symbol.
	void StoreValue(const string& sym, const string& val);

	// Stores a single data point from a string.
	void ParseToDataPoint(char* line);

	// Variables for storing symbol values.
	int Version_;
	int Maxchannels_;
	string DataFile_;
	string UserName_;
	string AcquisitionDateAndTime_;
	float XAxisMultiplier_;
	float YAxisMultiplier_;

	// Map for temporarily storing symbols and values.
	map<string, string> SymbolToValues_;
};

#endif // End: DataASCII