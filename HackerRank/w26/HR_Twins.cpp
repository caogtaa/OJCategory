/*
题意：孪生素数定义：i, j两个数都是素数并且|i-j| = 2。求[N, M]区间内的孪生素数对有多少个，i,j 和 j,i示为一对。
限制：1<=N<=M<=10^9,   M-N <= 10^6
思路1：遍历[N,M]区间，对数字做Miller_Rabin判断
思路2：由于N,M范围较大，不能用朴素打表算法，但是M-N<=10^6，可以修改打表法实现区间打表
仔细阅读朴素打表算法，可以发现N范围内的表都可以通过sqrt(N)的小表来获得，所以我们可以同时构造[2, sqrt(N)]和[N,M]两个区间的素数表。之后通过遍历[N,M]区间求解
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// https://www.hackerrank.com/contests/w26/challenges/twins
#define MAXN    61

bool unprime[MAXN+1];

void initPrime()
{
    int i;
    int base;
    int cc = (int)sqrt(MAXN * 1.0);
    unprime[1] = true;
    for (i = 2; i <= cc; i++){
        if (unprime[i])
            continue;
        
        base = i * i;
        while (base <= MAXN){
            unprime[base] = true;
            base += i;
        }
    }
}

long long pow_mod(long long a, long long d, long long n)
{
    if (d == 0)
        return 1;
    else if (d == 1)
        return a;
    else if (d & 1)
        return (pow_mod((a * a) % n, d / 2, n) * a) % n;

    return pow_mod((a * a) % n, d / 2, n);
}

bool is_prime_test(long long a, long long n)
{
    if (n == 2)
        return true;
    if (n == 1 || (n & 1) == 0)
        return false;
 
    long long d = n-1;
    d = n-1;
    while ((d & 1) == 0) {
        d >>= 1;
    }
    
    long long t = pow_mod(a, d, n);
    while (d != n-1 && t != 1 && t != n-1) {
        t = (t * t) % n;
        d <<= 1;
    }
    
    return t == n-1 || (d & 1);
}

bool is_prime(long long n)
{
    if (n <= 61)
        return !unprime[n];

    return is_prime_test(2, n) &&
        is_prime_test(7, n) &&
        is_prime_test(61, n);
}

// prime test using miller_rabin
int main() {
    initPrime();
    int N, M;
    cin >> N >> M;
    
    int result = 0;
    for (int i = N / 2 * 2 + 1; i + 2 <= M; i += 2) {
        if (i > 3 && (i + 1) % 6 > 0)
            // not satisfy {6n-1, 6n+1} rule
            continue;
        
        if (is_prime(i) && is_prime(i+2)) {
            ++ result;
        }
    }

    cout << result;
    return 0;
}

// 区间打表法，sieve
// 普通打表法可以参考最上面的代码，可以看出循环范围是 [2...sqrt(M)]时，可以打出M大小的表
// 本题中用打表法的思想打出[2...sqrt(M)] + [N...M]两个区间，中间断开的部分直接跳过，跳到第一个 >=N 的i的倍数上
int main_sieve() {
    int N, M;
    cin >> N >> M;
    
    int sqrtM = (int)sqrt(M * 1.0) + 1;
    bool *prime_seg_1 = new bool[sqrtM+1];
    bool *prime_seg_2 = new bool[M-N+1];  // [N,M] inclusive
    
    fill(prime_seg_1, prime_seg_1 + sqrtM + 1, true);
    prime_seg_1[0] = prime_seg_1[1] = false;

    fill(prime_seg_2, prime_seg_2 + M - N + 1, true);
    
    int base;
    for (int i = 2; i <= sqrtM; i++){
        if (!prime_seg_1[i])
            continue;
        
        base = i * i;
        while (base <= sqrtM) {
            prime_seg_1[base] = false;
            base += i;
        }
        
        base = max(base, (N / i + (N % i > 0)) * i);    // when N % i == 0, use N; otherwise use ((N / i) + 1) * i
        while (base <= M) {
            prime_seg_2[base - N] = false;
            base += i;
        }
    }
    
    auto is_prime = [&](int x) {
        if (x <= sqrtM)
            return prime_seg_1[x];
        
        return prime_seg_2[x-N];
    };
    
    int result = 0;
    for (int i = N / 2 * 2 + 1; i + 2 <= M; i+=2) { // todo: fix
        if (is_prime(i) && is_prime(i+2))
            ++ result;
    }
    
    cout << result;

    return 0;
}

