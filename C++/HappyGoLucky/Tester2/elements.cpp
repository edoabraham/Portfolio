#include "elements.h"

const string FILE_NAME = ELEMENT_TABLE;
const unsigned int NUM_ELE = 11;
const unsigned int LVL_ELE = 4;

Elemental::Elemental() {
	resize();
	store();
}

Elemental::~Elemental() {

}

void Elemental::resize() {
	for(unsigned int i = 0; i < (NUM_ELE * LVL_ELE); i++) {
		vector<double> temp;
		temp.resize(NUM_ELE);
		advantages_.push_back(temp);
	}
}

void Elemental::store() {
	ifstream myFile(FILE_NAME.c_str());
	if(!myFile.is_open()) cout << "Error Opening " << FILE_NAME << ".\n";
	if(!advantages_.empty() && !advantages_[0].empty() && (advantages_.size() == NUM_ELE * LVL_ELE)
		&& (advantages_[0].size() == NUM_ELE)) {
			if(myFile.is_open()) {
				read_in(myFile);
			} else {
				for(unsigned int i = 0; i < (NUM_ELE * LVL_ELE); i++) {
					for(unsigned int j = 0; j < (NUM_ELE); j++) {
						advantages_[i][j] = 0;
					}
				}
			}
			send_msg(FILE_NAME);
	} else {
		resize();
		send_msg("", 10, false, "Elements not sized properly");
	}
	myFile.close();
}

void Elemental::read_in(ifstream &file_stream) {
	istringstream file_line = file_read(file_stream);
	istringstream line;
	for(unsigned int i = 0; i < (NUM_ELE * LVL_ELE); i++) {
		if(!file_line.str().empty()) line = line_read(file_line);
		for(unsigned int j = 0; j < NUM_ELE; j++) {
			if(!line.str().empty()) advantages_[i][j] = (double(num_read(line, '\n'))) / 100;
			else advantages_[i][j] = 1.00;
		}
		line.str("");
	}
}

double Elemental::damage_modifier(unsigned int atk_signature, unsigned int def_signature, unsigned int level) {
	double result = 0.00;
	for(unsigned int i = 0; i < NUM_ELE; i++) {
		if(atk_signature / (int) pow(2, (double) i) >= 1) result *= effectiveness(i, def_signature, level);
	}
	return result;
}

double Elemental::effectiveness(unsigned int ele, unsigned int def_signature, unsigned int level) {
	double result = 0.00;
	int beginning(0);
	beginning = (NUM_ELE * (int) (level - 1));
	if(beginning < 0) beginning = 0;
	for(unsigned int i = (unsigned int) beginning; i < (NUM_ELE * level); i++) {
		if((def_signature / (int) pow(2, (double) i) >= 1) && (ele >= 0 && ele < NUM_ELE)) result *= advantages_[ele][i];
	}
	return result;
}