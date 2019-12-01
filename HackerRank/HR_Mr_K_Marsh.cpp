#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 题意：Mr.K想用栅栏围住一块地，这块地有写地方是湿地无法放置栅栏，栅栏必需是矩形，求能围住的最大周长是多少
// 思路：单边长度 N,M <= 500，N^3的算法是极限
// 1. 先计算两个辅助数组rit[i][k]和bottom[i][k]，分别表示从(i,k)点向右、向下连续无湿地的长度，使用DP的时间复杂度O(N*M)
// 2. 枚举举行的上边和下边的y，在y0,y1确定的情况下想要围成一个矩形，那么在y0行上的点，往下走，bottom值必需至少抵达y1，扫描这一行将所有满足的列记录
// 3. 对于所有上述列，两两匹配，对于左点的rit值至少抵达右点的点对，记录它们和y0 y1结合组成的矩形周长。这里用贪心扫描一遍即可。贪心思路是：选择最左侧的点作为左点，不断延伸右点。如果左点、右点连线上没有湿地，则作为一个合法的矩阵计算周长；如果遇到湿地，左点逐步右移直到连线上无湿地
// 一开始用N^3的算法不是很有底，看了一遍讨论区有人还是用N^4的算法做优化的，果断用N^3写了一遍。事实证明server的CPU很快

#define MAXN    501
int M, N;
char field[MAXN][MAXN];

int rit[MAXN][MAXN];
int bottom[MAXN][MAXN];

inline int perimeter(int h, int w)
{
    return 2 * (h + w);
}

int main()
{
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; ++i) {
        scanf("%s", field[i]);
    }
    
    for (int i = 0; i < M; ++i) {
        rit[i][N-1] = (field[i][N-1] == '.') ? 1 : 0;
        for (int k = N-2; k >= 0; --k) {
            if (field[i][k] == '.')
                rit[i][k] = rit[i][k+1] + 1;
            else
                rit[i][k] = 0;
        }
    }
    
    for (int k = 0; k < N; ++k) {
        bottom[M-1][k] = (field[M-1][k] == '.') ? 1 : 0;
        for (int i = M-2; i >= 0; --i) {
            if (field[i][k] == '.')
                bottom[i][k] = bottom[i+1][k] + 1;
            else
                bottom[i][k] = 0;
        }
    }
    
    vector<int> valid_columns;
    valid_columns.reserve(N);
    int best = 0;
    for (int l1 = 0; l1 < M; ++l1) {
        for (int l2 = l1 + 1; l2 < M; ++l2) {
            int height = l2 - l1;
            valid_columns.resize(0);
            for (int k = 0; k < N; ++k) {
                if (bottom[l1][k] >= height + 1) {
                    valid_columns.push_back(k);
                }
            }
            
            int sp = 0;
            int ep = 1;
            for (; ep < (int)valid_columns.size(); ++ep) {
                int w = valid_columns[ep] - valid_columns[sp];
                while (sp < ep && (rit[l1][valid_columns[sp]] < w+1 || rit[l2][valid_columns[sp]] < w+1)) {
                    ++ sp;
                }
                
                if (sp < ep) {
                    // valid rectangle found
                    best = max(best, perimeter(height, w));
                }
            }
        }
    }
    
    if (best > 0)
        printf("%d\n", best);
    else
        printf("impossible\n");
    
    return 0;
}
