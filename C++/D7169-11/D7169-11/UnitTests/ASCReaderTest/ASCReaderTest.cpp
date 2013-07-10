// DataASCIITest.cpp - Unit Test for DataASCII.
// Written by Jesse Z. Zhong

#include "DataASCII.h"

int main() {

	// Create a *dat.asc reader.
	DataASCII ascr = DataASCII();

	// Read and parse the file.
	//ascr.Read("06032013_s223(1).dat.asc");
	ascr.Read("06042013_Blank1.dat.asc");

	// Pause the console; wait for input.
	cin.get();

	return 0;
}