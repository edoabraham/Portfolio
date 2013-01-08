#ifndef _H_DEPENDENCIES
#define _H_DEPENDENCIES

#define _SECURE_SCL 1

// Header Dependencies
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <cassert>
#include <cmath>
#include <math.h>
#include <cstdarg>
#include <winsock.h>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

// Names and Directories
const string GAME_NAME = "Happy Go Lucky";

const string ICON_NAME = "Icon.ico";

const string GRAPHICS_DIR = "Graphics/";

const string DATA_DIR = "Data/";



// External File Listings
// Name Constants
const string NAME_CONSTANTS = "const.txt";

// Profession Titles
const string PROFESSION_NAMES = "prof_msg.txt";
const string PROFESSION_NAMES_OFFSET = "prof_msg_offset.txt";

// Skill Names
const string SKILL_NAMES = "skill_msg.txt";


/*******************************************************\
	Database Tables
\*******************************************************/

// Elements Table
const string ELEMENT_TABLE = "ele_table_db.txt";





// Interesting Functions
istringstream line_read(istringstream &line_stream);

istringstream file_read(ifstream &file_stream);

int num_read(istringstream &line_stream, const char token);

void send_msg(string fileName, int flag = 0, bool success = true, string err_msg = "");

#endif