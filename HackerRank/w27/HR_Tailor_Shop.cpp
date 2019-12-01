//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAXN    100000

long long A[MAXN+1];
long long C[MAXN+1];
int N, P;

int main()
{
    scanf("%d %d", &N, &P);
    for (int i = 0; i < N; ++i) {
        scanf("%lld", A+i);
        A[i] = A[i] / P + (A[i] % P > 0);
        ++ C[A[i]];
    }
    
    long long result = 0LL;
    long long rest = 0LL;
    for (int i = 1; i <= MAXN || rest > 0; ++i) {
        if (i > MAXN || (i <= MAXN && C[i] == 0 && rest > 0)) {
            -- rest;
            result += i;
        } else if (C[i] > 1) {
            rest += C[i]-1;
            C[i] = 1;
            result += i;
        } else if (C[i] == 1) {
            result += i;
        }
    }
    
    printf("%lld\n", result);
    return 0;
}