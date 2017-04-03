// 动态规划实例，利用结合律找出矩阵乘法的最小代价序列
// vpuu代表n个矩阵的高度和宽度
// vvu代表计算出来的矩阵链相乘的最小代价，整个矩阵链的最小代价在右上角
// vu代表在矩阵外围插入括号时需要的指示，它里面的元素代表在它所属的半部（由它上一步决定）最后的右括号插到哪个矩阵之后
// vs代表矩阵链
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using namespace std;

unsigned num;

// 在适当的矩阵外围插入括号，表示顺序
void insertWrap(vector<string> &vs, unsigned low, 
    unsigned high, vector<vector<unsigned>> &vu) {
    vs[low].insert(0, "(");
    vs[high].insert(vs[high].size(), ")");
    auto newd = vu[low][high];

    if (low >= high)
        return;
    insertWrap(vs, low, newd, vu);
    insertWrap(vs, newd+1, high, vu);
}

void printMCO(vector<vector<unsigned>> &vu) {
	vector<string> vs;
	auto p = vs.begin();
	char tmp[1024] = {0};
	unsigned wrap = 0;
    
	for(int i=0; i!=num; ++i) {
		string s("A");
		sprintf(tmp, "%d", i);
		s.insert(s.size(), tmp);
		vs.push_back(s);
		memset(tmp, 0, sizeof(tmp));
	}
	p = vs.begin();    
    for (auto iter = vs.begin();iter != vs.end();++iter) {
        cout << *iter << " ";
    }
    cout << endl;
    
    int len = vu.size()-1;
    auto dir = vu[0][len];

    insertWrap(vs, 0, dir, vu);
    insertWrap(vs, dir+1, len, vu);

	for(auto b=vs.begin(); b!=vs.end(); ++b)
		cout << *b << " ";
	cout << endl;
}

// 计算矩阵链相乘的最小代价vvu，并填充打印矩阵链相乘顺序所需的指示矩阵vu
void mco(vector<pair<unsigned, unsigned>> &vpuu, vector<vector<unsigned>> &vu)
{
	vector<vector<unsigned>> vvu;
	unsigned n = vpuu.size();
	unsigned max = 0, tmp = 0;
	int re;

    cout << "Begin init the two-dimension matrix...." << endl;
    cout << "The dimension-size is " << n << endl;
	for(unsigned i=0; i!=n; ++i) {
		vector<unsigned> vu1, vu2;
		for(unsigned j=0; j!=n; ++j) {
			vu1.push_back(0);
			vu2.push_back(0);
		}
		vu1[i+1] = vpuu[i].first*vpuu[i+1].second*vpuu[i].second;
		vvu.push_back(vu1);
		vu.push_back(vu2);
	}
    cout << "Begin calculate the result-matrix..." << endl;
    
    for (unsigned s = 1;s != n;++s) {                                           //s代表一层层对角线
        for (unsigned i = s, j = 0;i != n;++i, ++j) {					       //i代表列 j代表行，都是从0开始
            max = vpuu[j].first*vpuu[j].second*vpuu[i].second+vvu[j][j]+vvu[j+1][i];
            
            re = j;
            for(unsigned m=j; m!=i; ++m) {
                tmp = vpuu[j].first*vpuu[m].second*vpuu[i].second+vvu[j][m]+vvu[m+1][i];
                if(tmp < max) {
                    max = tmp;
                    re = m;
                }
            }
            vu[j][i] = re;
            vvu[j][i] = max;            
        }
    }

	for(unsigned i=0; i!=n; ++i) {
		for(unsigned j=0; j!=n; ++j)
			cout << vvu[i][j] << " ";
		cout << endl;
	}

    for (int i = 0;i != vu.size();++i) {
        for (int j = 0;j != vu.size();++j)
            cout << vu[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
	unsigned dim1, dim2, check;
	cout << "请输入矩阵数目：";
	cin >> num;
	vector<pair<unsigned, unsigned>> vpuu;
	vector<vector<unsigned>> vu;
	cout << "请依次输入矩阵的高和宽长度：" << endl;
	cin >> dim1;
	cin >> dim2;
	check = dim2;
	vpuu.push_back(make_pair(dim1, dim2));
	for(int i=1; i!=num; ++i) {
		cin >> dim1;
		cin >> dim2;
		if(check!=dim1) {
			cout << "不符合矩阵乘法规则，请检索输入矩阵的高度和宽度" << endl;
			return -1;
		}
		check = dim2;
		vpuu.push_back(make_pair(dim1, dim2));
	}
	cout << "Begin call mco..." << endl;
	mco(vpuu, vu);
    cout << "Begin print matrix-chain-order..." << endl;
	printMCO(vu);

	return 0;
}
