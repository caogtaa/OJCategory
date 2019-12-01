//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <set>

using namespace std;

long long F[10000];

long long SG(long long v)
{
    long long &ret = F[v];
    if (ret == -1) {
        set<long long> nxt;
        nxt.insert(v);  // remove canZero
        nxt.insert(0);
        for (long long i = 1; i < v; ++i) {
            nxt.insert(SG(i));
        }
        
        long long mex = 0;
        for (auto iter = nxt.begin(); iter != nxt.end(); ++iter, ++mex) {
            if (*iter != mex)
                break;
        }
        
        ret = mex;
    }
    
    return ret;
}

int main()
{
//    memset(F, -1, sizeof(F));
//    F[0] = 0;
//    SG(100);
//    
//    for (int i = 0; i < 100; ++i) {
//        printf("%lld\n", F[i]);
//    }
//
//    return 0;
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        long long SG = 0LL;
        long long A;
        scanf("%d", &N);
        while (N--) {
            scanf("%lld", &A);
            SG ^= ((A & 1) ? A + 1 : A - 1);
        }
        
        if (SG > 0)
            printf("W\n");
        else
            printf("L\n");
    }
    
    return 0;
}
