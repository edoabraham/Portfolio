/// Configuration.cpp - Configuration Class Method Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "Configuration.h"
#include "ProjectSettings.h"

// Buffer Length
const int BUFFER_LENGTH = 512;

// Constructor
Configuration::Configuration() {
    FilesDirectory_ = "";
    WindowPositionX_ = DEFAULT_WINDOW_POSX;
    WindowPositionY_ = DEFAULT_WINDOW_POSY;
    WindowWidth_ = DEFAULT_WINDOW_WIDTH;
    WindowHeight_ = DEFAULT_WINDOW_HEIGHT;
    GraphRefreshInterval_ = DEFAULT_REFRESH_INTERVAL;
}

// Checks if the Config File Exists for Not
bool Configuration::CheckForFile() const {
    FILE* myFile;
    myFile = fopen(CONFIGURATION_FILE_NAME.c_str(), "w+");
    if(myFile == NULL) {
        fclose(myFile);
        return false;
    } else {
        fclose(myFile);
        return true;
    }
}

// Checks if Configuration File Exists or Not
// If it Does, Begin Reading from the File
// Else, Create a Default File and then Read
void Configuration::ReadConfig() {
    if(CheckForFile()) {
        FILE* myFile;
        myFile = fopen(CONFIGURATION_FILE_NAME.c_str(), "r");
        
        char buffer[BUFFER_LENGTH] = {' '};
        
        if(myFile == NULL)
            throw "Error in reading the configuration file";
        
        fread(buffer, 1, BUFFER_LENGTH, myFile);
        stringstream s(buffer);
        
        string filesDirectory;
        
        s >> WindowPositionX_
            >> WindowPositionY_
            >> WindowWidth_
            >> WindowHeight_
            >> GraphRefreshInterval_
            >> filesDirectory
            >> ViewMode_;
        
        FilesDirectory_ = QString(filesDirectory.c_str());
        
        fclose(myFile);
        
    } else {
        // Write a Default File with Defaults
        // No Need to Read Again; Defaults in Place
        WriteConfig();
    }
}

// Writes a Configuration File
void Configuration::WriteConfig() {
    FILE* myFile;
    myFile = fopen(CONFIGURATION_FILE_NAME.c_str(), "w");
    
    char buffer[BUFFER_LENGTH] = {' '};
    
    if(myFile == NULL)
        throw "Error creating configuration file";
    
    // Write All Values Here
    stringstream s;
    
    s << WindowPositionX_ << endl
        << WindowPositionY_ << endl
        << WindowWidth_ << endl
        << WindowHeight_ << endl
        << GraphRefreshInterval_ << endl
        << FilesDirectory_.toStdString() << endl
        << ViewMode_ << endl;
    
    // Write to File then Close
    strcpy(buffer, s.str().c_str());
    fwrite(buffer, 1, BUFFER_LENGTH, myFile);
    fclose(myFile);
}

// ACCESSORS
// Note: All Set Functions will Write a New
// Config File on Call to Update on Change

// Window Position and Dimensions
QRect Configuration::GetGeometry() const {
    return QRect(WindowPositionX_, WindowPositionY_, WindowWidth_, WindowHeight_);
}
void Configuration::SetGeometry(QRect value) {
    WindowPositionX_ = value.x();
    WindowPositionY_ = value.y();
    WindowWidth_ = value.width();
    WindowHeight_ = value.height();
    WriteConfig();
}

// Graph Refresh Interval
int Configuration::GetRefreshInterval() const {
    return GraphRefreshInterval_;
}
void Configuration::SetRefreshInterval(int value) {
    GraphRefreshInterval_ = value;
    WriteConfig();
}

// Files Directory
QString Configuration::GetFilesDirectory() const {
    return FilesDirectory_;
}
void Configuration::SetFilesDirectory(QString value){
    FilesDirectory_ = value;
    WriteConfig();
}

// Viewing Mode
int Configuration::GetViewMode() const {
    return ViewMode_;
}
void Configuration::SetViewMode(int value) {
    ViewMode_ = value;
    WriteConfig();
}

// Returns Whether the Directory is Set or Not
bool Configuration::IsDirectorySet() const {
    if(FilesDirectory_ == "")
        return false;
    else
        return true;
}