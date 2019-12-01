#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long A[1000000];
int N;

int main() {
    scanf("%d", &N);
    long long G = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%lld", A+i);
        G ^= A[i];
    }
    
    if (G == 0)
        printf("0\n");
    else {
        long long result = 0LL;
        for (int i = 0; i < N; ++i) {
            if ((A[i] ^ G) < A[i])
                ++ result;
        }
        
        printf("%lld\n", result);
    }
    
    return 0;
}
