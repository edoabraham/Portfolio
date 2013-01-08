#include "game_data.h"

const int MIN_CONST_LIST_SIZE = 30;

Game_Data::Game_Data() {
	default_ = "void";
}

bool Game_Data::comment(string line) {
	if(line[0] == '/' && line[1] == '/') return true;
	else return false;
}

void Game_Data::parse_entities(const string line) {
	string read_string;
	string dump;
	bool running_on = true;
	istringstream read_stream(line);
	entity_list_.push_back(temp_);
	int index = -1;
	if(!entity_list_.empty()) index = int(entity_list_.size() - 1);
	while(!read_stream.eof() && index >= 0 && !read_stream.str().empty() && running_on) {
		if(get_line(read_string, read_stream, 10, 9) == constant(10)) parse_graphics(read_string, index);
		else if(get_line(read_string, read_stream,10, 9) == constant(11)) parse_status(read_string, index);
		else running_on = false;
	}
}

void Game_Data::parse_items(const string line) {
	string read_string;
	istringstream read_stream(line);
	while(!read_stream.eof() ) {
//		if(get_line(read_string, read_stream, return_range(20, 9)) == constant(20)) parse_graphics(read_string, val);
	}
}

void Game_Data::parse_graphics(const string line, int val) {
	string read_string;
	istringstream read_stream(line);
	bool running_on = true;
	while(!read_stream.eof() && const_str_.size() > MIN_CONST_LIST_SIZE && !read_stream.str().empty() && running_on) {
		if(get_line(read_string, read_stream, 20, 9) == constant(20)) parse_animations(read_string, val);
		else running_on = false;
	}
}

int Game_Data::str_to_int(string str) {
	int length = str.length();
	int result = 0;
	int digitsPlace = 1;
	for(int i = length - 1; i >= 0; i--) {
		if(str[i] <= '9' && str[i] >= '0') {	// Only Counts Numerical Characters; Skips Otherwise
			result = result + (str[i] - '0') * digitsPlace;
			digitsPlace = digitsPlace * 10;
		}
	}
	return result;
}

void Game_Data::parse_animations(const string line, int val) {
	string phrase;
	string read_string;
	istringstream read_stream(line);
	istringstream read_line;

	while(!read_stream.eof() && !read_stream.str().empty()) {
		getline(read_stream, read_string, '\n');
		read_line = istringstream(read_string);

		if(!read_string.empty()) {
			if(read_string.find(".png") != -1 || read_string.find(".jpg") != -1 || read_string.find(".bmp") != -1 || read_string.find(".jpeg") != -1) {
				read_line >> phrase;
				entity_list_[val].entity_.load(phrase);
			} else {
				if(read_line.str().find(":") != -1) {
					string segment_string;
					istringstream segment_stream;
					bool newLine = true;
					while(!read_line.eof()) {
						getline(read_line, segment_string, ';');
						segment_stream = istringstream(segment_string);
						string read_in;
						string temp_sum;
						while(segment_stream >> read_in) {
							temp_sum += read_in;
						}
						if(!temp_sum.empty()) {
							if(newLine) {
								entity_list_[val].entity_.push_push();
								newLine = false;
							}
							int vals[4] = { 0 };
							int val5 = 0;
							istringstream break_down(temp_sum);
							for(int l = 0; l < 3 && !break_down.eof(); l++) {
								getline(break_down, read_in, ':');
								vals[l] = atoi(read_in.c_str());
							}

							if(!break_down.eof()) {
								getline(break_down, read_in, '[');
								vals[3] = atoi(read_in.c_str());
								break_down >> read_in;
								val5 = str_to_int(read_in);
							}

							for(int i = 0; i < val5; i++) {
								if(entity_list_[val].entity_.index() != -1)
									entity_list_[val].entity_.add(entity_list_[val].entity_.index(), vals[0], vals[1], vals[2], vals[3]);
								vals[0] += vals[2];
							}
						}
					}
				} else {
					int width(0), height(0);
					if(read_line >> width >> height) {
						entity_list_[val].entity_.offset(width, height);
						cout << width << " " << height << endl;
					}
				}
			} 
		}
	}
}

void Game_Data::parse_status(const string line, int val) {
	string read_string;
	string phrase;
	int number;
	istringstream read_stream(line);
	istringstream read_line;
	while(!read_stream.eof() ) {
		getline(read_stream, read_string, '\n');
		read_line = istringstream(read_string);
		read_line >> phrase;
		if(phrase == const_str_[30]) {
			string temp;
			read_line >> temp;
			entity_list_[val].add_name(temp);
		} else {
			read_line >> number;
			if(phrase == const_str_[31]) entity_list_[val].add_element(number);
			else if(phrase == const_str_[32]) entity_list_[val].add_atk(number);
			else if(phrase == const_str_[33]) entity_list_[val].add_matk(number);
			else if(phrase == const_str_[33]) entity_list_[val].add_hp(number);
			else if(phrase == const_str_[34]) entity_list_[val].add_mp(number);
			else if(phrase == const_str_[35]) entity_list_[val].add_def(number);
			else if(phrase == const_str_[36]) entity_list_[val].add_mdef(number);
			else if(phrase == const_str_[37]) entity_list_[val].add_mspd(number);
			else if(phrase == const_str_[38]) entity_list_[val].add_aspd(number);
			else if(phrase == const_str_[39]) entity_list_[val].add_range(number);
		}
	}
}

void Game_Data::parse_file(string fileName) {
	ifstream myFile(fileName);
	string phrase;
	string file_string;
	string line;
	bool running_on = true;

	if(myFile.is_open()) {
		getline(myFile, file_string, '\0');
		istringstream file_stream(file_string);
		while(!file_stream.eof() && (const_str_.size() > MIN_CONST_LIST_SIZE) && !file_stream.str().empty() && running_on) {
			if(get_line(file_string, file_stream, 0, 9) == constant(0)) parse_entities(file_string);
//			else if(get_line(file_string, file_stream, return_range(0, 9)) == constant(1)) parse_items(file_string);
			else running_on = false;
		}
	}
}

string Game_Data::get_line(string &destination, istringstream &source, const int val, const int range) {
	bool running = true;
	string dummy;
	stringstream temp;
	int string_index = 0;
	int position = 0;
	bool pos_set = false;
	bool hasMatch = false;
	bool hasMatch2 = false;
	unsigned int i = 0;
	string source_string_line;
	getline(source, source_string_line, '\0');
	const unsigned int source_length = source_string_line.length();
	const unsigned int const_length = const_str_.size();
	const bool const_empty = const_str_.empty();
	const bool source_empty = source_string_line.empty();
	if(!const_empty && unsigned(val + range) < const_length && val >= 0) {
		for(; i < source_length && running; i++) {
			for(unsigned int l = val; !hasMatch && !const_empty && l < const_length && l <= unsigned(val + range) ; l++) {
			
				bool isRunning = true;
				for(unsigned int j = 0; !const_empty && (i + j) < source_length && j < const_str_[l].length() && !hasMatch; j++) {
					if((i + j) < source_length && !(source_string_line[i + j] == const_str_[l][j])) isRunning = false;
				}
				if(isRunning) {
					hasMatch = true;
					string_index = l;
					if((i + const_str_[string_index].length()) < source_length) i += const_str_[string_index].length();
					for(; i < source_length && source_string_line[i] != '\n' && source_string_line[i] != '\0'; i++) {
					}
					position = i;
					pos_set = true;
				}
			}
			
			if(hasMatch && pos_set) {
				for(unsigned int l = val; !hasMatch2 && !const_empty && l < const_length && l <= unsigned(val + range); l++) {
					bool isRunning2 = true;
					for(unsigned int j = 0; !const_str_[l].empty() && j < const_str_[l].length() && (i + j) < source_length && !hasMatch2; j++) {
						if((i + j) < source_length && !(source_string_line[i + j] == const_str_[l][j])) isRunning2 = false;
					}
					if(isRunning2) {
						hasMatch2 = true;
					} 
				}
			}

			if(hasMatch && hasMatch2 && !source_empty && unsigned(position) < source_length && unsigned(i) < source_length) {
				destination = source_string_line.substr(position, i - position);
				running = false;
			}
		}
	}
	if(hasMatch && !hasMatch2 && !source_empty && unsigned(position) < source_length && unsigned(i - 1) <= source_length) {
		destination = source_string_line.substr(position, i - position);
	}
	for(; !source_empty && i < source_length; i++) {
		temp.str() += source_string_line[i];

	}
	string string_line;
	getline(temp, string_line, '\0');
	source = istringstream(string_line);
	if(!const_empty) return const_str_[string_index];
	else return dummy;
}

void Game_Data::parse_data(string fileName) {
	ifstream myFile(fileName.c_str());
	string phrase;
	string file_string;
	string line;
	int la = 0;
	if(myFile.is_open()) {
		getline(myFile, file_string, '\0');
		istringstream file_stream(file_string);

		while(!file_stream.eof()) {
			// Divide File Stream by Line
			getline(file_stream, line, '\n');
			istringstream line_stream(line);

			// Parse Elements in Line
			bool finished = false;
			while(!finished && line_stream >> phrase) {
				
				// Skips Comments
				finished = comment(phrase);
				if(phrase == "DIR:") {
					line_stream >> phrase;
					finished = comment(phrase);
					if(!finished) parse_file(phrase);
				}
			}
		}
	}
	myFile.close();
}

void Game_Data::store_const(string fileName) {
	string word;
	string line;
	istringstream stream_line;
	ifstream myFile(fileName.c_str());
	if(myFile.is_open()) {
		while(!myFile.eof()) {
			getline(myFile, line, '\n');
			stream_line = istringstream(line);
			stream_line >> word;
			const_str_.push_back(word);
		}
	}
	myFile.close();
}

string Game_Data::constant(const int val) {
	if(!const_str_[val].empty()) return const_str_[val];
	else return default_ + int_to_str(val);
}

string Game_Data::int_to_str(const int val) {
	istringstream feed(val);
	string temp;
	feed >> temp;
	return temp;
}

Game_Data::~Game_Data() {
	for(unsigned int i = const_str_.size(); i > 0; i--) {
		const_str_.pop_back();
	}
}