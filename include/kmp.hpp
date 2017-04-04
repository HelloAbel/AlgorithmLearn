#ifndef KMP_HPP__
#define KMP_HPP__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void calcNext(string &pat, vector<int> &next)
{
    
    auto len = pat.size();

    for (auto i = 0;i != len;++i)
        next.push_back(-1);
    
    auto i = 1;
    auto k = next[i-1];
    while (i != len) {
        /*
         * next[0]=-1相当于一个哨兵位，next[i]里面存储的是当P[i]失位时需要重新开始比较
         * 的位置，即P[0]~P[i-1]子串中的最大前缀的长度。k在循环里的作用就是指示找到P[0]~P[k]
         * 某一个最大前缀后的后面一个位置，如果k指向-1，这时候P[0]~P[k]是一个空串，证明此时
         * P[0]~P[i-1]没有最长前缀，因此可以使next[i]=0。正好与一般情况下k++;next[i]=k效果一致
         */
        if (k == -1 || pat[i-1] == pat[k]) {
            k++;
            next[i] = k;
            i++;
        }
        else {
            k = next[k];
        }
    }
}

int kmp(string &src, string &pat)
{
    vector<int> next;
    
    calcNext(pat, next);
    
    for (auto iter = next.begin();iter != next.end();++iter) {
        cout << *iter << " ";
    }
    cout << endl;
    
    auto i = 0, j = 0;
    auto len1 = src.size(), len2 = pat.size();
    while (i != len1&&j != len2) {
        if (j == 0 || src[i] == pat[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }
    
    if (j == len2)
        return i-len2;
    return 0;
}


#endif
