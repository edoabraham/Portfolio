#include "dependencies.h"

// Interesting Functions
istringstream line_read(istringstream &line_stream) {
	string line_string;
	getline(line_stream, line_string, '\n');
	return istringstream(line_string);
}

istringstream file_read(ifstream &file_stream) {
	string file_string;
	getline(file_stream, file_string, '\0');
	return istringstream(file_string);
}

int num_read(istringstream &line_stream, const char token) {
	string line_string;
	getline(line_stream, line_string, token);
	istringstream feed(line_string);
	int num;
	feed >> num;
	return num;
}

void send_msg(string fileName, int flag, bool success, string err_msg) {
	switch (flag) {
	case 0:
		if(success) cout << "Done: File " << fileName << " has been successfully loaded.\n";
		else cout << "Error: File " << fileName << "encountered an error " << err_msg << ".\n";
		break;
	case 10:
		cout << "Error: " << err_msg << ".\n";
		break;
	default:
		cout << "Da Fuck did you want me to say?\n";
		break;
	}
}