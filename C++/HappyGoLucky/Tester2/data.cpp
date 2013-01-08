#include "characterOBJ.h"

const int MAX_DB_LENGTH = 256;


//static vector<objInfo> objList (MAX_DB_LENGTH);
//static vector<itemData> itemdb_array(MAX_DB_LENGTH); // Storage array for item list
//static vector<destrInfo> destrType (MAX_DB_LENGTH);
//static vector<enemyInfo> enemyType (MAX_DB_LENGTH);


// Thanks to Mas for the template
//template <class T> 
//int ARRAYSIZE(T someArray[])
//{
//	return (sizeof(someArray) / sizeof(T));
//}





///***************************************************************************
//	Object & Map Info
///***************************************************************************/
//struct enemyInfo {
//	int id;			// Enemy Type ID
//	string name;
//	int maxHP;
//	int atk, atkSpd, mvSpd;
//	int def;
//	int aiType;		// Includes Flag: Ground, Air, Water, ImmobileObj / For destructs, special AI drops item
//	enemyInfo() {}
//	enemyInfo (int i_id, string i_name, int i_maxHP, int i_atk, int i_atkSpd, int i_mvSpd, int i_def, int i_ai) {
//		id = i_id;		name = i_name;		maxHP = i_maxHP;		atk = i_atk;		atkSpd = i_atkSpd;
//		mvSpd = i_mvSpd;	def	= i_def;	aiType = i_ai;
//	}
//	~enemyInfo(){}
//};
//
//struct destrInfo {	// Destructible Obj (ex Crates and Pots) 
//	int id;
//	int def;
//	int maxHP;
//	destrInfo(int i_id, int i_def, int i_maxHP) {
//		id = i_id;		def = i_def;		maxHP = i_maxHP;
//	}
//	destrInfo(){}
//	~destrInfo(){}
//};
//
//struct objInfo {
//	int id;			// Id obj in map
//	string name;
//	int x, y;
//	int HP, maxHP;
//	int atk, atkSpd, mvSpd;
//	int def;
//	int aiType;
//	int typeID;		// Type of Obj; monster types, item types, obstacles
//	objInfo(int i_id, int i_x, int i_y, int i_typeID) {
//		id = i_id;		x = i_x;	y = i_y;	typeID = i_typeID;
//		if (typeID < 10) {
//			maxHP, HP = destrType[typeID].maxHP;
//			def = destrType[typeID].def;
//			// Put AI here
//			atk, atkSpd, mvSpd = 0;
//		}
//		if (typeID >= 10) {
//			maxHP, HP = enemyType[typeID].maxHP;
//			name = enemyType[typeID].name;
//			atk = enemyType[typeID].atk;
//			atkSpd = enemyType[typeID].atkSpd;
//			mvSpd = enemyType[typeID].mvSpd;
//			def = enemyType[typeID].def;
//		} else {
//			maxHP, HP, name, atk, atkSpd, mvSpd, def = 0;
//		}
//	}
//	objInfo(){}
//	~objInfo(){}
//private:
//	void aiControl();
//} objInfoSet;
//
//
//
///******************************************************************************************
// Parsers 
//	By Jesse (Takuto)
//	parsers (definition) - crazy migraine inducers, just saying...
//
//*******************************************************************************************/
//
//// struct itemData;
//struct itemData {		// Item_data
//	int id;
//	string name;
//	int atk, def, cost;
//	itemData() {}
//	itemData(int i_id, string i_name, int i_atk, int i_def, int i_cost) {
//		id = i_id;	name = i_name;	atk = i_atk;	def = i_def;	cost = i_cost;
//	}
//	~itemData() {}
//} itemDataSet;

//
///******************************************************************************
//	The Epic Parsers
///******************************************************************************/
//
//
///*	Item Database Parser / My proud Achievement Haha
///*********************************************/
//	void textReaderItemDB(char* fileName) {
///*********************************************/
//	ifstream myfile(fileName);
//	string stringLine;
//	string line[MAX_DB_LENGTH];
//	string slot[5];
//	if(myfile.is_open() && getline(myfile,stringLine, '\0')) {
//		getline(myfile,stringLine, '\0');
//		istringstream iss(stringLine);
//		for(int i = 0; i < MAX_DB_LENGTH ; i++) {
//			getline(iss, line[i],'\n');
//			const char* lineChar = line[i].c_str();
//			if (lineChar[1] == '[') {
//			} else {
//				istringstream lss(line[i]);
//				for(int j = 0; j < 5; j++) {
//					getline(lss, slot[j], ',');
//				}
//				for (int z = itemdb_array.size(); z < atoi(slot[0].c_str()); z++) {  // Safe Push       
//					itemdb_array.push_back(itemDataSet);
//				}
//				itemdb_array[atoi(slot[0].c_str())] = itemData(atoi(slot[0].c_str()), slot[1], atoi(slot[2].c_str()),
//					atoi(slot[3].c_str()), atoi(slot[4].c_str()));
//			}
//		}
//	}
//	myfile.close();
//}
//
//// Prints the Item Info of a specific item
//void printItem (itemData list) {
//	cout << "Item: " << list.name << endl << "ID: " << list.id << endl
//		 << "Attack: " << list.atk << endl << "Defense: " << list.def << endl
//		 << "Price: " << list.cost << "\n\n\n";
//}

/*	Controls Settings Parser
/*********************************************/
	void textReaderCtrlDB(string fileName, PlayerControls &p) {
/*********************************************/
	ifstream myfile(fileName.c_str());
	string stringLine;					// file string
	string line[MAX_DB_LENGTH];			// string array for rows
//	string slot[2];						// 2 slots for parsing

	if(getline(myfile,stringLine, '\0') == NULL) {	// file to string
		defaultControls (fileName);
		ifstream myfile(fileName);
		getline(myfile,stringLine, '\0');
	}
	istringstream iss(stringLine);

	for(int i = 0; i < MAX_DB_LENGTH; i++) {
		getline(iss,line[i],'\n');
		const char* lineChar = line[i].c_str();
		if (lineChar[0] == '[') {
		} else { 
			string ctrl;
			string symsyms;
			char brackcrack;
			string key;
			istringstream (line[i]) >> ctrl >> symsyms >> brackcrack >> key;
			getline(istringstream(key), key,']');
			// Case Statements here
			if (ctrl.c_str()) {
				if("Left" == ctrl) 		p.Left = charReturn(key.c_str());
				if("Right" == ctrl)		p.Right = charReturn(key.c_str());
				if("Jump" == ctrl)		p.Jump = charReturn(key.c_str());
				if("Duck" == ctrl)		p.Duck = charReturn(key.c_str());
				if("BackSlide" == ctrl)	p.Backslide = charReturn(key.c_str());
				if("Katar" == ctrl)		p.Katar = charReturn(key.c_str());
				if("Dagger" == ctrl)	p.Dagger = charReturn(key.c_str());
				if("Bow" == ctrl)		p.Bow = charReturn(key.c_str());
				if("Knife" == ctrl)		p.Knife = charReturn(key.c_str());
				if("Grab" == ctrl)		p.Grab = charReturn(key.c_str());
				if("Block" == ctrl)	 	p.Block = charReturn(key.c_str());
				if("Skill1" == ctrl)	p.Skill1 = charReturn(key.c_str());
				if("Skill2" == ctrl)	p.Skill2 = charReturn(key.c_str());
				if("Equipment" == ctrl)	p.Equipment = charReturn(key.c_str());
				if("Inventory" == ctrl)	p.Inventory = charReturn(key.c_str());
				if("Skills" == ctrl)	p.Skills = charReturn(key.c_str());
				if("Menu" == ctrl)		p.Menu = charReturn(key.c_str());
				if("Item1" == ctrl)		p.Item1 = charReturn(key.c_str());
				if("Item2" == ctrl)		p.Item2 = charReturn(key.c_str());
				if("Item3" == ctrl)		p.Item3 = charReturn(key.c_str());
				if("Item4" == ctrl)		p.Item4 = charReturn(key.c_str());
				if("Item5" == ctrl)		p.Item5 = charReturn(key.c_str());
				if("Item6" == ctrl)	{	p.Item6 = charReturn(key.c_str());	} else {
				}
			}
		}
	}
	myfile.close();
}

// Built in Key Values
int charReturn (const string input) {					// Assigning my own keystroke codes
	char key;
	if (input == "Space") key = 0x20;
	if (input == "Esc") key = 0x1B;
	if (input == "Tab") key = 0x09;
	if (input == "'") key = 0x27;
	if (input == "Up") key = 0x11;		// Randomly assigned; Total after thought =_="
	if (input == "Down") key = 0x12;
	if (input == "Left") key = 0x13;
	if (input == "Right") key = 0x14;
	if (input == "Backspace") { key = 0x08; } else {
		key = input[0];
	}
	switch(key) {		// ASCII Characters Recognized; Edit: Conversion to SDL keystate array
	case 'a':	case 'A':	return SDLK_a;	break;	// return 0x20;	break;
	case 'b':	case 'B':	return SDLK_b;	break;	// return 0x21;	break;
	case 'c':	case 'C':	return SDLK_c;	break;	// return 0x22;	break;
	case 'd':	case 'D':	return SDLK_d;	break;	// return 0x23;	break;
	case 'e':	case 'E':	return SDLK_e;	break;	// return 0x24;	break;
	case 'f':	case 'F':	return SDLK_f;	break;	// return 0x25;	break;
	case 'g':	case 'G':	return SDLK_g;	break;	// return 0x26;	break;
	case 'h':	case 'H':	return SDLK_h;	break;	// return 0x27;	break;
	case 'i':	case 'I':	return SDLK_i;	break;	// return 0x28;	break;
	case 'j':	case 'J':	return SDLK_j;	break;	// return 0x29;	break;
	case 'k':	case 'K':	return SDLK_k;	break;	// return 0x2A;	break;
	case 'l':	case 'L':	return SDLK_l;	break;	// return 0x2B;	break;
	case 'm':	case 'M':	return SDLK_m;	break;	// return 0x2C;	break;
	case 'n':	case 'N':	return SDLK_n;	break;	// return 0x2D;	break;
	case 'o':	case 'O':	return SDLK_o;	break;	// return 0x2E;	break;
	case 'p':	case 'P':	return SDLK_p;	break;	// return 0x2F;	break;
	case 'q':	case 'Q':	return SDLK_q;	break;	// return 0x30;	break;
	case 'r':	case 'R':	return SDLK_r;	break;	// return 0x31;	break;
	case 's':	case 'S':	return SDLK_s;	break;	// return 0x32;	break;
	case 't':	case 'T':	return SDLK_t;	break;	// return 0x33;	break;
	case 'u':	case 'U':	return SDLK_u;	break;	// return 0x34;	break;
	case 'v':	case 'V':	return SDLK_v;	break;	// return 0x35;	break;
	case 'w':	case 'W':	return SDLK_w;	break;	// return 0x36;	break;
	case 'x':	case 'X':	return SDLK_x;	break;	// return 0x37;	break;
	case 'y':	case 'Y':	return SDLK_y;	break;	// return 0x38;	break;
	case 'z':	case 'Z':	return SDLK_z;	break;	// return 0x39;	break;
	case '0':	return SDLK_0;	break;	// 	return 0x3A;	break;
	case '1':	return SDLK_1;	break;	// 	return 0x3B;	break;
	case '2':	return SDLK_2;	break;	// 	return 0x3C;	break;
	case '3':	return SDLK_3;	break;	// 	return 0x3D;	break;
	case '4':	return SDLK_4;	break;	// 	return 0x3E;	break;
	case '5':	return SDLK_5;	break;	// 	return 0x3F;	break;
	case '6':	return SDLK_6;	break;	// 	return 0x40;	break;
	case '7':	return SDLK_7;	break;	// 	return 0x41;	break;
	case '8':	return SDLK_8;	break;	// 	return 0x42;	break;
	case '9':	return SDLK_9;	break;	// 	return 0x43;	break;
	case 0x20:	return SDLK_SPACE;	break;	// 	return 0x44;	break;	// Spacebar
	case 0x1B:	return SDLK_ESCAPE;	break;	// 	return 0x45;	break;	// Esc
	case 0x09:	return SDLK_TAB;	break;	// 	return 0x46;	break;	// Tab
	case '[':	return SDLK_LEFTBRACKET;	break;	// 	return 0x47;	break;
	case ']':	return SDLK_RIGHTBRACKET;	break;	// 	return 0x48;	break;
	case ';':	return SDLK_SEMICOLON;	break;	// 	return 0x49;	break;
	case 0x27:	return SDLK_QUOTE;	break;	// 	return 0x4A;	break;	// Single Quote
	case ',':	return SDLK_COMMA;	break;	// 	return 0x4B;	break;
	case '.':	return SDLK_PERIOD;	break;	// 	return 0x4C;	break;
	case '/':	return SDLK_SLASH;	break;	// 	return 0x4D;	break;
	case 0x5C:	return SDLK_BACKSLASH;	break;	// 	return 0x4E;	break;	// Backslash
	case '`':	return SDLK_BACKQUOTE;	break;	// 	return 0x4F;	break; This might be wrong...
	case 0x08:	return SDLK_BACKSPACE;	break;	// 	return 0x50;	break;	// Backspace
	case 0x11:	return SDLK_UP;	break;
	case 0x12:	return SDLK_DOWN;	break;
	case 0x13:	return SDLK_LEFT;	break;
	case 0x14:	return SDLK_RIGHT;	break;
	default:
		return (NULL);
	}
}

// Default Printable Controls
void defaultControls (string file) {
	ofstream myfile(file.c_str());
	char ctrlDefault[1024] = 
		"[Controls]\n\n"
		"[Movement]\n"
		"Left	= [s]\n"			//0
		"Right	= [f]\n"			//1
		"Jump	= [e]\n"			//2
		"Duck	= [d]\n"			//3
		"BackSlide	= [a]\n\n"		//4
		"[Attacks]\n"				
		"Katar	= [j]\n"			//5
		"Dagger	= [i]\n"			//6
		"Bow	= [u]\n"			//7
		"Knife	= [h]\n"			//8
		"Grab	= [o]\n"			//9
		"Block	= [;]\n\n"			//10
		"[Skills]\n"
		"Skill1	= [Space]\n"		//11
		"Skill2 = [k]\n\n"			//12
		"[UI]\n"
		"Equipment	= [1]\n"		//13
		"Inventory	= [2]\n"		//14
		"Skills		= [3]\n"		//15
		"Menu		= [4]\n\n"		//16
		"[Items]\n"
		"Item1	= [7]\n"			//17
		"Item2	= [8]\n"			//18
		"Item3	= [9]\n"			//19
		"Item4	= [0]\n"			//20
		"Item5	= [-]\n"			//21
		"Item6	= [=]\0";				//22

	myfile.write(ctrlDefault, sizeof(ctrlDefault));
	myfile.close();
}


///*	Object List Parser
///********************************************************************/
//	void textReaderOBJ(char* fileName) {
///********************************************************************/
//	ifstream myfile(fileName);
//	string stringLine;
//	string line[MAX_DB_LENGTH];
//	string slot[3];
//	getline(myfile, stringLine, '\0');
//	istringstream iss(stringLine);
//	if(myfile.is_open() && getline(myfile,stringLine, '\0')) {
//		for(int i = 0; i < MAX_DB_LENGTH ; i++) {
//			getline(iss, line[i],'\n');
//			const char* lineChar = line[i].c_str();
//			if (lineChar[1] == '[') {
//			} else {
//				istringstream lss(line[i]);
//				for(int j = 0; j < 3; j++) {
//					getline(lss, slot[j], ',');
//				}
//				for (int z = objList.size(); z < atoi(slot[0].c_str()); z++) {        
//					objList.push_back(objInfoSet);
//				}
//				objList[i] = objInfo(i, atoi(slot[0].c_str()), atoi(slot[1].c_str()), atoi(slot[2].c_str()));
//			}
//		}
//	}
//	myfile.close();
//}

/*	Player Save List Parser
/************************************************************************/
	void textReaderSaveList(string fileName, vector<PlayerInfo> &p) {
/************************************************************************/
	ifstream myfile(fileName.c_str());
	string stringLine;
	string line[MAX_DB_LENGTH];
	string slot[13];
	PlayerInfo temp;

	if(getline(myfile,stringLine, '\0') == NULL) {	// file to string
		newSaveFile(fileName);
		ifstream myfile(fileName);
		getline(myfile,stringLine, '\0');
	}

	getline(myfile,stringLine, '\0');
	istringstream iss(stringLine);

	for(int i = 0; i < MAX_DB_LENGTH; i++) {
		getline(iss,line[i],'\n');
		const char* lineChar = line[i].c_str();
		if (lineChar[1] == '[') {
		} else {
			istringstream lss(line[i]);
			for(int j = 0; j < 13; j++) {
				getline(lss, slot[j], ',');
			}
			temp.init(atoi(slot[0].c_str()), slot[1], atoi(slot[2].c_str()), atoi(slot[3].c_str()), 
				atoi(slot[4].c_str()), atoi(slot[5].c_str()), atoi(slot[6].c_str()), atoi(slot[7].c_str()), 
				atoi(slot[8].c_str()), atoi(slot[9].c_str()), atoi(slot[10].c_str()), atoi(slot[11].c_str()), 
				atoi(slot[12].c_str()));
			p.push_back(temp);
		}
	}
	myfile.close();
}

// Makes Default Save File
void newSaveFile(string fileName) {
	ofstream myfile(fileName.c_str());
	char newSave[1024] = 
		"0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n";
	myfile.write(newSave, sizeof(newSave));
	myfile.close();
}