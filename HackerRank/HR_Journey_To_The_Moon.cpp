#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// BFS
// 题意：挑选一对宇航员上月球，要求两个宇航员来自不同国家
// 现有一批宇航员，并且只知道那些人来自同一个国家，求有多少种组合的可能性
// 思路：找出所有联通分量，对于每一个分量，如果分量大小是S，从该分量挑选出一个人的组合数是 S * (N-S)，枚举所有分量，最终结果/2去重

#define MAXN    100000
int N, P;
vector<int> sz; // size of each components
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
    scanf("%d %d", &N, &P);
    int from, to;
    for (int i = 0; i < P; ++i) {
        scanf("%d %d", &from, &to);
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    
    long long total = 0LL;
    for (int i = 0; i < N; ++i) {
        if (visited[i])
            continue;
        
        sz.push_back(BFS(i));
    }
    
    long long result = 0LL;
    for (int i = 0; i < (int)sz.size(); ++i) {
        result += (long long)sz[i] * (N-sz[i]);
    }

    printf("%lld\n", result / 2);
    return 0;
}
