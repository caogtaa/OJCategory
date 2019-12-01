#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int G[15][15];

pair<int, int> delta[4] = {
    {-2, 1},
    {-2, -1},
    {1, -2},
    {-1, -2}
};

int Grundy(int x, int y) {
    int &ret = G[x][y];
    if (ret == -1) {
        vector<int> S;
        int nx, ny;
        for (int i = 0; i < 4; ++i) {
            nx = x + delta[i].first;
            ny = y + delta[i].second;
            if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15)
                continue;
            
            S.push_back(Grundy(nx, ny));
        }
        
        
        S.push_back(-1);
        sort(S.begin(), S.end());
        
        ret = S.back() + 1;
        for (int i = 1; i < (int)S.size(); ++i) {
            if (S[i-1] + 1 < S[i]) {
                ret = S[i-1] + 1;
                break;
            }
        }
    }
    
    return ret;
}

int main() {
    memset(G, -1, sizeof(G));
    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;
        int x, y;
        int nimValue = 0;
        for (int i = 0; i < K; ++i) {
            cin >> x >> y;
            nimValue ^= Grundy(x-1, y-1);
        }
        
        if (nimValue > 0) {
            cout << "First" << endl;
        } else {
            cout << "Second" << endl;
        }
    }

    return 0;
}
