/// FileReader.h - File Reader Class Declaration
/// Written by Jesse Z. Zhong

#include "stdafx.h"

using namespace std;

/// Digit Length in File Names for Snapshots
const int DIGIT_LENGTH_SNAPSHOTS = 8;

/// Digit Length in File Names for Savepoints
const int DIGIT_LENGTH_SAVEPOINTS = 6;

/// Digit Length in File Names for Collision Energy
const int DIGIT_LENGTH_COLLISION_ENERGY = 8;

/// Keyword String for Denoting a Snapshot File
const string KEYWORD_SNAPSHOTS = "Snapshot";

/// File Extension for Snapshots
const string FILE_EXTENSION_SNAPSHOTS = ".dat";

/// Keyword String for Denoting a Savepoint File
const string KEYWORD_SAVEPOINTS = "SavePoint";

/// File Extension for Savepoints
#ifdef READ_IN_BINARY_MODE
const string FILE_EXTENSION_SAVEPOINTS = ".data";
#else
const string FILE_EXTENSION_SAVEPOINTS = ".txt";
#endif

/// Keyword String for Denoting a Collision Energy File
const string KEYWORD_COLLISION_ENERGY = "CollisionEnergy";

/// File Extension for Collision Energy
const string FILE_EXTENSION_COLLISION_ENERGY = ".csv";

/// Starting Number for Reading the First File
/// for All Files [MODIFIABLE]
const int START_VALUE = 1;

/// Max Number of Files that can be Read
/// [MODIFIABLE]
/// -1 Will Disable this Feature
const int FILE_NUMBER_CAP = -1;

class FileReader {
public:
	// Constructor
	FileReader();
    
    // Init-Constructor
    FileReader(string directory);
	
	// Checks the Number of Files
	// that are Readable in Sequence -
	// There are No Missing Files
	int FileCheck();

	// Returns the Snapshot File
	// Name of the Requested Index
	string SnapshotFileName(int index) const;
    
    // Returns the Savepoint File
    // Name of the Requiested Index
    string SavepointFileName(int index) const;
    
    // Returns the Collision Energy
    // File Name of the Requested Index
    string CollisionEnergyFileName(int index) const;

	// Returns the Max Number of Files
    int GetMaxNumOfFiles() const;
    
    // ACCESSOR
    // File Directory
    string GetDirectory() const;
    void SetDirectory(string value);

protected:
	// Creates a Snapshot File Name
	string CreateSnapshotFileName(int fileNumber) const;
    
    // Creates a Savepoint File Name
    string CreateSavepointFileName(int fileNumber) const;
    
    // Creates a Collision Energy File Name
    string CreateCollisionEnergyFileName(int fileNumber) const;

	// Number of Snapshot Files
	int NumberOfSnapshotFiles_;
    
    // Number of Savepoint Files
    int NumberOfSavepointFiles_;
    
    // Number of Collision Energy Files
    int NumberOfCollisionEnergyFiles_;
    
    // Number of Usable File Sets
    int NumberOfSets_;
    
    // Directory
    string Directory_;
};