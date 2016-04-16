#ifndef COMMON_HPP__
#define COMMON_HPP__

#include <iostream>
#include <vector>

template <typename T>
inline void inData(std::vector<T> &s, std::istream &is)
{
	T tmp;
	while(is >> tmp)
		s.push_back(tmp);
}

template <typename T>
inline void outData(std::vector<T> &d, std::ostream &os)
{
	for(const auto &e : d)
		os << e << "\t";
	os << std::endl;
}

#endif
