//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

/*
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _ O O _ O _ O _
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O O O O _ _ _ O
 O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O _ _ O O _ O O
 */
/*
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O _ _ O _ O _ O
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
 O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _ _ _ _ O O O _
 _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _ O O _ _ O _ _
 */

using namespace std;

#define MAXN    2000
#define SOME    2000

// int H[MAXN+1];
bool MAT[SOME+10][SOME+10];
int N, Q;

int main()
{
    //    H[1] = 1;
    //    H[2] = 2;
    //    H[3] = 3;
    //    for (int i = 4; i <= MAXN; ++i) {
    //        H[i] = H[i-1] + 2*H[i-2] + 3*H[i-3];
    //        H[i] %= 10000;
    //    }
    
    scanf("%d %d", &N, &Q);
    if (N % 7 == 6) {
        // optimize
        int v;
        for (int i = 0; i < Q; ++i) {
            scanf("%d", &v);
            printf("0\n");
        }
        
        return 0;
    }
    
    pair<int, int> offset[12] = {
        {0, 0}, {0, 5},
        {1, 2}, {1, 3},
        {2, 1}, {2, 4},
        {3, 1}, {3, 4},
        {4, 2}, {4, 3},
        {5, 0}, {5, 5}
    };
    
    for (int i = 0; i < N; i += 7) {
        for (int k = 0; k < N; k += 7) {
            for (const auto &p : offset) {
                MAT[i+p.first][k+p.second] = true;
            }
        }
    }
    
    for (int i = 6; i < N; i += 7) {
        for (int k = 0; k < N; ++k) {
            MAT[i][k] = true;
        }
    }
    
    for (int k = 6; k < N; k += 7) {
        for (int i = 0; i < N; ++i) {
            MAT[i][k] = true;
        }
    }
    
    // 90 deg
    long long result90 = 0;
    long long result180 = 0;
    long long result270 = 0;
    
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            if (MAT[i][k] != MAT[k][N-i-1]) {
                ++ result90;
            }
            if (MAT[i][k] != MAT[N-i-1][N-k-1]) {
                ++ result180;
            }
            if (MAT[i][k] != MAT[N-k-1][i]) {
                ++ result270;
            }
        }
    }
    
    int v;
    for (int i = 0; i < Q; ++i) {
        scanf("%d", &v);
        v %= 360;
        if (v == 0)
            printf("0\n");
        else if (v == 90)
            printf("%lld\n", result90);
        else if (v == 180)
            printf("%lld\n", result180);
        else
            printf("%lld\n", result270);
    }
    //
    //    for (int i = 0; i < N; ++i) {
    //        for (int k = 0; k < N; ++k) {
    //            if (MAT[i][k])
    //                printf("O ");
    //            else
    //                printf("_ ");
    //            // printf("%c ", MAT[i][k]);
    //        }
    //        printf("\n");
    //    }
    
    return 0;
}
