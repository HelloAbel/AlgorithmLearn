//归并排序
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T, 
	typename _compare = function<bool(int,int)>>
bool mergeSort(vector<T> &A, unsigned low1, unsigned high1, unsigned high2,
		_compare comp = [](T x, T y) -> bool { return x<y?true:false; })
{
	vector<T> thir;
	int i,j;										//循环变量
	unsigned mid1 = (low1+high1)/2;
	unsigned mid2 = (high1+high2+1)/2;
	unsigned len1 = high1-low1+1, len2 = high2-high1;

	if((len1+len2)==1)
		return true;

	mergeSort(A, low1, mid1, high1);
	mergeSort(A, high1+1, mid2, high2);

	for(i=0,j=0;i<=(len1-1)&&j<=(len2-1);){
		if(comp(A[i+low1],A[j+high1+1])){
			thir.push_back(A[i+low1]);
			++i;
		}
		else{
			thir.push_back(A[j+high1+1]);
			++j;
		}
	}
	//下面的判断语句别用<判断，否则在基础情况也就是只有一个元素
	//的时候不好处理
	if(j>(len2-1)){
		for(;i<=(len1-1);++i)
			thir.push_back(A[i+low1]);
	}
	else if(i>(len1-1)){
		for(;j<=(len2-1);++j)
			thir.push_back(A[j+high1+1]);
	}
	for(int m=0;m<=(len1+len2-1);++m)
		A[m+low1] = thir[m];

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
	if(mergeSort<TYPE>(vt, 0, (vt.size()-1)/2, vt.size()-1)){
		for(const auto &em : vt)
			cout << em << "\t";
	}
	cout << endl;

	ifs.close();
	return 0;
}
