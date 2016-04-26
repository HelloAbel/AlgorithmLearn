//桶排序头文件
//2016-04-25
//
#ifndef BUCKET_SORT_HPP__
#define BUCKET_SORT_HPP__

#include "common.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <memory>
#include <limits>
#include <iostream>

//算出是十进制几位数
template <typename T>
inline unsigned bias(T x)
{
	unsigned d;
	for(T tmp=x; tmp>=1.0; tmp/=10.0)
		d += 1;

	return d;
}

//计算10的n次方
inline unsigned long long
pow(int n)
{
	unsigned long long result = 1;
	for(int x=1; x<=n; ++x)
		result *= 10;

	return result;
}

//定义这个删除器函数是为了改变
//智能指针的删除行为，防止二次释放
template <typename T>
void del(T *)
{}

template <typename T>
bool bucketSort(std::vector<T> &s)
{
	using namespace std;
	struct ele
	{
		double num;
		shared_ptr<ele> priv;
		shared_ptr<ele> next;
	};

	if(!CheckArithmType<T>())
		return false;

	auto size = s.size();
	auto maxEle = max_element(s.begin(), s.end());
	vector<ele> tmps(s.size());
	//落入同一个桶中的用链表串起来
	vector<ele> sameBucket(s.size());
	unsigned post;
	//对每一个元素进行处理成0-1的规范项
	auto maxpost = static_cast<double>(pow(bias(*maxEle)));
	unsigned postSlot;

	for(int i=0; i!=s.size(); ++i) {
		tmps[i].num = static_cast<double>(s[i])/maxpost;
		sameBucket[i].num = numeric_limits<T>::min();
	}
	for(int i=0; i!=s.size(); ++i) {
		//当用智能指针串成链表的时候需要注意，如果不传递删除器，
		//智能指针会将参数当作动态内存释放，而ele类型是聚合类，
		//会在函数结束后自动释放变量，这样就会造成二次释放，
		//产生非法指针被释放的错误
		post = static_cast<unsigned>(tmps[i].num*s.size());
		if(sameBucket[post].next==nullptr) {
			sameBucket[post].next = shared_ptr<ele>(&tmps[i], del<ele>);
			tmps[i].priv = shared_ptr<ele>(&sameBucket[post], del<ele>);
		}
		else {
			auto ptr = sameBucket[post].next;
			while(ptr->num<tmps[i].num) {
				if(ptr->next == nullptr)
					break;
				ptr = ptr->next;
			}
			if(ptr->next!=nullptr || ptr->num>=tmps[i].num) {
				tmps[i].next = ptr;
				tmps[i].priv = ptr->priv;
				ptr->priv->next = shared_ptr<ele>(&tmps[i], del<ele>);
				ptr->priv = shared_ptr<ele>(&tmps[i], del<ele>);
			}
			else {
				ptr->next = shared_ptr<ele>(&tmps[i], del<ele>);
				tmps[i].priv = ptr;
				tmps[i].next = nullptr;
			}
		}
	}

	for(int i=0; i!=s.size(); ++i) {
		if(sameBucket[i].next != nullptr) {
			auto ptr = sameBucket[i].next;
			while(ptr!=nullptr) {
				s[postSlot] = static_cast<T>(ptr->num*maxpost);
				ptr = ptr->next;
				++postSlot;
			}
			continue;
		}
	}

	return true;
}

#endif
