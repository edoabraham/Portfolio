// DataManager.cpp - Data Manager Class Method Implementations
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "DataManager.h"
#include "Util.h"
#include <QDir>
#include <QProgressDialog>
#pragma endregion
#pragma region File Extensions
// File extension for snapshot files.
const QString EXT_Snapshot = ".dat";

// File extension for save point files.
const QString EXT_Save_Point = ".txt";

// File extension for collision energy files.
const QString EXT_Collide_Energy = ".csv";

// File extension for snapshot files.
const QString EXT_RPK_Data = ".dat";

// Keyword for indicating snapshot files.
const QString KEY_Snapshot = "Snapshot";

// Keyword for indicating save point files.
const QString KEY_Save_Point = "SavePoint";

// Keyword for indicating collision energy files.
const QString KEY_Collide_Energy = "CollisionEnergy";

// Keyword for indicating RPK data files.
const QString KEY_RPK_Data = "RP";

// Asterisk reference.
const QString CHR_Asterisk = "*";

// Forward slash reference.
const QString CHR_Slash = "/";
#pragma endregion
#pragma region Progress Dialog
// Sets the max size of the progress bar.
const int ProgressMaxWidth = 240;
#pragma endregion
// Stores All Available Snapshots
void DataManager::StoreData() {

	// Attempt to initialize directory access.
	QDir dir = QDir(this->DirPath_);
	if(!dir.exists()) {
		Util::Print("Path " + this->DirPath_.toStdString() 
			+ " could not be accessed or does not exist.");
		return;
	}

	// Clear the containers of previous data entries.
	this->Snapshot_.clear();
	this->Savepoint_.clear();
	this->CollideEnergy_.clear();

	// Get all the file names for each data type.
	QStringList rpkNames = dir.entryList(QStringList(KEY_RPK_Data
		+ CHR_Asterisk + EXT_RPK_Data), QDir::Files, QDir::Name);
	QStringList snapshotNames = dir.entryList(QStringList(KEY_Snapshot
		+ CHR_Asterisk + EXT_Snapshot), QDir::Files, QDir::Name);
	QStringList savePointNames = dir.entryList(QStringList(KEY_Save_Point
		+ CHR_Asterisk + EXT_Save_Point), QDir::Files, QDir::Name);
	QStringList collideEnergyNames = dir.entryList(QStringList(KEY_Collide_Energy
		+ CHR_Asterisk + EXT_Collide_Energy), QDir::Files, QDir::Name);

	// Sum up the number of files.
	int numOfFiles = rpkNames.size() + snapshotNames.size() 
		+ savePointNames.size() + collideEnergyNames.size();
	Util::Print(QString().setNum(numOfFiles).toStdString() + " file(s) found.\n"
		+ QString().setNum(rpkNames.size()).toStdString() + " RP file(s) found.\n"
		+ QString().setNum(snapshotNames.size()).toStdString() + " Snapshot file(s) found.\n"
		+ QString().setNum(savePointNames.size()).toStdString() + " Save Point file(s) found.\n"
		+ QString().setNum(collideEnergyNames.size()).toStdString() + " Collision Energy file(s) found.");

	// Create a progress dialog, with a cancel button, 
	// to inform user of the file reading progress.
	const QString LoadingFilesStr = "%1/%2 files loaded.";
	const QString StopLoadingStr = "Stop Loading";
	QProgressDialog progress(LoadingFilesStr.arg("0", QString().setNum(numOfFiles)),
		StopLoadingStr, 0, numOfFiles, this->Parent_);
	progress.setWindowModality(Qt::WindowModal);
	progress.setMaximumWidth(ProgressMaxWidth);
	progress.setValue(0);
	progress.show();

	// Reserve space for data depending on the number of files found.
	int snapshotSize, savePointSize, collideEnergySize;
	this->Snapshot_.reserve(snapshotSize = snapshotNames.size());
	this->Savepoint_.reserve(savePointSize = savePointNames.size());
	this->CollideEnergy_.reserve(collideEnergySize = collideEnergyNames.size());

	// Use this method to update the progress bar or cancel updating.
	const auto progressUpdate = [] (QProgressDialog& progress, 
		const QString& LoadingFilesStr, int maximum) -> bool {
		progress.setValue(progress.value() + 1);
		progress.setLabelText(LoadingFilesStr.arg(progress.value(), maximum));
		if(progress.wasCanceled())
			return false;
		return true;
	};

	// Append the slash to the directory path.
	QString dirPath = dir.path() + CHR_Slash;

	// Attempt to read in the first RPK file found.
	if(!rpkNames.empty()) {
		this->RPK_.Read((dirPath + rpkNames[0]).toStdString());
		progressUpdate(progress, LoadingFilesStr, numOfFiles);
	}

	// Make sure that there is at least one file for each type.
	if(snapshotNames.empty() || savePointNames.empty() || collideEnergyNames.empty()) {
		Util::Print("At least one of the file data types is missing from the directory."
			 "\nPlease ensure that you have Snapshot*.dat, SavePoint*.txt, and Collision Energy*.csv files in the directory.");
		return;
	}

	// Special case method used for converting a string to integer.
	// The method skips over all non-numerical characters until the
	// first digit is found. It proceeds to create a number out of the
	// digits until a non-numerical character is found or the end is met.
	auto strToInt = [] (const string& str)->int {

		// Define method used for checking
		// if a character is a numerical digit.
		auto isNum = [] (char c)->bool {
			return (('0' <= c) && 
				(c <= '9')) ? true : false;
		};

		// Define method used for convert 
		// a number character to an integer.
		auto charToInt = [] (char c)->int {
			return (int)(c - '0');
		};

		// Create an index and localize string length.
		int i = 0;
		int length = str.size();

		// Skip over all characters that aren't numbers.
		while((i < length) && !isNum(str[i]))
			i++;

		// Check if the index already 
		// reached the end of the string.
		if(i >= length)
			return 0;

		// Read in leftmost digit into the results.
		int result = charToInt(str[i]);

		// Iterate through the string until the 
		// length is hit or there is no more digits.
		for(i += 1; i < length; i++) {
			if(!isNum(str[i]))
				return result;

			// Bump all read in digits left and insert new digit.
			result = result * 10 + charToInt(str[i]);
		}

		// Return the final result.
		return result;
	};

	// Grab the last number values of each of the data file types.
	int snapshotLast = strToInt(snapshotNames[snapshotNames.size() - 1].toStdString().c_str());
	int savePointLast = strToInt(savePointNames[savePointNames.size() - 1].toStdString().c_str());
	int collisionEnergyLast = strToInt(collideEnergyNames[collideEnergyNames.size() - 1].toStdString().c_str());

	// Assign the last file number that will be used for when to stop reading in files.
	int lastFile = max(max(snapshotLast, savePointLast), collisionEnergyLast);

	// Create iterators for each of the file name lists.
	auto snapshotIter = snapshotNames.begin();
	auto snapshotIterLast = snapshotNames.end();
	auto savePointIter = savePointNames.begin();
	auto savePointIterLast = savePointNames.end();
	auto collisionEnergyIter = collideEnergyNames.begin();
	auto collisionEnergyIterLast = collideEnergyNames.end();

	// Create a value to record the number of sets successfully stored.
	int fileSetsStored = 0;

	// Iterate through the lists of files, attempt to read them in order.
	for(int i = 0; i <= lastFile; i++) {

		// Snapshots
		// Check if the iterator has reached its end or not
		// and compare the number ID's in the file names with i.
		if((snapshotIter != snapshotIterLast)
			&& (i == strToInt(snapshotIter->toStdString()))) {
				this->Snapshot_.push_back(DataSnapshot((dirPath + *snapshotIter).toStdString()));
				if(!progressUpdate(progress, LoadingFilesStr, numOfFiles))
					break;

				// Iterate until the number is higher than i.
				// This is to skip over copies and dupes.
				while((snapshotIter != snapshotIterLast) 
					&& (i >= strToInt(snapshotIter->toStdString())))
					snapshotIter++;
		} else
			this->Snapshot_.push_back(DataSnapshot());

		// Save Points
		// Check if the iterator has reached its end or not
		// and compare the number ID's in the file names with i.
		if((savePointIter != savePointIterLast) 
			&& (i == strToInt(savePointIter->toStdString().c_str()))) {
				this->Savepoint_.push_back(DataSavepoint((dirPath + *savePointIter).toStdString()));
				if(!progressUpdate(progress, LoadingFilesStr, numOfFiles))
					break;

				// Iterate until the number is higher than i.
				// This is to skip over copies and dupes.
				while((savePointIter != savePointIterLast)
					&& (i >= strToInt(savePointIter->toStdString().c_str())))
					savePointIter++;
		} else
			this->Savepoint_.push_back(DataSavepoint());
		
		// Collision Energy
		// Check if the iterator has reached its end or not
		// and compare the number ID's in the file names with i.
		if((collisionEnergyIter != collisionEnergyIterLast)
			&& (i == strToInt(collisionEnergyIter->toStdString().c_str()))) {
				this->CollideEnergy_.push_back(DataCollisionEnergy((dirPath + *collisionEnergyIter).toStdString()));
				if(!progressUpdate(progress, LoadingFilesStr, numOfFiles))
					break;

				// Iterate until the number is higher than i.
				// This is to skip over copies and dupes.
				while((collisionEnergyIter != collisionEnergyIterLast)
					&& (i >= strToInt(collisionEnergyIter->toStdString().c_str())))
					collisionEnergyIter++;
		} else
			this->CollideEnergy_.push_back(DataCollisionEnergy());

		// Iterate files stored.
		fileSetsStored++;
	}

	// Internalize the amount of sets stored to the data manager.
	this->MaxSets_ = fileSetsStored;
}

// Returns a single RPK data.
// Returns a blank RPK if no data is found.
DataRPK& DataManager::GetRPKData() {
	return this->RPK_;
}

// Returns snapshot data at a given index.
// Returns a blank snapshot if no data is found.
DataSnapshot& DataManager::GetSnapshotData(int index) {
    if(this->CheckBounds<DataSnapshot>(index, this->Snapshot_))
        return this->Snapshot_[index];
	else
        throw "Index accessed is out of bounds.";
}

// Returns the save point data at a given index.
// Returns a blank save point data if no data is found.
DataSavepoint& DataManager::GetSavepointData(int index) {
	if(this->CheckBounds<DataSavepoint>(index, this->Savepoint_))
		return this->Savepoint_[index];
	else
		throw "Index accessed is out of bounds.";
}

// Returns the collision energy data at a given index.
// Returns a blank collision energy data if no data is found.
DataCollisionEnergy& DataManager::GetCollisionEnergyData(int index) {
    if(this->CheckBounds<DataCollisionEnergy>(index, this->CollideEnergy_))
        return this->CollideEnergy_[index];
	else
		throw "Index accessed is out of bounds.";
}

// Returns the collision energy data at a given index.
// Returns a blank collision energy data if no data is found.
template<typename T>
bool DataManager::CheckBounds(int index, vector<T> container) const {
    if(!((index >= 0) && (index < container.size())))
        return false;
    return true;
}

// Returns the maximum number of file sets of
// snapshots, save points, or collision energy.
int DataManager::GetMaxSets() const {
	return max(max(this->Snapshot_.size(), this->Savepoint_.size()),
		this->CollideEnergy_.size());
}

// File Directory
QString DataManager::GetDirPath() const {
	return this->DirPath_;
}
void DataManager::SetDirPath(const QString& dir) {
	this->DirPath_ = dir;
}