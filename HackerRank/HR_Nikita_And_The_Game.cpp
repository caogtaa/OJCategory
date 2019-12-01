#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Nikita and the Game
// https://www.hackerrank.com/challenges/array-splitting
// 简单题，分治，Divide and conquer
// 如果所有输入都是0，切割次数就是N-1，即每次切掉一个0
// 如果出现了正整数，忽略掉所有的0，因为0并不会增加选择可能性
// 忽略了0之后，切割位置就变成唯一的了（如果存在一个位置）
// 用DP计算出sum[]数组，sum[x]表示所有x左侧的数字的和，sum[]可以帮助二分查找到切割位置
// 然后递归＋分治求解

#define MAXN    ((1<<14) + 1)
int N;
int A[MAXN];
long long sum[MAXN];

int mmax(int a, int b) {
    return a > b ? a : b;
}

int F(int sp, int ep) {
    if (ep - sp < 1)
        // single number can not be divided
        return 0;
    
    long long s = sum[ep] - sum[sp-1];
    if (s & 1)
        // not even number
        return 0;
    
    s >>= 1;
    s += sum[sp-1];
    long long *pos = lower_bound(sum+sp, sum+ep+1, s);
    if (*pos != s)
        // can not evenly divided
        return 0;
    
    // divide
    return mmax(F(sp, (int)(pos-sum)), F((int)(pos-sum)+1, ep)) + 1;
}

int main() {
    int T = 0;
    cin >> T;
    while (T-- > 0) {
        int tempN;
        cin >> tempN;
        
        // ignore all zeros
        N = 1;
        for (int i=0; i < tempN; ++i) {
            cin >> A[N];
            if (A[N] != 0)
                ++N;
        }
        --N;
        
        if (N == 0) {
            cout << tempN-1 << endl;
            continue;
        }
        
        sum[0] = A[0];
        for (int i = 1; i <= N; ++i)
            sum[i] = sum[i-1] + A[i];
        
        cout << F(1, N) << endl;
    }
    
    return 0;
}
