/*
题意：给出一个数字N，求使得x*a+y*b=N成立，并a<b及a,b,x,y均为整数的不同(a,b)对的数量。N <= 3*10^5
一开始一直纠结没有低复杂度的算法，尝试了感觉会TLE的算法，并进行了优化最后判定是一道需要优化算法常数的题目
思路：先计算出N以内所有数的除数，复杂度O(NlogN)。两重循环枚举a、x，在每个迭代里令B=y*b，我们需要找的是B的除数中大于a的。在a的循环里可能会遇到相同的b，中间需要去重复。
*/

//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <string.h>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define MAXN    300000

int G[MAXN+1];
vector<int> D[MAXN+1];

int visited[MAXN+1];

unordered_set<long long> cache;

//bool unprime[MAXN+1];
//vector<int> prime;
//
//void initPrime()
//{
//    int i;
//    int base;
//    int cc = (int)sqrt(MAXN * 1.0);
//    unprime[1] = true;
//    for (i = 2; i <= cc; i++){
//        if (unprime[i])
//            continue;
//        
//        base = i * i;
//        while (base <= MAXN){
//            unprime[base] = true;
//            base += i;
//        }
//    }
//    
//    for (int i = 2; i <= MAXN; ++i)
//        if (!unprime[i])
//            prime.push_back(i);
//}

// initialize divisiors of [1, MAXN], using sieve
void initDivisor(int N)
{
    // totally 3,829,833 for 3*10^5
    //long long some = 0LL;
    for (int i = 1; i <= N; ++i) {
        for (int k = i; k <= N; k += i) {
            D[k].push_back(i);
            //++ some;
        }
    }
}


long long solve_1(int A, int B)
{
    int DAN = (int)D[A].size();
    int DBN = (int)D[B].size();
    int i = 0, k = 0;
    
    long long result = 0LL;
    while (k < DBN && D[B][k] <= D[A][i]) {
        // find 1st DB > DA
        ++ k;
    }
    
    while (k < DBN) {
        while (i < DAN-1 && D[A][i+1] < D[B][k]) {
            ++ i;
        }
        
        result += i+1;
        ++k;
    }
    
    return result;
}

void solve_2(int A, int B)
{
    // totally loops 77,989,696 for 3*10^5
    // 2 nest loops
    int DAN = (int)D[A].size();
    int DBN = (int)D[B].size();
    int i = 0, k = 0;

    long long check;
    for (i = 0; i < DAN; ++i) {
        for (k = 0; k < DBN; ++k) {
            if (D[A][i] < D[B][k]) {
                check = (((long long)D[A][i]) << 32) + D[B][k];
                cache.insert(check);
            }
        }
    }
}

void solve_3(int A, int B)
{
    int DAN = (int)D[A].size();
    int DBN = (int)D[B].size();
    int i = 0, k = 0;
    
    long long check;
    int DBk;
    int DAi;
    for (k = 0; k < DBN; ++k) {
        DBk = D[B][k];
        for (i = 0; i < DAN; ++i) {
            DAi = D[A][i];
            if (DAi >= DBk)
                break;

            check = (((long long)DAi) << 32) + DBk;
            cache.insert(check);
        }
    }
}

int main()
{
    // initPrime();
    
    int N;
    cin >> N;
    auto start = system_clock::now();
    initDivisor(N);
    
//    auto end1   = system_clock::now();
//    auto dur1 = duration_cast<milliseconds>(end1 - start);
//    cout << dur1.count() << endl;
    
//    long long result = 0LL;
//    int B;
//    for (int A = 1; A <= N; ++A) {
//        B = N - A;
//        // result += solve(A, B);
//        solve_2(A, B);
//        // solve_3(A, B);
//    }
//    
//    //cout << result;
//    cout << cache.size();
    
    long long result = 0LL;
    int A;
    int B;
    int k;
    int *p = nullptr;
    for (int a = 1; a < N; ++a) {
        for (A = a; A < N; A += a) {
            B = N - A;
//            for (k = (int)D[B].size() - 1; k >= 0 && D[B][k] > a; --k) {
//                if (visited[D[B][k]] != a) {
//                    visited[D[B][k]] = a;
//                    ++ result;
//                }
//            }
            for (p = &D[B].back(); p >= &D[B][0] && *p > a; --p) {
                if (visited[*p] != a) {
                    visited[*p] = a;
                    ++ result;
                }
            }
//            for(int k=1;k<=sqrt(B);k++)
//            {
//                if(B%k == 0)
//                {
//                    if(k > a && visited[k] != a) {
//                        ++result;
//                        visited[k] = a;
//                    }
//                    long long l = B/k;
//                    if(l != k && l > a && visited[l] != a) {
//                        visited[l] = a;
//                        ++result;
//                    }
//                }
//            }
        }
    }
    
    cout << result;
    auto end   = system_clock::now();
    auto dur = duration_cast<milliseconds>(end - start);
    cout << endl << dur.count();
    cout << endl << duration<double>(dur).count() << endl;
    return 0;
    
    // best 1.454
    // best 1.34 for pointer access
}

/*1000
12817

1001
9507

10000
235955

300000
16274455*/


//long long gcd(long long a, long long b)
//{
//    while(b != 0)
//    {
//        long long r = b;
//        b = a % b;
//        a = r;
//    }
//    return a;
//}
//
//long long exgcd(long long m, long long n, long long &x, long long &y)
//{
//    long long x1,y1,x0,y0;
//    x0=1; y0=0;
//    x1=0; y1=1;
//    x=0; y=1;
//    long long r=m%n;
//    long long q=(m-r)/n;
//    while(r)
//    {
//        x=x0-q*x1; y=y0-q*y1;
//        x0=x1; y0=y1;
//        x1=x; y1=y;
//        m=n; n=r; r=m%n;
//        q=(m-r)/n;
//    }
//    return n;
//}
//
//bool linear_equation(long long a, long long b, long long c, long long &x, long long &y)
//{
//    long long d=exgcd(a,b,x,y);
//    if(c%d)
//        return false;
//    long long k=c/d;
//    x*=k; y*=k;
//    return true;
//}
//
//int main()
//{
//    int N;
//    long long A, B;
//    long long x, y;
//    
//    cin >> N;
//    //cin >> N >> A >> B;
//    //linear_equation(A, B, N, x, y);
//    
//    long long result = 0;
//    for (A = 1; A < N; ++A) {
//        for (B = A+1; B < N; ++B) {
//            if (!linear_equation(A, B, N, x, y))
//                continue;
//            
//            long long g = abs(gcd(A, B));
//            long long bng = B / g;
//            long long ang = A / g;
//            long long t;
//            if (x > 0) {
//                t = x / bng;
//                if (x % bng == 0)
//                    -- t;
//                x -= t * bng;
//                y += t * ang;
//            } else {
//                t = -x / bng;
//                ++ t;
//                x += t * bng;
//                y -= t * ang;
//            }
//            
//            if (x > 0 && y > 0)
//                ++ result;
//        }
//    }
//    
//    cout << result;
//    return 0;
//}
