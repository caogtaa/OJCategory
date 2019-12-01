#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

// https://www.hackerrank.com/challenges/prime-xor/problem
// DP
// 题意：给定N个数字组成一个集合，(N <= 1e5, 数字范围[3500, 4500])。需要找出具备如下性质的所有子集合数量：“集合内所有元素的XOR结果是素数”
// 思路：数字范围是[3500, 4500]，很容易想到把数字计数，范围缩小至1000（命名为M)
// [3500, 4500]内的数字XOR后的结果范围是[0, 8191]，根据如下推算可以得到（命名为MAXA)
// 4500 = 1000110010100
// 8191 = 1111111111111
//
// 能想到的最好算法复杂度是 M * MAXA 级别的，不是很有信心怕超时。看到评论区有人这么做了就试了一把
// 设F[i][p]为用前i个数字组成的所有子集中，SET XOR的结果是p的子集数量
// i遍历所有出现的数字，根据F[i][?]和第i+1个数字的出现次数，能推算出F[i+1][?]。具体推导见代码
// F[M]保存了所有子集SET XOR能够得到的不同结果以及出现次数，累加其中的prime项即为所求

// helper functions
string binary_present(int n)
{
    string result;
    while (n) {
        if (n & 1) {
            result.insert(0, "1");
        } else {
            result.insert(0, "0");
        }
        
        n >>= 1;
    }
    
    return result;
}

int hex_present(const string &b)
{
    int result = 0;
    for (size_t i = 0; i < b.size(); ++i) {
        result <<= 1;
        if (b[i] == '1') {
            ++ result;
        }
    }
    
    return result;
}



// #define MAXN 100000
#define MAXA 8191
#define MOD  1000000007

long long F[2][MAXA+1];
int Q;
int N;
int appear[4501];
bool unprime[MAXA+1];

void init_prime()
{
    int i;
    int base;
    int cc = (int)sqrt(MAXA * 1.0);
    unprime[1] = true;
    for (i = 2; i <= cc; i++){
        if (unprime[i])
            continue;
        
        base = i * i;
        while (base <= MAXA){
            unprime[base] = true;
            base += i;
        }
    }
}

int main()
{
    init_prime();

    scanf("%d", &Q);
    while (Q--) {
        scanf("%d", &N);
        memset(appear, 0, sizeof(appear));
        int x;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &x);
            ++ appear[x];
        }
        
        // read input finish, start DP
        bool cur = 0;
        bool nxt = 1;
        memset(F[cur], 0, sizeof(long long) * (MAXA + 1));
        for (int k = 3500; k < 4501; k++) {
            if (appear[k] == 0)
                continue;
            
            // DP update
            memset(F[nxt], 0, sizeof(long long) * (MAXA + 1));

            // add self only
            F[nxt][k] += ((appear[k]+1) >> 1);  // add odd number of k's
            F[nxt][0] += (appear[k]>>1);        // add even number of k's
            
            for (int p = 0; p <= MAXA; ++p) {
                if (!F[cur][p])
                    continue;
                
                // add odd number of k's, XOR
                F[nxt][p^k] += F[cur][p] * ((appear[k]+1) >> 1);
                F[nxt][p^k] %= MOD;
                
                // add even/zero number of k's
                F[nxt][p] += F[cur][p] * ((appear[k]>>1) + 1);
                F[nxt][p] %= MOD;
            }
            
            cur = !cur;
            nxt = !nxt;
        }
        
        long long result = 0LL;
        for (int p = 2; p <= MAXA; ++p) {
            if (F[cur][p] > 0 && !unprime[p]) {
                result = (result + F[cur][p]) % MOD;
            }
        }
        
        printf("%lld\n", result);
    }
    
    return 0;
}
