//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAXN    30

bool isPrime[10];
int compNumCount[MAXN][MAXN];   // number of composite number in rectangle (0,0)->(r,c)
int N;
int G[MAXN][MAXN][MAXN][MAXN];
int PAD[MAXN][MAXN];

inline int CN(int r, int c, int r2, int c2)
{
    if (r == 0 && c == 0)
        return compNumCount[r2][c2];
    
    if (r == 0)
        return compNumCount[r2][c2] - compNumCount[r2][c-1];
    
    if (c == 0)
        return compNumCount[r2][c2] - compNumCount[r-1][c2];
    
    return compNumCount[r2][c2] - compNumCount[r2][c-1] - compNumCount[r-1][c2] + compNumCount[r-1][c-1];
}

int Grundy(int r, int c, int r2, int c2) {
    int &ret = G[r][c][r2][c2];
    if (ret == -1) {
        if (CN(r, c, r2, c2) == 0) {
            ret = 0;
        } else {
            // tangtai.cgt: using bool array is much faster than using set/unordered_set
            bool visited[75];
            memset(visited, false, sizeof(visited));
            for (int rr = r; rr < r2; ++rr) {
                // horizontal cut
                visited[Grundy(r, c, rr, c2) ^ Grundy(rr+1, c, r2, c2)] = true;
            }

            for (int cc = c; cc < c2; ++cc) {
                // vertical cut
                visited[Grundy(r, c, r2, cc) ^ Grundy(r, cc+1, r2, c2)] = true;
            }
        
            ret = 0;
            for (int mex = 0; mex < 75; ++mex) {
                if (!visited[mex]) {
                    ret = mex;
                    break;
                }
            }
        }
    }
    
    return ret;
}

int main()
{
    isPrime[2] = isPrime[3] = isPrime[5] = isPrime[7] = true;
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        memset(G, -1, sizeof(G));
        int r, c;
        scanf("%d", &N);
        for (r = 0; r < N; ++r) {
            for (c = 0; c < N; ++c) {
                scanf("%d", &PAD[r][c]);
                G[r][c][r][c] = 0;
            }
        }
        
        // DP to fill primeCount
        // no need to initialize, new values always overwrite old values
        int r2, c2;
        
        compNumCount[0][0] = !isPrime[PAD[0][0]];
        for (r2 = 1; r2 < N; ++r2)
            compNumCount[r2][0] = compNumCount[r2-1][0] + !isPrime[PAD[r2][0]];
        
        for (c2 = 1; c2 < N; ++c2)
            compNumCount[0][c2] = compNumCount[0][c2-1] + !isPrime[PAD[0][c2]];
        
        for (r2 = 1; r2 < N; ++r2) {
            for (c2 = 1; c2 < N; ++c2) {
                compNumCount[r2][c2] = compNumCount[r2-1][c2] + compNumCount[r2][c2-1] - compNumCount[r2-1][c2-1] + !isPrime[PAD[r2][c2]];
            }
        }
        
        if (Grundy(0, 0, N-1, N-1) > 0) {
            printf("First\n");
        } else {
            printf("Second\n");
        }
    }
    
    return 0;
}
