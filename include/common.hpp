#ifndef COMMON_HPP__
#define COMMON_HPP__

#include <iostream>
#include <vector>
#include <type_traits>

//检查元素类型是否为算术类型
template <typename T>
bool CheckArithmType()
{
	using namespace std;

	if(is_arithmetic<T>::value == false) {
		cerr << "The element's type must is arithmetic" << endl;
		return false;
	}
	return true;
}

//检查元素类型是否为整形
template <typename T>
bool CheckIntegral()
{
	using namespace std;

	if(is_integral<T>::value == false 
			|| is_unsigned<T>::value == false) {
		cerr << "The element's type must is unsigned integral" << endl;
		return false;
	}
	return true;
}

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
	for(auto e : d)
		os << e << "\t";
	os << std::endl;
}

#endif
