// 字符串搜索KMP算法实现
#include <iostream>
#include <string>
#include <vector>
#include "../../include/kmp.hpp"

int main()
{
    string src;
    string pattern;

    cout << "Input the text string: ";
    cin >> src;
    cout << "Input the pattern string: ";
    cin >> pattern;

    auto res = kmp(src, pattern);
    if(!res) {
        cout << "No Match the pattern!!!" << endl;
        return 0;
    }
    
    cout << "Match the pattern in the text[" << res << "]" <<  endl;
    
    return 0;
}
