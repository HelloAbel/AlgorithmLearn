//测试Fibonacci数列
#include <iostream>

using namespace std;

static unsigned long long amount1 = 0;
static unsigned long long amount2 = 0;

//使用递归的方法计算
unsigned long long fibo1(int pos)
{
	amount1 += 1;
	if(pos==0)
		return 0;
	else if(pos==1)
		return 1;
	else
		return fibo1(pos-1)+fibo1(pos-2);
}

//使用迭代的方法计算
unsigned long long fibo2(int pos, int len, unsigned long long count, unsigned long long preCount)
{
	amount2 += 1;
	if(pos == len)
		return count;
	return fibo2(pos+1, len, count+preCount, count);
}

int main()
{
	int len = 30;
	cout << "result1: " << fibo1(len) << "\tresult2: " << fibo2(1, len, 1, 0) << endl;
	cout << "amount1: " << amount1 << "\tamount2: " << amount2 << endl;

	return 0;
}
