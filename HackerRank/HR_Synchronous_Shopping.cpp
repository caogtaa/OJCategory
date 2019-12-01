#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

// Dijkstra，最短路径
// 题意：有N个购物中心(N <= 1000)，M条路将它们相连(M <= 2 * 1000)，每个购物中心有渔贩会卖K种鱼中的部分(K <= 10)
// 有两只猫从购物中心1出发买鱼，它们计划买齐K种鱼后在城市N会和，求它们所需的最短时间是多少
// 思路：虽然是Medium题但是被难到了，思路没有摆脱旧时Dijkstra的经典用法，以及分头行动两条路径的问题，看了editorial后收到启发
// 节点本身被扩展成<nodeID, bitMask>对，作为一个“虚拟节点”，dist[u][v]表示到达u点刚好持有v所花的最短时间
// 先求点1到所有虚拟节点的距离，然后挑选出点1到点N的所有距离，求最终结果
// 算法过程和Dijkstra一样，设<1, mask[1]>为源点，开始松弛路径。使用小顶堆加速“最近点”的获取，堆元素结构为<距离，<nodeID, bitMask>>
// dist[N][v]表示到达N点时持有v所花的最短时间，表示的是一只猫可以选择的路径，暴力两两取出or操作，如果mask满足(2^k)-1则所有鱼都买齐
// 算法复杂度editorial里说是 O(MlogN*(2^k))，但是我觉得有点问题。节点被扩展成 N*(2^k)个虚拟结点后，边数量本身也变多了，是M*(2^k)。整体复杂度应该是O(M*(2^k)*log(N*(2^k)))，最大数量级是 1000 * 1000 * log(1000 * 1000) = 20e6，勉强过关

#define MAXN    1000
#define MAXMASK 1024

const long long INF = 1000000000000000000LL;
set<pair<long long, pair<int ,int>>> qu;
long long dist[MAXN+1][MAXMASK+1];
vector<pair<int, int>> edge[MAXN+1];
int N, M, K;
int mask[MAXN+1];

int main()
{
    scanf("%d %d %d", &N, &M, &K);
    
    // N lines node fish info
    for (int i = 1; i <= N; ++i) {
        int fish_count;
        int fish_index;
        scanf("%d", &fish_count);
        while (fish_count--) {
            scanf("%d", &fish_index);
            mask[i] |= (1 << (fish_index-1));
        }
    }
    
    // M lines road info
    int from, to, len;
    for (int i = 1; i <= M; ++i) {
        scanf("%d %d %d", &from, &to, &len);
        edge[from].push_back(make_pair(to, len));
        edge[to].push_back(make_pair(from, len));
    }
    
    // initialize dist
    int mask_full = (1 << K) - 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= mask_full; ++j) {
            dist[i][j] = INF;
        }
    }
    
    // start relaxing
    dist[1][0] = 0;
    dist[1][mask[1]] = 0;
    qu.insert(make_pair(0, make_pair(1, mask[1])));
    while (qu.size() > 0) {
        auto cost = qu.begin()->first;
        auto info = qu.begin()->second; // info = <nodeID, bitMask>
        qu.erase(qu.begin());
        
        for (const auto &p : edge[info.first]) {    // p = <nodeID, roadLen>
            auto nxtNode = p.first;
            auto nxtMask = mask[p.first] | info.second;
            if (dist[nxtNode][nxtMask] <= cost + p.second) {
                continue;
            }
            
            if (dist[nxtNode][nxtMask] == INF) {
                // do insert
                qu.insert(make_pair(cost + p.second, make_pair(nxtNode, nxtMask)));
            } else {
                // find current info in qu, erase, update and re-insert
                pair<long long, pair<int, int>> existing_p = make_pair(dist[nxtNode][nxtMask], make_pair(nxtNode, nxtMask));
                auto iter = qu.find(existing_p);
                if (iter != qu.end())
                    qu.erase(iter);

                existing_p.first = cost + p.second;
                qu.insert(existing_p);
            }
            dist[nxtNode][nxtMask] = cost + p.second;
        }
    }
    
    long long result = INF;
    for (int i = 0; i <= mask_full; ++i) {
        if (dist[N][i] == INF)
            continue;
        
        for (int j = 0; j <= mask_full; ++j) {
            if (dist[N][j] == INF)
                continue;
            
            if ((i | j) < mask_full)
                continue;
            
            result = min(result, max(dist[N][i], dist[N][j]));
        }
    }
    printf("%lld\n", result);
    
    return 0;
}
