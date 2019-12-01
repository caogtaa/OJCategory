// https://www.hackerrank.com/challenges/strplay
// 简单题，DP
// 题意：
// 串S切成2段，在两段中分别找出一个回文，求两个回文长度乘积最大是多少。|S| <= 3000

// 思路：
// 根据|S| <= 3000可以用O(N^2)算法，可求所有S[sp, ep]子串内的最大回文长度，然后遍历切分位置
// 设F[len][sp]为从sp开始，长度为len的子串中所能找出的最长回文子串, ep = len + sp - 1
// 递推公式：
// 当S[sp] == S[ep]时, F[len][sp] = 2 + F[len-2][sp+1]  (两头缩短，根据贪心定理可以不于下述条件比max)
// 否则 F[len][sp] = F[len-1][sp] + F[len-1][sp+1]  (尝试左边缩短或者右边缩短，取最大值)
// 根据递推公式，可以优化内存空间为3行滚动数组

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define MAXN    3001

int N;
char S[MAXN];
int F[MAXN][MAXN];

int main() {
    scanf("%s", S);
    N = (int)strlen(S);
    for (int i = 0; i < N; ++i) {
        F[1][i] = 1;
    }
    
    int res;
    int ep;
    for (int len = 2; len <= N; ++len) {
        for (int sp = 0; sp + len <= N; ++sp) {
            ep = sp+len-1;
            if (S[ep] == S[sp]) {
                F[len][sp] = 2 + (len > 2 ? F[len-2][sp+1] : 0);
            } else {
                F[len][sp] = max(F[len-1][sp+1], F[len-1][sp]);
            }
        }
    }
    
    int best = 0;
    for (int len = 1; len < N; ++len) { // token 1 length
        best = max(best, F[len][0] * F[N-len][len]);
    }
    
    printf("%d\n", best);
    
    return 0;
}

