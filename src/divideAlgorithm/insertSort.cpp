//插入排序
#include <iostream>
#include <type_traits>
#include <vector>
#include <utility>
#include <functional>
#include <fstream>

using namespace std;

template<typename T, typename _compare = function<bool(T, T)>>
bool insertSort(vector<T> &A, unsigned high, 
		_compare comp = [](T x, T y) -> bool { return x<y?true:false; })
{
	decltype(A.begin()) ins;
	decltype(A.begin()) del;
	int i;									//循环变量

	if(high==0){
		return true;
	}

	if(insertSort(A, high-1, comp)){
		for(i=high-1; i>=0 && !comp(A[i],A[high]); --i){
		}
		ins = A.begin()+i+1;
		A.insert(ins, A[high]);
		del = A.begin()+high+1;
		A.erase(del);
	}

	return true;
}

int main(int argc, char *argv[])
{
	typedef int TYPE;
	vector<TYPE> vt;
	ifstream ifs(argv[1], ifstream::in);
	TYPE ele;

	while(ifs>>ele)
		vt.push_back(ele);

	cout << "Init size: " << vt.size() << endl;
	for(const auto &em : vt)
		cout << em << "\t";
	cout << endl;
	cout << "===============================" << endl;
	if(insertSort<TYPE, function<bool(TYPE, TYPE)>>(vt, vt.size()-1, 
				[](TYPE x, TYPE y) -> bool { return x>y?true:false; })){
		for(const auto &em : vt)
			cout << em << "\t";
	}
	cout << endl;
	cout << "===============================" << endl;
	if(insertSort<TYPE>(vt, vt.size()-1)){
		for(const auto &em : vt)
			cout << em << "\t";
	}
	cout << endl;

	ifs.close();
}
