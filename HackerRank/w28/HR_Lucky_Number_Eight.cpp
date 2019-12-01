#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define MAXN    200000

long long F[2][8];  // F[pre][x]
char S[MAXN+10];

int main()
{
    int N;
    scanf("%d", &N);
    scanf("%s", S);

    int digit;
    bool pre = 0;
    bool cur = 1;
    // long long result = 0LL;
    for (size_t i = 0; i < N; ++i) {
        digit = S[i] - '0';
        for (int k = 0; k < 8; ++k) {
            F[cur][k] = F[pre][k];
        }
        
        ++ F[cur][digit % 8];

        for (int k = 0; k < 8; ++k) {
            F[cur][(k * 10 + digit) % 8] += F[pre][k];
            F[cur][(k * 10 + digit) % 8] %= MOD;
        }
        
        pre = !pre;
        cur = !cur;
    }
    
    printf("%lld\n", F[pre][0] % MOD);
}
