//测试寻找第i顺序统计量
//2016-04-20
//
#include <iostream>
#include <fstream>
#include "../../../include/OrderStatistic.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	typedef long TYPE;
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

	auto result = selectOrder<TYPE>(vt, 5);
	auto testR = static_cast<int>(result);

	if(testR==-1 || testR==-2)
		exit(-1);

	if(argc>=3) {
		ofs.open(argv[2]);
//		outData(vt, ofs);
		cout << result << endl;
	}
	else
		cout << result << endl;
//		outData(vt, cout);
	ofs.close();

	return 0;
}
