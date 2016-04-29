//列排序头文件
//正确性由0-1排序引理证明
//见算导第8章最后一道思考题
//2016-04-30
//

#ifndef COLUMN_SORT_HPP
#define COLUMN_SORT_HPP

#include <vector>
#include <functional>
#include <boost/math/special_functions.hpp>
#include "common.hpp"
#include "QuickSort.hpp"

template <typename T, typename _comp = 
					std::function<bool(T, T)>>
bool columnSort(std::vector<T> &s, _comp cmp =
		[](T x, T y) ->bool { return x<y?true:false; })
{
	using namespace std;
	if(!CheckArithmType<T>())
		return false;

	auto size = s.size();
	if(size<16 || size%2)
		return false;

	vector<T> mid(size);
	int first;
	//求出可以用列排序的最优列数，根据列排序
	//的约束条件可知，这个数为不大于n/2的立方根
	//且可以整除n的最大整数
	auto tmpS = static_cast<long>(boost::math::powm1<long, double>
			(size/2, 1.0/3.0)) + 1;
	while((size%tmpS)!=0)
		--tmpS;
	auto optS = tmpS;
	auto optR = size/optS;				//行数
	if(optR < 2*optS*optS) {
		cerr << "raw-number must be greater than 2*col^2" << endl;
		return false;
	}
	vector<T> trail(optR/2);

	//遍历矩阵的步长
	auto step1 = static_cast<long>(optR/optS);
	auto step = step1;
	if((step1*optS)==optR)
		step = optR;
	else
		step = (step1+1)*optS;
//	auto stepR = optS;

	//第一步，首先对每一“列”进行排列，这个列不一定是完整的一列
	//当列数不是行数的因子时，在这一步的需要扩展第一列使之可以被
	//列数整除
	for(first=0; first<=(size-step); first+=step) {
		quickSort<T, _comp>(s, cmp, first, first+step-1);
	}
	quickSort<T, _comp>(s, cmp, first, size-1);

	//第二步，转置并重新使之与原矩阵形状一样，即按列优先读取
	//但按行优先写入,在这里注意，本程序默认矩阵遍历顺序为列优先
	for(int i=0; i!=size; ++i) 
		mid[i] = s[i];
	for(int i=0, m=0, j=0; j!=size; ++j, ++m) {
		if(m==optS) {
			m=0;
			++i;
		}
		s[optR*m+i] = mid[j];
	}

	//第三步，再次对列进行排序，与第一步一样
	for(int i=0; i!=size; i+=optR) {
		quickSort<T, _comp>(s, cmp, i, i+optR-1);
	}

	//第四步，做第二步的逆操作,即按行读取，按列写入
	for(int i=0, m=0, j=0; j!=size; ++j, ++m) {
		if(m==optS) {
			m=0;
			++i;
		}
		mid[j] = s[optR*m+i];
	}
	for(int i=0; i!=size; ++i) 
		s[i] = mid[i];

	//第五步，继续对每一列进行排序
	for(int i=0; i!=size; i+=optR) {
		quickSort<T, _comp>(s, cmp, i, i+optR-1);
	}

	//第六步，将矩阵最后半列元素单独提出，
	//表现效果就是全体向后移动半列
	for(int i=0; i!=trail.size(); ++i) 
		trail[i] = s[size-optR/2+i];

	//第七步，先对前面半列进行排序，
	//然后对紧随其后的每一列进行排列
	quickSort<T, _comp>(s, cmp, 0, optR/2-1);
	for(int i=optR/2; i<(size-optR/2); i+=optR) {
		quickSort<T, _comp>(s, cmp, i, i+optR-1);
	}

	//第八步，利用在第六步提出的尾半列
	//整合成一个完整的顺序矩阵
	for(int i=0; i!=trail.size(); ++i)
		s[i+size-optR/2] = trail[i];

	return true;
}

#endif
