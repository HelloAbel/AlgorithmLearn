//堆排序的头文件
//2016-4-15
#ifndef HEAP_HPP__
#define HEAP_HPP__

#include <type_traits>
#include <functional>
#include <algorithm>
#include <utility>
#include <iostream>
#include "common.hpp"

#define LEFT_CH(POST) ( ((POST+1)<<1)-1 )
#define RIGHT_CH(POST) ( LEFT_CH(POST)+1 )

//检查元素类型是否为算术类型
template <typename T>
static inline bool CheckArithmType()
{
	using namespace std;

	if(is_arithmetic<T>::value == false) {
		cerr << "The element's type must is arithmetic" << endl;
		return false;
	}
	return true;
}

//从一列元素中根据选取规则选取极值并返回它和对应于列中位置组成的pair
template <typename T, typename __compare>
inline auto MinMax(std::initializer_list<T> _l, __compare _comp)
	-> std::pair<T, int>
{
	using namespace std;
	auto next = (_l.begin()+1);
	auto est = _l.begin();

	while(next != _l.end()){
		if(_comp(*next, *est))
			est = next;
		++next;
	}

	return std::make_pair(*est, static_cast<int>(est-_l.begin()));
}

template <typename T>
class HeapSort
{
	typedef std::function<bool(T, T)> DIRECT;
	//维护堆的性质
	void HeapIfy(std::vector<T> &s, int post, DIRECT _comp)
	{
		using namespace std;
		auto size = s.size();

		if(((post+1)<<1)<=(size-1))											//有两个儿子
		{
			auto est = MinMax<T, DIRECT>({s[post], s[LEFT_CH(post)], 
					s[RIGHT_CH(post)]}, _comp);
			//将需要交换的动作做成函数表
			vector<function<int(int)>> postV;
			postV.push_back([](int p) ->int { return (p); });
			//left
			postV.push_back([](int p) ->int { return ((p<<1)+1); });
			//right
			postV.push_back([](int p) ->int { return ((p+1)<<1); });
			while(post<(size/2) && s[post]!=est.first) {
				using std::swap;
				int chp = postV[est.second](post);
				swap(s[post], s[chp]);
				post = chp;
				if((post+1)*2 < size) 										//有两个儿子
					est = MinMax<T, DIRECT>({s[post], s[LEFT_CH(post)],
							s[RIGHT_CH(post)]}, _comp);
				else if((post+1)*2 == size) 								//只有左儿子
					est = MinMax<T, DIRECT>({s[post], s[LEFT_CH(post)]}, _comp);
			}
		}
		else {																//有且只有左儿子
			using std::swap;
			if(s[post]<s[LEFT_CH(post)]) {
				swap(s[post], s[LEFT_CH(post)]);
			}
		}
	}
	//默认最大堆
	bool BuildHeap(std::vector<T> &ss, DIRECT Comp)
	{
		using namespace std;
		if(CheckArithmType<T>() == false)
			return false;

		int i = ss.size()/2-1;
		int j  = 0;
		auto size = ss.size();

		//从第一个有儿子的节点开始不断维护堆的性质，直到根节点
		//建成一个最大或者最小堆
		HeapIfy(ss, i--, Comp);
		for(;i>=0;--i, ++j) {
			if(!(size%2))
				HeapIfy(ss, i, Comp);
			else
				HeapIfy(ss, i, Comp); 
		}

		return true;
	}

public:
	std::vector<T> hSort(std::vector<T> &A, DIRECT realComp = 
			[](T x, T y) -> bool { return x>y?true:false; })
	{
		using namespace std;
		vector<T> result;

		if(BuildHeap(A, realComp)) {
			//建好堆以后通过不断将根节点元素拿下和维护堆的性质
			//输出一个有序数组
			using std::swap;
			for(auto i=A.size(); i>=2; --i) {
				swap(A[0], A[i-1]);
				result.push_back(A[i-1]);
				A.pop_back();
				//最后一轮(i==2)只剩一个元素，若是继续维护堆的性质
				//便会把原本换下的倒数第二个元素又换到堆里，vector
				//的pop_back并不是把元素真正从内存中删除，所以这是
				//可能的，这时有序数组的最后一名便会被倒数第二覆盖
				if(i!=2)
					HeapIfy(A, 0, realComp);
			}
			result.push_back(A[0]);
		}

		return result;
	}
};

#endif
