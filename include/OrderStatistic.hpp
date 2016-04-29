//期望时间为线性时间地
//寻找第i顺序统计量算法头文件
//2016-04-29
//

#ifndef ORDER_STATISTIC_HPP
#define ORDER_STATISTIC_HPP

#include <functional>
#include <vector>
#include <iostream>
#include "QuickSort.hpp"

template <typename T, typename _comp>
T orderStatistic(std::vector<T> &, int, _comp, int, int);

template <typename T, typename _comp =
					std::function<bool(T, T)>>
T selectOrder(std::vector<T> &s, int order, _comp cmp =
		[](T x, T y) ->bool { return x>y?true:false; })
{
	return orderStatistic<T, _comp>(s, order, cmp, 0, s.size()-1);
}

template <typename T, typename _comp>
T orderStatistic(std::vector<T> &s, int order, _comp cmp,
		int begin , int end) 
{
	using namespace std;

	if(order<0 || order>s.size()) {
		cerr << "order invaild" << endl;
		return static_cast<T>(-1);
	}
	if(!CheckArithmType<T>())
		return static_cast<T>(-2);

	auto p = partition<T, _comp>(s, cmp, begin, end);
	if(p.first<=(order-1) && p.second>=(order-1))
		return s[p.first];
	else if(p.first>(order-1))
		return orderStatistic<T, _comp>(s, order, 
				cmp, begin, p.first-1);
	else if(p.second<(order-1))
		return orderStatistic<T, _comp>(s, order,
				cmp, p.second+1, end);
}

#endif
