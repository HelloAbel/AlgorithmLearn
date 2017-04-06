#ifndef BMH_HPP__
#define BMH_HPP__

#include <string>
#include <vector>
#include <utility>

using namespace std;

#define SHIFT int                                           //位置类型

SHIFT bmh(string &src, string &pat)
{
    vector<pair<char, SHIFT>> shiftTable;
    auto plen = pat.size();
    auto slen = src.size();
    
    // 计算偏移表，即当发生失位时，文本指针需要向后移动几位来重新比较
    for (SHIFT i = 0;i != plen-1;++i) {
        auto iter = shiftTable.begin();
        for (;iter != shiftTable.end();++iter) {
            if (iter->first == pat[i]) {
                iter->second = plen-1-i;
                break;
            }
        }
        if (iter == shiftTable.end()) {
            shiftTable.push_back(make_pair(pat[i], plen-1-i));
        }
    }
    
    SHIFT i = 0, j = plen-1;
    // 寻找对应字母的偏移量
    auto search = [&shiftTable, &plen](char dist) -> SHIFT {
        for (auto iter = shiftTable.begin();iter != shiftTable.end();++iter) {
            if (dist == iter->first)
                return iter->second;
        }
        return plen;
    };
    while (i <= slen-plen) {
        while (pat[j] == src[i+j]) {
            --j;
            if (j < 0) 
                return i;
        }
        i = i+search(src[i+plen-1]);                        // 发生失位，向后移动
        j = plen-1;
    }
    
    return 0;
}


#endif
