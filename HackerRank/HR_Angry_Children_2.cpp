#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP, greedy
// 题意: 有N个袋子(N <= 1e5)，每个袋子里有不同数量的糖果(candy <= 1e9)，要把袋子分给K个孩子(K <= N)，要求这些袋子对应的"unfairness"最小
// 思路: 根据贪心原则，肯定是选择糖果数相近的袋子。先对袋子按照糖果数量排序，然后以K大小的窗口从左到右移动，中途记录UF最小值
// 窗口移动过程的UF可以根据上一个窗口的UF快速计算得到

#define MAXN    100000
int N, K;
long long candy[MAXN+1];
long long sum[MAXN+1];

int main()
{
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i) {
        scanf("%lld", candy + i);
    }
    
    sort(candy, candy+N);
    sum[0] = candy[0];
    for (int i = 1; i < N; ++i) {
        sum[i] = sum[i-1] + candy[i];
    }
    
    // choose 1st K packs
    long long base = 0LL;
    for (int i = 1; i < K; ++i) {
        base += (sum[K-1] - sum[i-1]) - candy[i-1] * (K-i);
    }
    
    long long best = base;
    for (int i = K; i < N; ++i) {
        // including ith pack, and remove i-Kth pack
        auto range = sum[i-1] - sum[i-K];
        base -= range - candy[i-K] * (K-1);
        base += candy[i] * (K-1) - range;
        best = std::min(best, base);
    }
    
    printf("%lld", best);
    return 0;
}
