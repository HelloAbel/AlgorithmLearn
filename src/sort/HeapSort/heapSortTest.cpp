#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <type_traits>
#include "../../../include/heap.hpp"
#include "../../../include/common.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	typedef float TYPE;
	vector<TYPE> vt;
	TYPE ele;
//	heap<TYPE> hs;
	ifstream ifs;
	ofstream ofs;

	if(argc>=2) {
		ifs.open(argv[1]);
		inData(vt, ifs);
	}
	else 
		inData(vt, cin);
	ifs.close();

	pQueue<TYPE> pq(vt, [](TYPE x, TYPE y) ->bool
			{return x>=y?true:false; });
//	auto rv = hs.hSort(vt);
/*
	if(argc>=3) {
		ofs.open(argv[2]);
		outData(vt, ofs);
	}
	else
		outData(vt, cout);
	ofs.close();
*/
	TYPE inEle;
	int post;
	outData(vt, cout);
	cout << "It's maximum element is: " << pq.estEle(vt) << endl;
	cout << "Please input a element..." ;
	cout << flush;
	cin >> inEle;
	pq.insert(vt, inEle);
	cout << "After insert, the priority queue is " << endl;
	outData(vt, cout);
	cout << "Please input a post and it would be how:k, k must be >= [post]" << endl;
	cout << flush;
	cin >> post;
	cin >> inEle;
	pq.increaseKey(vt, post, inEle);
	cout << "After increase, the priority queue is " << endl;
	outData(vt, cout);
	pq.extractMax(vt);
	cout << "After pop_front maximum..., the priority queue is " << endl;
	outData(vt, cout);

	return 0;	
}
