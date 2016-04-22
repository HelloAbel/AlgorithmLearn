//计数排序
//2016-04-22
//
#ifndef COUNT_SORT_HPP__
#define COUNT_SORT_HPP__

#include <type_traits>
#include <vector>
#include <utility>
#include <algorithm>
#include "common.hpp"

template <typename T>
bool countSort(std::vector<T> &s)
{
	using namespace std;
	if(!CheckIntegral<T>())
		return false;
	
	vector<T> trans(s.size());
	auto maxs = max_element(s.begin(), s.end());
	vector<T> cap((*maxs)+1);
/*
	for(long i=0; i!=static_cast<long>(*maxs)-1; ++i)
		cap[i] = 0;*/
	for(int i=s.size()-1; i>=0; --i)
		cap[s[i]] += 1;
	for(long i=1; i!=static_cast<long>(*maxs+1); ++i)
		cap[i] += cap[i-1];
	for(int i=s.size()-1; i>=0; --i) {
		trans[cap[s[i]]-1] = s[i];
		cap[s[i]] -= 1;
	}
	for(int i=0; i!=s.size(); ++i)
		s[i] = trans[i];

	return true;
}

#endif
