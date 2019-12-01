#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

// DP, permutation
// 题意：Sherlock用一个错误的算法把多个数组合并到一起并进行排序
// 这个算法步骤如下:
// 1. 将所有数组左对齐(按照下标对齐)
// 2. k = 0->N-1，每次将所有数组中下标为k的数字丢到数组T中(如果数组不足k长度则这一步该数组不提供数字)
// 3. 对T里的数字排序，然后存入最终数组M
// Watson想要根据Sherlock合并后的数组M逆向还原出输入参数，求输入的参数有多少种可能性

// 思路：通过观察可以发现如果M中出现了逆序的数字对，那么这两个数字必需位于不同的下标（不管是不是在相同数组里）
// 正序的一系列数字，可以以任意长度按批次输出，这个长度是当前状态下仍存在的数组数量，但是由于下标越大数组的数量会越小（部分数组长度不足），输出的序列长度也会逐步变小
// 算法：
// 1. 将输入序列预处理，以逆序出现的位置截断进行分层，分层后每一层里的数字都是正序的
// 2. 尝试初始的数组数量为K (1 <= K <= 第一层数字个数)，令F[K][S]是当前有K个数组，M[S...N)的数字有多少种不同的分配方法
//    递推公式为F[K][S] = sigma(F[i][S-i] * A(K, i)) [i = 1 ... K]   i表示当前列打算挑选i个数字，挑选后数组的个数也会变成i
//    其中A(K, i)需要预处理打表，F[K][0]的处理是不需要A(K, i)项的，因为此时的排列是重复的
// N <= 1200，算法时间复杂度看起来是O(N^3)，但是没有超时，复杂度分析可能有问题

using namespace std;

#define MOD     1000000007
#define MAXN    1200
//#define MAXN    4
long long A[MAXN+1][MAXN+1];    // permutation number, A(n, n) stand for A!
long long F[MAXN+1][MAXN+1];
int level[MAXN+2];
int N;
int M[MAXN+2];
vector<int> level_end;

void initA()
{
//    A[1][1] = 1;
//    for (int i = 2; i <= MAXN; ++i) {
//        A[i][i] = (A[i-1][i-1] * i) % MOD;
//    }
    
    for (int i = 0; i <= MAXN; ++i) {
        A[i][0] = 1;
    }

    for (int i = 1; i <= MAXN; ++i) {
        A[i][0] = 1;
        A[i][1] = i;
        for (int k = 2; k <= i; ++k) {
            A[i][k] = (A[i][k-1] * (i-k+1)) % MOD;
        }
    }
}

long long Func(int k, int s)
{
    if (s >= N)
        // all number is assigned
        return 1;

    long long &ret = F[k][s];
    if (ret == -1) {
        if (k <= 1) {
            // 1 array left, all numbre append to it
            ret = 1;
        } else {
            ret = 0;
            int na = min(k, level_end[level[s]] - s);
            while (na >= 1) {
                // choose na number of array
                ret += A[k][na] * Func(na, s+na);
                ret %= MOD;
                -- na;
            }
        }
    }
    
    return ret;
}

int main() {
    memset(F, -1, sizeof(F));
    initA();
    
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", M+i);
    }
    
    M[N] = -1;  // sentinel
    
    int level_start = 0;
    int level_index = 0;
    level[0] = 0;
    for (int i = 1; i <= N; ++i) {
        if (M[i] < M[i-1]) {
            // end this level
            level_end.push_back(i);
            ++ level_index;
            level_start = i;
        }
        
        level[i] = level_index;
    }
    
    long long result = 0LL;
    
    // F[0][0] without coef
    // 1st level is level_end[0] size, try different nubmer of array
    for (int k = level_end[0]; k >= 1; --k) {
        result += Func(k, k);
        result %= MOD;
    }
    
    printf("%lld", result);
    
    return 0;
}
