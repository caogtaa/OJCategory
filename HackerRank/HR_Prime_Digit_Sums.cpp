#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;

// DP
// 题意：Chloe定义了一种数字的规则（这里简称为Chloe数)
// 1. 所有连续3个数字之和是素数
// 2. 所有连续4个数字之和是素数
// 3. 所有连续5个数字之和是素数
// 给定N(N <= 4e5)，求N位的10进制数中有多少个Chloe数，Query数Q <= 2e4
// 思路：Q比较大，暂时先不管，考虑一个N的情况
// 先进行一些准备工作，枚举一下 [0...99999]范围内的Chloe数，发现数量是393（小于5位数的都以0开头补齐，这些数字是允许出现于数字的非开头部分）
// 5位的Chloe数“右移”一位，即去掉最左侧一位，右侧加上一位，能够得到另一个5位的Chloe数。以此可以得到所有5位Chloe数的转换关系，这种转换关系很少，只有200+
// 根据转换关系可以通过DP求出N位Chloe数的数量。初始5位数字注意去掉0开头的数字
// N = [1...4]的情况可以通过暴力枚举出来

// 优化：每次的DP是O(200N)的时间复杂度，Q<=2e4，所以不能对每个Q从头开始计算
// 找出所有Q中的最大N，在计算这个Query的过程中会经过其他Query，顺便记录下这些结果

#define MOD     1000000007
#define MAXP    100000
#define VALIDN  393
bool unprime[MAXP+1];
long long F[2][VALIDN+1];
int N[20001];
bool appear[400001];    // if query k is appear
long long result[400001];

vector<int> pre[VALIDN+1];
unordered_map<int, int> order;

void initPrime()
{
    int i;
    int base;
    int cc = (int)sqrt(MAXP * 1.0);
    unprime[0] = unprime[1] = true;
    for (i = 2; i <= cc; i++){
        if (unprime[i])
            continue;
        
        base = i * i;
        while (base <= MAXP){
            unprime[base] = true;
            base += i;
        }
    }
}

bool sum_is_prime(int n)
{
    int p = 0;
    while (n) {
        p += n % 10;
        n /= 10;
    }
    
    return !unprime[p];
}

bool isValid(int n)
{
    if (!sum_is_prime(n))
        return false;
    
    if (!sum_is_prime(n % 10000))
        // right four digits
        return false;
    
    if (!sum_is_prime(n / 10))
        // left four digits
        return false;
    
    if (!sum_is_prime(n % 1000))
        // right 3 dights
        return false;
    
    if (!sum_is_prime(n / 100))
        // left 3 digits
        return false;
    
    if (!sum_is_prime((n % 10000) / 10))
        // middle 3 digits
        return false;
    
    return true;
}

bool isValid3(int n)
{
    return sum_is_prime(n);
}

bool isValid4(int n)
{
    if (!sum_is_prime(n))
        return false;
    
    if (!sum_is_prime(n % 1000))
        return false;
    
    if (!sum_is_prime(n / 10))
        return false;
    
    return true;
}

// FILE *pin = freopen("/users/taobao/workspace/inputx.txt", "r", stdin);
// FILE *pout = freopen("/users/taobao/workspace/outputx2.txt", "w", stdout);

int main()
{
    initPrime();
    isValid(10193);
    vector<int> valid;
    int idx = 0;
    for (int i = 0; i <= 99999; ++i) {
        if (isValid(i)) {
            valid.push_back(i);
            order[i] = idx++;
        }
    }
    
    // valid = 393
    for (size_t i = 0; i < valid.size(); ++i) {
        auto v = valid[i];
        for (int d = 0; d < 10; ++d) {
            int k = (v % 10000) * 10 + d;
            if (isValid(k)) {
                // nxt[i].push_back(k);
                pre[order[k]].push_back((int)i);
            }
        }
    }
    
    int Q;
    scanf("%d", &Q);
    int mxn = 0;
    for (int t = 0; t < Q; ++t) {
        scanf("%d", N+t);
        appear[N[t]] = true;
        mxn = std::max(mxn, N[t]);
    }
    
    bool cur = false;
    for (int i = 0; i < VALIDN; ++i) {
        if (valid[i] >= 10000)
            F[cur][i] = 1;
    }
    
    for (int i = 6; i <= mxn; ++i) {
        for (int k = 0; k < VALIDN; ++k) {
            F[!cur][k] = 0LL;
            for (auto p : pre[k]) {
                F[!cur][k] += F[cur][p];
                F[!cur][k] %= MOD;
            }
        }
        
        cur = !cur;
        
        if (appear[i]) {
            // make result for i+1
            long long r = 0LL;
            for (int k = 0; k < VALIDN; ++k) {
                r += F[cur][k];
                r %= MOD;
            }
            
            result[i] = r;
        }
    }
    
    // bruteforce N <= 4
    result[1] = 9;
    result[2] = 90;
    result[3] = 0LL;
    for (int i = 100; i <= 999; ++i) {
        if (isValid3(i))
            ++ result[3];
    }
    
    for (int i = 1000; i <= 9999; ++i) {
        if (isValid4(i))
            ++ result[4];
    }
    
    for (auto v : valid) {
        if (v >= 10000)
            ++ result[5];
    }

    // result[5] = VALIDN;
    for (int t = 0; t < Q; ++t) {
        printf("%lld\n", result[N[t]]);
    }
    
    return 0;
}
