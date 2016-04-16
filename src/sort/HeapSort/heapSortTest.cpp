#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <type_traits>
#include "../../include/heapSort.hpp"
#include "../../include/common.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	typedef float TYPE;
	vector<TYPE> vt;
	TYPE ele;
	HeapSort<TYPE> hs;
	ifstream ifs;
	ofstream ofs;

	if(argc>=2) {
		ifs.open(argv[1]);
		inData(vt, ifs);
	}
	else 
		inData(vt, cin);
	ifs.close();

	auto rv = hs.hSort(vt);
	if(argc>=3) {
		ofs.open(argv[2]);
		outData(rv, ofs);
	}
	else
		outData(rv, cout);
	ofs.close();

	return 0;	
}
