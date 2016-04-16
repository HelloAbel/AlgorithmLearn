//寻找最大连续子数组
#include <iostream>
#include <vector>
#include <type_traits>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

//寻找跨越中点的最大子数组
template<typename T>
auto maxCross(vector<T> &A, unsigned low,
	unsigned mid, unsigned high) -> tuple<T, unsigned, unsigned>
{
	if(is_arithmetic<T>::value == false)
	{
		cerr << "Element's type must be arithmetic" << endl;
		exit(-1);
	}

	T leftSum = numeric_limits<T>::min(), rightSum = numeric_limits<T>::min();
	T leftTmp, rightTmp; 
	int pos1, pos2;
	unsigned lsp, rsp;						//指向跨越中点最大子数组的左右位置
	lsp = mid; rsp = mid+1;

	for(pos1=mid;pos1!=static_cast<int>(low);--pos1)
	{
		leftTmp += A[pos1];
		if(leftTmp > leftSum)
		{
			leftSum = leftTmp;
			lsp = pos1;
		}
	}
	for(pos2=mid+1;pos2!=static_cast<int>(high);++pos2)
	{
		rightTmp += A[pos2];
		if(rightTmp > rightSum)
		{
			rightSum = rightTmp;
			rsp = pos2;
		}
	}

	return make_tuple(leftSum+rightSum, lsp, rsp);
}

//利用maxCross，从左边最大、跨中最大、右边最大选取最大，递归解出最大子数组
template<typename T>
auto maxSubarray(vector<T> &A, unsigned low, unsigned high)
	-> tuple<T, unsigned, unsigned>
{
	unsigned mid;
	tuple<T, unsigned, unsigned> ls, rs, cs;
	T lsm, rsm, csm, msm;

	if(high == low)
		return make_tuple(A[low], low, high);
	else
	{
		mid = (high+low)/2;
		ls = maxSubarray(A, low, mid);
		rs = maxSubarray(A, mid+1, high);
		cs = maxCross(A, low, mid, high);

		lsm = get<0>(ls);
		rsm = get<0>(rs);
		csm = get<0>(cs);
		msm = max<T>({lsm, rsm, csm});

		if(lsm == msm)
			return ls;
		else if(csm == msm)
			return cs;
		else
			return rs;
	}
}


int main(int argc, char *argv[])
{
	typedef float TYPE;
	vector<TYPE> vt;
	ifstream ifs(argv[1], ifstream::in);
	TYPE ele;
	tuple<TYPE, unsigned, unsigned> result;

	while(ifs>>ele)
		vt.push_back(ele);
	ifs.close();

	result = maxSubarray(vt, 0, vt.size()-1);

	cout << "The max subarray is from " << get<1>(result) << " to " <<  get<2>(result)
		<< "\nIt's sum is " << get<0>(result) << endl;

	return 0;
}
