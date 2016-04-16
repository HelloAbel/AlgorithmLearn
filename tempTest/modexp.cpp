//测试指数模运算
#include <iostream>

using namespace std;

static unsigned count = 0;

unsigned modexp(long long x, unsigned long long y, unsigned int N)
{
	count += 1;
	auto down2 = [](unsigned long long t) -> unsigned long long { return t%2==1?(t-1)/2:t/2; };
	if(y==0)
		return 1;
	auto z = modexp(x,down2(y),N);
	if(y%2)
		return (x*y*y)%N;
	else
		return (y*y)%N;
}

int main()
{
	long long x;
	unsigned long long y;
	unsigned n;
	cout << "输入三个数: ";
	cin >> x >> y >> n;
	cout << "模指数结果为: " << modexp(x,y,n)  << endl;

	return 0;
}
