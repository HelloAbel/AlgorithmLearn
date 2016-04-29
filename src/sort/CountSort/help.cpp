#include <iostream>
#include <fstream>
#include <vector>
#include "../../../include/common.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	typedef unsigned long TYPE;
	vector<TYPE> vt;
	TYPE ele;
	ifstream ifs;
	ofstream ofs;

	if(argc>=2) {
		ifs.open(argv[1]);
		inData(vt, ifs);
	}
	else 
		inData(vt, cin);
	ifs.close();
/*
	if(columnSort<TYPE>(vt))
		cout << "Succeed!!!" << endl;
*/
	if(argc>=3) {
		ofs.open(argv[2]);
		for(auto e : vt)
			ofs << e%2 << " ";
	}
	else
		outData(vt, cout);
	ofs.close();

	return 0;
}
