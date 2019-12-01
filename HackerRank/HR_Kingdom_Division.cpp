#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN    100000
#define MOD     1000000007

int N;
vector<int> edges[MAXN+1];          // 边信息(双向)
vector<int> on_way_edge[MAXN+1];    // 双向边简化为单向边
bool visited[MAXN+1];
long long F[MAXN+1][2][2];
vector<int> top_order;

// 题意：
// 一棵树，每个节点要被染色，颜色有两种。要求每个节点相邻的节点中，至少有一个和自己颜色相同，求总共有多少种合法的染色方法

// 思路：
// 大致思路是，指定任意一个节点为根节点，先尝试自己染色，然后让子节点染色，转化成子问题。子节点染色的结果求解本节点的染色方法数
// 树型结构一般可用递归求解，但是由于节点个数较多(10W数量级)，所以采用广度优先遍历后，从后往前DP，减少栈开销
// 在计算顺序上和递归的深度优先计算不尽相同，但是能保证先计算孩子节点再计算父亲节点
// 令F[k][s][pres]为：在节点k上染色为s，其父节点已经被染色pres时，以k为根的整个子树能够有多少种选择
// 可以看出，当s = pres的时候，k下面的子节点自由度较高，可以染s或者!s  （F[k][s][pres] = 所有子节点的F排列组合, 代码中的total）
// 当s != pres的时候，k下面的子节点至少需要有一个颜色为s，以保证k点不被孤立   (F[k][s][pres]在total基础上减去所有子节点染色为!s的情况数）
// 边缘case:
// 1. 叶子节点必须要和其父亲染成相同颜色，否则会被孤立，所以F[k][0][0] = F[k][1][1] = 1
// 2. 整颗树的根节点root没有父亲节点，可以假设它有一个颜色不一样的父亲节点。题目所求即 F[1][0][1] + F[1][1][0]

void BFS()
{
    vector<int> queue;
    top_order.push_back(1);
    visited[1] = true;
    int pos = 0;
    
    while (pos < top_order.size()) {
        int node = top_order[pos];
        for (int nxt : edges[node]) {
            if (visited[nxt])
                continue;
            
            visited[nxt] = true;
            on_way_edge[node].push_back(nxt);
            top_order.push_back(nxt);
        }
        
        ++ pos;
    }
}

long long Solve()
{
    for (int i = (int)top_order.size() - 1; i >= 0; --i) {
        int node = top_order[i];
        const auto &children = on_way_edge[node];
        if (children.size() == 0) {
            F[node][0][0] = F[node][1][1] = 1;
            F[node][0][1] = F[node][1][0] = 0;
            continue;
        }
        
        for (bool s : {false, true}) {
            long long total = 1LL;
            // long long all_same = 1LL;
            long long all_diff = 1LL;
            
            for (auto child : children) {
                total = (total * (F[child][0][s] + F[child][1][s])) % MOD;
                // all_same = (all_same * F[child][s][1]) % MOD;
                all_diff = (all_diff * F[child][!s][s]) % MOD;
            }
            
            F[node][s][s] = total;
            F[node][s][!s] = total - all_diff;
            if (F[node][s][!s] < 0)
                F[node][s][!s] += MOD;

        }
    }
    
    return (F[1][0][1] + F[1][1][0]) % MOD;
}

int main() {
    scanf("%d", &N);
    int from, to;
    for (int i = 1; i < N; ++i) {
        scanf("%d %d", &from, &to);
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    
    // BFS to make top order for each node
    BFS();
    
    // reverse traverse top order to DP
    printf("%lld\n", Solve());
    return 0;
}
