#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

// DP, 先将所有输入统计，放入数组A
// F[pos][ab][bc][ca] 表示从A数组pos位置开始往后摆放，当前3个集合的相交状态分别是ab,bc,ca，所能够得到的不同triple数量
// 初始条件是F[0][false][false][false]

// 题目要求A, B, C 3个集合两两相交，但是要求3个集合没有共同数字
// 所以对于一个数字，要么放入一个集合，要么放入3个集合，要么跳过这个数字不放
// 放入的时候考虑可以放入1到count个，累加上述可能性求出F

const long long MOD = 1000000007;
int N;
int cnt[1000001];
long long F[100001][2][2][2];
vector<int> A;

long long Func(int pos, bool ab, bool bc, bool ca)
{
    if (pos >= A.size()) {
        return (ab && bc && ca) ? 1 : 0;
    }
    
    auto &ret = F[pos][ab][bc][ca];
    if (ret != -1)
        return ret;
    
    ret = 0;
    int c = cnt[A[pos]];
    // assign current value to one set, possibility = 3 * count
    ret += ((3LL * c) % MOD) * Func(pos+1, ab, bc, ca);
    ret %= MOD;
    
    // assign to two set, possibility = count * count
    long long c2 = c * c;
    c2 %= MOD;

    // ab
    ret += c2 * Func(pos+1, true, bc, ca);
    ret %= MOD;
    
    // bc
    ret += c2 * Func(pos+1, ab, true, ca);
    ret %= MOD;
    
    // ca
    ret += c2 * Func(pos+1, ab, bc, true);
    ret %= MOD;
    
    // not assign
    ret += Func(pos+1, ab, bc, ca);
    ret %= MOD;

    return ret;
}

int main()
{
    cin >> N;
    int v;
    int mx = 0;
    for (int i = 0; i < N; ++i) {
        cin >> v;
        mx = max(mx, v);
        ++ cnt[v];
    }
    
    // make possible recursive stack shorter
    for (int i = 1; i <= mx; ++i) {
        if (cnt[i] > 0)
            A.push_back(i);
    }
    
    memset(F, -1, sizeof(F));
    cout << Func(0, 0, 0, 0) << endl;
    
    return 0;
}
