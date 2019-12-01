#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

long long F[2002];
//long long G[2002];  // single base
long long sum[2002];

#define MOD 1000000007;

long long Func(int x)
{
    long long &ret = F[x];
    if (ret != -1)
        return ret;
    
    ret = 0;
    for (int i = 1; i <= x-1; ++i) {
        // ret += Gunc(i) + Func(x-i);  // Gunc(i) = Func(i-1);
        ret += (Func(i-1) * Func(x-i)) % MOD;
        ret %= MOD;
    }
    
    ret += Func(x-1);   // wrap
    ret %= MOD;
    return ret;
}

int main() {
    memset(F, -1, sizeof(F));
    F[0] = 1;
    F[1] = 1;
    F[2] = 2;
    
//    memset(G, -1, sizeof(G));
//    G[1] = 1;
//    G[2] = 1;
    
    Func(2000);
    sum[1] = F[1];
    for (int i = 2; i <= 2000; ++i) {
        sum[i] = (sum[i-1] + F[i]) % MOD;
    }
    
    int T, N;
    cin >> T;
    while (T-- > 0) {
        cin >> N;
        N >>= 1;
        cout << sum[N] << endl;
    }

    return 0;
}
