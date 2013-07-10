// DataFile.h - DataFile Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __DataFile_h__
#define __DataFile_h__
#pragma region Includes
#include "stdafx.h"
using namespace std;
#pragma endregion
#pragma region Delimiters
extern const char* Delimiters;
#pragma endregion
// Base class for reading and storing file data.
class DataFile {
public:
	// Constructor
	DataFile() {
		this->FileName_ = "";
		this->DataStored_ = false;
	}

	// Lists the type of data the files are.
	enum EFileType {
		RPK,
		Snapshot,
		Savepoint,
		Distribution,
		CollisionEnergy,
	};

	// Parses a file according to the
	// implementation of a derived file reader.
	virtual void Read(const string& fileName) = 0;

	// Returns the name of the file the data was read from.
	string GetFileName() const { return this->FileName_; }

	// Returns the type of data stored.
	EFileType GetType() const { return this->Type_; }

	// Returns whether or not data has been stored.
	bool GetDataStored() const { return this->DataStored_; }

protected:
	// Name of the file that the data is read from.
	string FileName_;

	// Indicates the type of data stored.
	EFileType Type_;

	// Flag indicating if data has been stored.
	bool DataStored_;
};

#endif // End: DataFile