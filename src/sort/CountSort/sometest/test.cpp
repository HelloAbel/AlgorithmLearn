#include <iostream>

using namespace std;

int main()
{
	int i = 0;
	int j = 0;
	if(decltype(i) == decltype(j))
		cout << "same" << endl;

	return 0;
}
