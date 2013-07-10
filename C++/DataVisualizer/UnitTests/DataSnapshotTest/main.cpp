// Program entry point.
// Written By Jesse Z. Zhong
#include <iostream>
#include <string>
#include "DataSnapshot.h"
#include "DataSavepoint.h"
#include "DataRPK.h"
using namespace std;

int main() {

// 	DataSnapshot ds = DataSnapshot();
// 	ds.Read("Snapshot00000001.dat");

	DataSavepoint sv = DataSavepoint();
	sv.Read("SavePoint000001.txt");

	DataRPK dr = DataRPK();
	dr.Read("RPactual.dat");
	cout << dr << endl;

	cin.get();
	return 0;
}