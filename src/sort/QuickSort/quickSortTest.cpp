//测试快速排序
//2016-04-20
//
#include <iostream>
#include <fstream>
#include "../../../include/QuickSort.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	typedef int TYPE;
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

	if(qSort<TYPE>(vt, [](TYPE x, TYPE y) ->bool
				{ return x<y?true:false; }))
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
