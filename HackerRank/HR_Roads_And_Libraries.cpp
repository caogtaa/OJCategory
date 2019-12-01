#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define MAXN   100000

// BFS
// if costL <= costR, build one library for each city
// otherwise, build as less libraries as possible.
// BFS to find components, for component with N node, build N-1 roads and 1 library

int Q;
int C, R;
long long costL, costR;
vector<int> edges[MAXN+1];
bool visited[MAXN+1];

int BFS(int root)
{
    visited[root] = true;
    vector<int> qu;
    qu.push_back(root);
    int result = 1;
    int cur = 0;
    while (cur < qu.size()) {
        int node = qu[cur];
        for (auto nxt : edges[node]) {
            if (visited[nxt])
                continue;
            
            visited[nxt] = true;
            qu.push_back(nxt);
            ++ result;
        }
        ++ cur;
    }
    
    return result;
}

int main() {
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d %d %lld %lld", &C, &R, &costL, &costR);
        
        // clear previous state
        memset(visited, 0, sizeof(bool) * C);
        for (int i = 0; i < C; ++i) {
            edges[i].resize(0);
        }

        int from, to;
        for (int i = 0; i < R; ++i) {
            scanf("%d %d", &from, &to);
            -- from;
            -- to;
            edges[from].push_back(to);
            edges[to].push_back(from);
        }
        
        if (costL <= costR) {
            printf("%lld\n", costL * C);
            continue;
        }
        
        long long result = 0;
        for (int i = 0; i < C; ++i) {
            if (visited[i])
                continue;
            
            int sz = BFS(i);
            result += costR * (sz-1) + costL;
        }
        
        printf("%lld\n", result);
    }

    return 0;
}
