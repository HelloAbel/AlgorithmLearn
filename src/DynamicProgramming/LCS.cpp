// 利用动态规划求解最长公共子序列
// calcMatrix代表根据动态规划求解最长公共子序列的长度矩阵
// trace代表根据calcMatrix求出的路径矩阵，'+'代表这个元素会出现在LCS中
#include <iostream>
#include <vector>

using namespace std;

#define ELEM int
#define VALUE int

typedef vector<ELEM> ltype;
typedef vector<vector<VALUE>> mtype;

void printLCS(mtype &trace, ltype &list1, ltype &list2)
{
    vector<ELEM> result;
    auto len1 = list1.size();
    auto len2 = list2.size();
    
    for (auto i = 1;i != len1+1;++i) {
        for (auto j = 1;j != len2+1;++j) {
            if (trace[i][j] == '+') {
                result.push_back(list1[i-1]);
                break;
            }
        }
    }
    
    cout << "Print the LCS: ";
    for (auto iter = result.begin();iter != result.end();++iter)
        cout << *iter << " ";
    cout << endl;
}

void lcs(ltype &list1, ltype &list2, mtype &calcMatrix, mtype &trace)
{
    auto rowlen = list1.size();
    auto colen = list2.size();
//    auto max = [](VALUE x, VALUE y) -> VALUE { return x>y?x:y; };
    
    for (int i = 1;i != rowlen+1;++i) {
        for (int j = 1;j != colen+1;++j) {
//            cout << "compara " << list1[i-1] << " and " << list2[j-1] << endl;
            if (list1[i-1] == list2[j-1] ) {
                calcMatrix[i][j] = calcMatrix[i-1][j-1]+1;
                trace[i][j] = '+';
            }
            else {
                auto left = calcMatrix[i][j-1];
                auto up = calcMatrix[i-1][j];
                if (left>up) {
                    trace[i][j] = '-';
                    calcMatrix[i][j] = left;
                }
                else {
                    trace[i][j] = '|';
                    calcMatrix[i][j] = up;
                }
            }
        }
    }    
    
}

int main()
{
    ltype list1;
    ltype list2;
    ELEM ele;
    
    cout << "Input the first list: ";
    while (cin>>ele) {
        list1.push_back(ele);
    }
    cout << "Input the second list: ";
    cin.clear();
    if (cin.eof())
        cout << "It's EOF" << endl;
    while (cin>>ele) {
        list2.push_back(ele);
    }
    cout << "Begin calculate the LCS..." << endl;
    
    auto len1 = list1.size();
    auto len2 = list2.size();
    mtype calcMatrix, trace;
    
    for (int i = 0;i != len1+1;++i) {
        vector<VALUE> col;
        for (VALUE j = 0;j != len2+1;++j) {
            col.push_back(0);
        }
        calcMatrix.push_back(col);
        trace.push_back(col);
    }
    lcs(list1, list2, calcMatrix, trace);
    printLCS(trace, list1, list2);
    
    return 0;
}
