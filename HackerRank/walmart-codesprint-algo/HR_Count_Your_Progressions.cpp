/*
题意：找出数列A中的所有递增数列，空数列和一个数字也被认为是递增数列。数列长度N <= 2*10^5, 1 <= ai <= 100
思路：考虑过DP做法，但是没有得出递推公式，同时N*max(ai)的大小也几乎是内存极限
我们首先考虑差>0的等差数列，不考虑所有元素相等的数列或者递减数列
设F[X][D][b]表示当前已知的以数字X开始，差为D的数列个数，b为true时表示改数列长度len>1，否则len==1
b的作用在后面会解释
设appear[X]为当前已知X是否已经出现过
从右到左遍历数列A，考虑如何计算以Ai开头，差为D的数列
1.++F[Ai][D][false]，即多了一个以Ai结尾的，差为D的数列
2.如果Ai+D出现过，则基于所有Ai+D开头，差为D的数列，我们在开头补一个Ai，可以得到一个新的数列
所以F[Ai][D] += F[Ai+D][D][true] + F[Ai+D][D][false]

数列A遍历完后，枚举X = 1..100 和D = 1..100，得到所有D > 0的等差数列数量
接下来考虑D < 0的情况，我们将数列A反转，重复上述步骤即可
接下来考虑D == 0的情况，我们统计所有数字的出现频度，问题变为一个类似排列组合的问题
设sum[i]为i个相同数字能得到的数列个数（不同位置的相同数字组成的数列也被认为是不同数列）
sum[0] = 0, sum[1] = 1
sum[i] = sum[i-1] * 2 + 1     // 即增加一个数字后，这个数字和之前所有的数列都能拼出一个新数列，同时自己单独也形成一个数列
D>0, D<0, D==0的情况累加，在加上空序列数量1，就是题目所求
时间复杂度O(N * max(Ai))
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

#define MOD 1000000009
#define MAXN    100
int N;
int A[200001];
long long sum[200001];
int cnt[MAXN+1];
int appear[(MAXN << 1)+1];        // appear[i] = appearance of number i
long long F[MAXN+1][MAXN+1][2];     // F[i][D][b] = count of sequence start with number i, ofset = D. b means if seq length >= 2

long long roll()
{
    memset(F, 0, sizeof(F));
    memset(appear, -1, sizeof(appear));
    for (int pos = N-1; pos >= 0; --pos) {
        // make F[i][k]
        int i = A[pos];
        for (int D = 0; D <= MAXN; ++D) {
            ++F[i][D][false];
            F[i][D][false] %= MOD;

            if (appear[i+D] != -1) {
                // D, try accumulate sequence {i, i+D, ...}
                F[i][D][true] += ((F[i+D][D][true] + F[i+D][D][false]) % MOD);
                F[i][D][true] %= MOD;
            }
        }
        
        
        appear[i] = pos;
    }
    
    long long result = 0LL;
    for (int i = 1; i <= MAXN; ++i) {
        for (int D = 1; D <= MAXN; ++D) {
            result += F[i][D][true];
        }
    }
    
    return result;
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        ++ cnt[A[i]];
    }
    
    auto result = roll();
    reverse(A, A+N);
    result = (result + roll()) % MOD;

    // initialize sum
    sum[0] = 0;
    sum[1] = 1;
    for (int i = 2; i <= N; ++i) {
        sum[i] = sum[i-1] * 2 + 1;
        sum[i] %= MOD;
    }

    // add simple sequence
    for (int i = 1; i <= MAXN; ++i) {
        result = result + sum[cnt[i]];
    }
    
    // add empty sequence +1
    result = (result + 1) % MOD;
    
    cout << result << endl;
    return 0;
}
