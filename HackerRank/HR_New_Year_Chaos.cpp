#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int C[100001];
int V[100001];


int T, N;

inline int LowBit(int x){
    return x & (x^(x-1));
}

void Change(int k, int delta){
    while( k<=N ){
        C[k] += delta;
        k += LowBit(k);
    }
}

int Getsum(int k){
    int ret = 0;
    while( k>0 ){
        ret += C[k];
        k -= LowBit(k);
    }
    return ret;
}

void Solve()
{
    memset(C, 0, sizeof(int) * (N+1));
    int reserve = 0;
    int result = 0;
    for (int i = N-1; i >= 0; --i) {
        reserve = Getsum(V[i]-1);
        if (reserve > 2) {
            printf("Too chaotic\n");
            return;
        }
        
        Change(V[i], 1);
        result += reserve;
    }
    
    printf("%d\n", result);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", V+i);
        }
        
        Solve();
    }
    return 0;
}
