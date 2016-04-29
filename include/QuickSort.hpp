//快速排序头文件
//2016-04-20

#ifndef QUICK_SORT_HPP__
#define QUICK_SORT_HPP__

#include "common.hpp"
#include <vector>
#include <functional>
#include <utility>

template <typename T, typename _comfunc>
void quickSort(std::vector<T> &s, _comfunc _comp, int begin, int end);
template <typename T, typename __comfunc>
std::pair<int, int> partition(std::vector<T> &s, __comfunc _comp, int begin, int end);

//带初步类型检查的快排入口函数
//默认以降序排列
template <typename T, typename comfunc =
	std::function<bool(T, T)>>
bool qSort(std::vector<T> &vt, comfunc comp =
		[](T x, T y) ->bool { return x>y?true:false; })
{
	if(!CheckArithmType<T>() || vt.size()==0)
		return false;
	quickSort<T, comfunc>(vt, comp, 0, vt.size()-1);
	return true;
}

template <typename T, typename comf>
void tailRecur(std::vector<T> &s, comf cf, 
		int begin, int end)
{
	int i = begin;

	while(i<end) {
		auto pp = partition<T, comf>(s, cf, i, end);
		tailRecur(s, cf, i, pp.first-1);
		i = pp.second+1;
	}
}

template <typename T, typename _comfunc>
void quickSort(std::vector<T> &s, _comfunc _comp,
		int begin, int end)
{
	if(begin < end) {
		auto part = partition<T, _comfunc>(s, _comp, begin, end);
		quickSort(s, _comp, begin, part.first-1);
//		quickSort(s, _comp, part.second+1, end);
		//将第二个递归式改成尾递归的形式
		//减小栈深度
		tailRecur<T, _comfunc>(s, _comp, begin, end);
	}
}

//划分子程序，找到划分点
template <typename T, typename __comfunc>
auto partition(std::vector<T> &s, __comfunc __comp,
		int begin, int end) -> std::pair<int, int>
{
	using std::swap;

	T master = s[end];
	int rep = begin-1;				//严格关系时移动指针
	int eqp;						//只负责相等时候移动
	int tmp = end-1;

	//跳过相等的值
	for(; s[tmp]==s[end] && tmp>=begin; --tmp)
		;
	eqp = tmp;
	for(int i=begin; i!=(eqp+1); ++i) {
		if(__comp(s[i], master)) {
			++rep;
			std::swap(s[rep], s[i]);
		}
		else if(s[i] == master) {
			std::swap(s[eqp], s[i]);
			--eqp;
			//跳过相等的值
			for(; s[eqp]==s[end] && eqp>=i; --eqp)
				;
			--i;
		}
	}

	//此时，相等的区间在数组最后，此时分两种情况讨论
	//当相等区间长度小于中间区间长度时
	//和相等区间长度大于中间区间长度时
	//两种情况下当把相等区间移到中间时与中间区间的交换
	//动作有区别
	if((end-eqp)<(eqp-rep)) {
		for(int i=0; (eqp+i)!=end; ++i) 
			std::swap(s[i+rep+1], s[i+eqp+1]);
	}
	else {
		for(int i=0; i!=(eqp-rep); ++i) 
			std::swap(s[i+rep+1], s[i+end-eqp+rep+1]);
	}

	return std::make_pair(rep+1, end-eqp+rep);
}

#endif
