#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define MAXN    100000

int G[MAXN+1];
vector<int> D[MAXN+1];
vector<int> buff;

// initialize divisiors of [1, MAXN], using sieve
void initDivisor() {
    for (int i = 1; i <= MAXN; ++i) {
        for (int k = i; k <= MAXN; k += i) {
            D[k].push_back(i);
        }
    }
}

int MEX(int v) {
    buff.resize(0);
    for (auto d : D[v]) {
        // divide into d parts, each part have size v/d
        if (d & 1)
            buff.push_back(G[v/d]);
        else
            buff.push_back(0);
    }
    
    buff.push_back(-1); // guarder, we want 1st element to be 0
    sort(buff.begin(), buff.end());
    for (int i = 1; i < (int)buff.size(); ++i) {
        if (buff[i-1] + 1 < buff[i])
            return buff[i-1] + 1;   // buff is not consecutive, found MEX
    }
    
    return buff.back() + 1;
}

// calculate grund number of [1,MAXN] for this game
void makeGrund() {
    // G[0] = G[1] = 0, loose position
    for (int i = 2; i <= MAXN; ++i) {
        G[i] = MEX(i);
    }
}

int main()
{
    initDivisor();
    makeGrund();
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        int H;
        int grund = 0;
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> H;
            grund ^= G[H];
        }
        
        if (grund > 0) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }
    }
    
    return 0;
}
