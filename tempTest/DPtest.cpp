//动态规划实例：计算硬币最大和
//问题描述：给定一排硬币，在位置不相邻的情况下计算最大和
//思路描述：设硬币有n个，最大和的值为F[n]，则最大化有两种情况，要么不包含最后一枚硬币，要么包含最后一枚硬币，
//用公式表述就是F[n]=max{c_n+F[n-2], F[n-1]}，c_n是第n个硬币的值
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> coin;
    vector<int> res;
    int val;
    
    cout << "Input the coin's value" << endl;
    while(cin >> val)
        coin.push_back(val);
    
    res.push_back(0);
    res.push_back(coin[0]);
    for(int i=1; i<coin.size(); ++i) {
        res.push_back(res[i]>(coin[i]+res[i-1])?res[i]:(coin[i]+res[i-1]));
    }
    
    cout << "The maximum coin-sum is " << *(res.end()-1) << endl;
    return 0;
}
