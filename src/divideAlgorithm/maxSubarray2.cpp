//以线性时间找出最大子数组的非递归方法
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <type_traits>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

//A[1,j+1]的最大子数组要么位于A[1,j]中，要么位于A[i,j+1]中
template<typename T>
auto maxJ(vector<T> &A, T aj, unsigned j1, unsigned l1)
	-> tuple<T, unsigned, unsigned>
{
	if(is_arithmetic<T>::value == false)
	{
		cerr << "Elements must be arithmetic" << endl;
		exit(-1);
	}

//	tuple<T, unsigned, unsigned> rj;
	unsigned pos, lsp = l1, rsp = j1-1;
	T sum = 0;
	T curMax = aj;

	for(pos=0;pos!=static_cast<int>(j1+1);++pos)
	{
		sum = accumulate<decltype(A.cbegin()), T>(A.cbegin()+pos,A.cbegin()+j1+1,0);
//		cout << " from " << pos << " to " << j1 << endl;
		if(sum>curMax)
		{
//			cout << "left position to " << pos << endl;
			curMax = sum;
			lsp = pos;
			rsp = j1;
		}
	}

	return make_tuple(curMax, lsp, rsp);
}

template<typename T>
auto maxSubarray(vector<T> &A)
	-> tuple<T, unsigned, unsigned>
{
	T curMax = A[0];
	tuple<T, unsigned, unsigned> result{curMax, 0, 0};
	unsigned jp = 1;

	for(jp=1;jp!=A.size();++jp)
		result = maxJ(A, get<0>(result), jp, get<1>(result));

	return result;
}

int main(int argc, char *argv[])
{
	typedef float TYPE;
	vector<TYPE> vt;
	ifstream ifs(argv[1]);
	TYPE ele;

	while(ifs>>ele)
		vt.push_back(ele);

	auto result = maxSubarray(vt);

	cout << "The max subarray is from " << get<1>(result) << " to " << get<2>(result)
		<< "\nIt's sum is " << get<0>(result) << endl;

	return 0;
}
