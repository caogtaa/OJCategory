#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP
// 题意：用四种长度的乐高积木，每一种无限量，堆积一个高N，宽M的墙。要求墙没有洞，是稳定结构（即墙不是用多面独立的小墙排列得到，在不切断积木的情况下无法将墙从某两列的缝隙分离）。乐高积木只能横着放，求总共有多少种堆积方法
// 思路：一开始没有很清晰的解题思路如何去掉unsolid的方法，思维局限在了以行的方式递推，看了editorial后发现解发很巧妙
// 1. 单独考虑一行的排列，很容易得到递推公式one_row[x] = sigma(one_row[x-k]) [k=1..4]
// 2. 考虑混合了unsolid摆发的方法数，每一行的排列都是单独考虑的，对于H * W的墙总数是 unsolid[H][W] = one_row[W]^H
// 3. 如何从unsolid[H][W]筛选出solid的值是此题的关键，假设我们已经知道solid[H][1] ~ solid[H][k-1]的摆法，可以求出solid[H][k]
//    在H * k的墙中，unsolid的摆法对应的分割线可能出现在任意位置，我们可以枚举分割线，假设左i列的摆法是solid的，那么右边k-i可以任意排列
//    于是有递推公式：
//    solid[H][1] = unsolid[H][1] = 1
//    solid[H][k] = unsolid[H][k] - sigma(solid[H][i] * unsolid[H][k-i]) [i=1...k-1]
//    其中H是常数，而且递推中并用不到，所以solid可以是一维数组

#define MOD 1000000007
#define MAXN    1000

int N, M;

long long solid[MAXN+1];    // solid[k] = F[height][k] with height fixed to N
long long one_row[MAXN+1];  // one_row[k] = F[1][k]

long long exp_mod(long long x, int e)
{
    if (e == 0)
        return 1LL;
    
    long long result = exp_mod(x, e >> 1);
    result = (result * result) % MOD;
    if (e & 1) {
        result = (result * x) % MOD;
    }
    
    return result;
}

long long unsolid(int h, int w)
{
    return exp_mod(one_row[w], h);
}

void init()
{
    one_row[0] = one_row[1] = 1;
    for (int w = 2; w <= MAXN; ++w) {
        one_row[w] = 0;
        for (int k = 1; k <= 4; ++k) {
            if (w-k >= 0) {
                one_row[w] += one_row[w-k];
                one_row[w] %= MOD;
            }
        }
    }
}

int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        solid[0] = solid[1] = 1;
        for (int w = 2; w <= M; ++w) {
            auto result = unsolid(N, w);
            for (int s = 1; s <= w-1; ++s) {
                result -= solid[s] * unsolid(N, w-s);
                result %= MOD;
                if (result < 0)
                    result += MOD;
            }
            solid[w] = result;
        }
        
        printf("%lld\n", solid[M]);
    }

    return 0;
}
