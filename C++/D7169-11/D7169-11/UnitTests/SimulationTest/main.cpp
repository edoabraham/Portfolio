/// Program main entry point.
/// Written By Jesse Z. Zhong
#include <string>
#include <iostream>
#include <ncFile.h>
#include <ncDim.h>
#include <ncVar.h>
#include <ncAtt.h>
#include "DataCDF.h"

using namespace std;
using namespace netCDF;

int main() {
	try {	
		DataCDF file;
		file.Read("D:/06032013_s223(1)dat-TRACE 1300_GC-Channel 1.cdf");
		//file.Write();

		/*
		NcFile myFile = NcFile("D:\\Projects\\D7169-11\\D7169-11\\Win32\\Debug\\06032013_s223(1)dat-TRACE 1300_GC-Channel 1.cdf", NcFile::FileMode::read);

		// Output logistical information.
		cout << "Name: " << myFile.getName(true) << endl;
		cout << "ID: " << myFile.getId() << endl;
		cout << "Variable Count: " << myFile.getVarCount() << endl;
		cout << "Dimension Count: " << myFile.getDimCount() << endl;
		cout << "Attribute Count: " << myFile.getAttCount() << endl;
	
		// Grab the dimensions.
		cout << endl << endl << "Dimensions:" << endl;
		auto dims = myFile.getDims();
		for(auto i = dims.begin(), j = dims.end(); i != j; i++) {
			cout << (*i).first << "\t\t" << (*i).second.getSize() << endl;
		}

		// Grab the variables.
		cout << endl << endl << "Variables:" << endl;
		auto vars = myFile.getVars();
		for(auto i = vars.begin(), j = vars.end(); i != j; i++) {
			cout << (*i).first << "\t\t" << endl;
		}

		// Grab the attributes.
		cout << endl << endl << "Attributes:" << endl;
		auto att = myFile.getAtts();
		for(auto i = att.begin(), j = att.end(); i != j; i++) {
			string strVal = "";
			(*i).second.getValues(strVal);
			cout << (*i).first << "\t\t" << strVal << endl;
		}

		auto maxPts = myFile.getDim("point_number");
		double* vals = new double[maxPts.getSize()];
		auto shit = vars.find("ordinate_values");
		NcVar fuck = shit->second;
		cout << endl << endl << "Shit:" << endl;
		fuck.getVar(vals);
		for(int i = 0; i < 100; i++) {
			cout << vals[i] << endl;
		}

		// Grab the data.
		auto dat = myFile.getCoordVars();
		for(auto i = dat.begin(), j = dat.end(); i != j; i++) {
			string strVal = "";
			strVal = (*i).second.getName();
			cout << (*i).first << "\t\t" << strVal << endl;
		}

		delete[] vals;
		*/
	} catch (char* ex) {
		cout << ex << endl;
	}

	cin.get();
	return 0;
}