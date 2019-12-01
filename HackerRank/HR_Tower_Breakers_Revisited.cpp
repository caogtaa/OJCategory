#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN    1000000
// int H[100];
int V[MAXN+1];
vector<int> prime;
bool unprime[MAXN+1];

void initPrime()
{
    int i;
    int base;
    int cc = (int)sqrt(MAXN * 1.0);
    unprime[1] = true;
    for (i = 2; i <= cc; i++){
        if (unprime[i])
            continue;

        base = i * i;
        while (base <= MAXN){
            unprime[base] = true;
            base += i;
        }
    }
}

// 因式分解，因数个数（除1之外）就是Nim堆的大小，归纳为经典Nim游戏求解
int main() {
    initPrime();
    for (int i = 2; i <= MAXN; ++i) {
        if (!unprime[i])
            prime.push_back(i);
    }
    
    for (int i = 2; i <= MAXN; ++i) {
        if (!unprime[i])
            V[i] = 1;
            
        for (auto p : prime) {
            if ((long long)i * p <= MAXN)
                V[i*p] = V[i] + 1;
            else
                break;
        }
    }
        
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        int nimNum = 0;
        for (int i = 0; i < N; ++i) {
            int H;
            cin >> H;
            nimNum ^= V[H];
        }
        
        if (nimNum > 0) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }
    }
    
    return 0;
}
