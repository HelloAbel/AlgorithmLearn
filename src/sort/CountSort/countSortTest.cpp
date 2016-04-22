//测试计数排序
//2016-04-20
//
#include <iostream>
#include <fstream>
#include "../../../include/CountSort.hpp"

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

	if(countSort<TYPE>(vt))
		cout << "Succeed!!!" << endl;

	if(argc>=3) {
		ofs.open(argv[2]);
		outData(vt, ofs);
	}
	else
		outData(vt, cout);
	ofs.close();

	return 0;
}
