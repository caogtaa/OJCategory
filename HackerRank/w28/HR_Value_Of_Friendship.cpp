#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <utility>

using namespace std;


#define MAXN    100000
long long sum[MAXN+10];
vector<int> edges[MAXN+10];
bool visited[MAXN+10];
vector<int> nodes;
int queue[MAXN+10];

vector<pair<long long, long long>> resultCache;

int Q;
int N, M;

void BFS(int node)
{
    int qlen = 0;
    nodes.resize(0);
    queue[qlen++] = node;
    visited[node] = true;
    nodes.push_back(node);
    
    int cur = 0;
    while (cur < qlen) {
        node = queue[cur];
        for (auto nxt : edges[node]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                nodes.push_back(nxt);
                queue[qlen++] = nxt;
            }
        }
        
        ++ cur;
    }
}

int main()
{
    sum[0] = 0;
    for (int i = 1; i <= MAXN; ++i) {
        sum[i] = sum[i-1] + (1LL + i) * i;
    }

    scanf("%d", &Q);
    while (Q--) {
        scanf("%d %d", &N, &M);
        for (int i = 1; i <= MAXN; ++i) {
            edges[i].resize(0);
        }
        
        int x, y;
        for (int i = 0; i < M; ++i) {
            scanf("%d %d", &x, &y);
            edges[x].push_back(y);
            edges[y].push_back(x);
        }
        
        memset(visited, 0, sizeof(visited));
        resultCache.resize(0);
        for (int i = 1; i <= N; ++i) {
            if (!visited[i]) {
                BFS(i);
                
                // find how many edges in nodes
                long long nodeCount = nodes.size();
                long long totalEdgeCount = 0LL;
                for (auto node : nodes) {
                    totalEdgeCount += edges[node].size();
                }
                totalEdgeCount /= 2;
                
                resultCache.push_back(make_pair(nodeCount, totalEdgeCount));
            }
        }
        
        sort(resultCache.begin(), resultCache.end(), [](const pair<long long, long long> &p1, const pair<long long, long long> &p2) {
            return p1.first > p2.first;
        });

        long long result = 0LL;
        long long tmp = 0LL;
        long long rest = 0LL;
        for (const auto &p : resultCache) {
            long long nodeCount = p.first;
            long long totalEdgeCount = p.second;
            // result += tmp * totalEdgeCount;
            // result += sum[nodeCount-1] + ((long long)(totalEdgeCount - nodeCount+1)) * (nodeCount - 1) * nodeCount;
            result += tmp * (nodeCount-1);
            result += sum[nodeCount-1];
            rest += totalEdgeCount - nodeCount + 1;
            tmp += (nodeCount - 1) * nodeCount;
        }
        result += tmp * rest;
        
        printf("%lld\n", result);
    }
    
    return 0;
}
