/// Configuration.h - Configuration Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "stdafx.h"
#include "ProjectSettings.h"

using namespace std;

// Default Values
const int DEFAULT_WINDOW_WIDTH = 1000;
const int DEFAULT_WINDOW_HEIGHT = 600;
const int DEFAULT_WINDOW_POSX = 0;
const int DEFAULT_WINDOW_POSY = 0;
const int DEFAULT_REFRESH_INTERVAL = 200;

// Configuration File Name
const string CONFIGURATION_FILE_NAME = "CONFIG";

// Enumurates All Program Configuration and Settings
// and Maintains a User Input and Output Save
class Configuration {
public:
    
    // Constructor
    Configuration();
    
    // Checks if Configuration File Exists or Not
    // If it Does, Begin Reading from the File
    // Else, Create a Default File and then Read
    void ReadConfig();
    
    // Save the Current Settings to the Configuration File
    void WriteConfig();
    
    // Checks if the Config File Exists for Not
    bool CheckForFile() const;
    
    // ACCESSORS
    // Window Position and Dimensions
    QRect GetGeometry() const;
    void SetGeometry(QRect value);
    void SetGeometry(int x, int y, int width, int height);
    
    // Graph Refresh Interval
    int GetRefreshInterval() const;
    void SetRefreshInterval(int value);
    
    // Files Directory
    QString GetFilesDirectory() const;
    void SetFilesDirectory(QString value);
    
    // Viewing Mode
    int GetViewMode() const;
    void SetViewMode(int value);
    
    // Returns Whether the Directory is Set or Not
    bool IsDirectorySet() const;
    
private:
    
    // Window Defined Saved Dimensions
    int WindowWidth_;
    int WindowHeight_;
    
    // User Defined Saved Position
    int WindowPositionX_;
    int WindowPositionY_;
    
    // The Refresh Rate of the
    // Graphs, Measured in Milliseconds
    int GraphRefreshInterval_;
    
    // Files Directory
    QString FilesDirectory_;
    
    // Viewing Mode
    int ViewMode_;
};



#endif
