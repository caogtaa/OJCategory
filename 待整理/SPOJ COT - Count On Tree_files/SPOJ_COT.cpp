#pragma comment(linker, "/STACK:1024000000,1024000000")

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

// Persistent Segment Tree, 主席树
// 题意：有一棵N个节点的树(N <= 1e5)，每个节点有值Ai，Ai可重复出现。Q个请求，f(u, v, k)求u->v路径上第k小的数字
// 思路：首先对A进行压缩得到B，因为Ai可重复，所以 BN = sizeof(B) <= sizeof(A)
// 在[0...BN)区间建立线段树，这个线段树记录当前已经出现的位序（比如第K大的数字已经出现，则Bk = 1)
// 树上每个节点分配一个上述线段树，按照DFS先序遍历树，每到一个节点时，“拷贝父节点的线段树”后将Ai的对应位序更新到该线段树上，作为本节点线段树
// 根据如上规则，节点u的线段树只会记录u到root路径上的位序。在这个线段树上求 <= X位序的数字个数，就是求root->u路径上 <= X位序的数字个数
// 设g(u, X)是root->u路径上 <= X位序的数字个数，G(u, v, X)是u->v路径上 <= X位序的数字个数
// G(u, v, X) = g(u, X) + g(v, X) - g(lca(u, v), X) - g(parent(lca(u, v)), X), 画个图比较容易get到
// 于是我们可以用二分法确定一个最小的X，使G(u, v, X) >= k，X就是u->v路径上第k小的位序
// 数据结构：
// 1. 每个节点上都有一棵线段树，并且和父节点的线段树只有一个count之差，用Persistent Segment Tree进行处理
// 2. lca(u, v)使用ST表O(NlogN)初始化后，O(1)时间查询
// 优化：
// 目前的初始化复杂度 O(NlogN)，查询 O(M * logN * logN)，查询部分可以优化
// 上述出现的4个g(u, X)，g(v, X), g(lca(u, v), X), g(parent(lca(u, v)), X)分别对应u, v, lca(u, v), parent(lca(u, v))点上的线段树，所有线段树的规模都是完全相同，如果我们将这4个线段树合并，得到就是一棵只有u->v路径上位序的线段树！在这棵线段树上可以直接求第k小的数字，时间复杂度O(logN)
// 优化后时间复杂度是<O(NlogN), O(MlogN)>

using namespace std;

#define MAXN    100000
int N, Q;
int A[MAXN];
vector<int> edges[MAXN];
map<int, int> compressed;
int kth_value[MAXN];

// for LCA
int ST[20][MAXN * 2];
int first_access_tm[MAXN];
int parent[MAXN];
int tm;

struct Node {
    int _sp, _ep;
    int _lft_idx;
    int _rit_idx;
    
    // data
    int _count;
    
    // function
    void construct(int sp, int ep);
    void update(int pos);
    int query(int X);
};

Node base_root;
Node root[MAXN];          // entrance of each segment tree, 1 root each update, plus original one
vector<Node> nodes;

void Node::construct(int sp, int ep)
{
    _sp = sp;
    _ep = ep;
    if(sp+1 == ep){
        _lft_idx = _rit_idx = -1;
        _count = 0;
        return;
    }
    
    _lft_idx = (int)nodes.size();
    _rit_idx = (int)nodes.size() + 1;
    nodes.resize(nodes.size() + 2);
    
    _count = 0;
    int mid = (sp+ep) >> 1;
    nodes[_lft_idx].construct(sp, mid);
    nodes[_rit_idx].construct(mid, ep);
}

void Node::update(int pos)
{
    if (_sp+1 == _ep) {
        // assert(_sp == pos);
        ++ _count;
        return;
    }
    
    int mid = (_sp+_ep) >> 1;
    if (pos < mid) {
        // create new left node
        nodes.resize(nodes.size() + 1);
        nodes.back() = nodes[_lft_idx];
        _lft_idx = (int)nodes.size()-1;
        nodes[_lft_idx].update(pos);
    } else {
        // create new right node
        nodes.resize(nodes.size() + 1);
        nodes.back() = nodes[_rit_idx];
        _rit_idx = (int)nodes.size()-1;
        nodes[_rit_idx].update(pos);
    }
    
    ++ _count;
}

// query numbers <= X (actually X is the numbers order)
int Node::query(int X)
{
    if (X < _sp || X >= _ep)
        return 0;

    if (_sp + 1 == _ep) {
        return _count;
    }
    
    // if (nodes[_lft_idx]._count >= X) {
    if (X < (_sp + _ep) >> 1) {
        return nodes[_lft_idx].query(X);
    }
    
    return nodes[_lft_idx]._count + nodes[_rit_idx].query(X);
}

void DFS(int node, int pre)
{
    // record access time
    first_access_tm[node] = tm;
    ST[0][tm++] = node;
    parent[node] = pre;
    
    root[node] = pre == -1 ? base_root : root[pre];
    root[node].update(compressed[A[node]]);
    for (int i = 0; i < (int)edges[node].size(); ++i) {
        int child = edges[node][i];
        if (child == pre)
            continue;
        
        DFS(child, node);
        ST[0][tm++] = node;
    }
}

int LCA(int from, int to)
{
    if (from == to)
        return from;
    
    int from_tm = first_access_tm[from];
    int to_tm = first_access_tm[to];
    if (from_tm > to_tm)
        swap(from_tm, to_tm);
    
    ++ to_tm;
    int len = to_tm - from_tm;
    int depth = (int)(log(len-1)/log(2.0));
    if (first_access_tm[ST[depth][from_tm]] < first_access_tm[ST[depth][to_tm-(1 << depth)]])
        return ST[depth][from_tm];
    
    return ST[depth][to_tm-(1 << depth)];
}

int solve_fast(int from, int to, int K)
{
    int lca = LCA(from, to);
    int lca_parent = parent[lca];
    Node *from_node = &root[from];
    Node *to_node = &root[to];
    Node *lca_node = &root[lca];
    Node *parent_node = (lca_parent == -1) ? NULL : &root[lca_parent];
    
    while (true) {
        if (from_node->_sp+1 == from_node->_ep)
            return kth_value[from_node->_sp];
        
        int lft_count =
            nodes[from_node->_lft_idx]._count +
            nodes[to_node->_lft_idx]._count -
            nodes[lca_node->_lft_idx]._count;
        
        if (parent_node)
            lft_count -= nodes[parent_node->_lft_idx]._count;
        
        if (lft_count >= K) {
            from_node = &nodes[from_node->_lft_idx];
            to_node = &nodes[to_node->_lft_idx];
            lca_node = &nodes[lca_node->_lft_idx];
            if (parent_node)
                parent_node = &nodes[parent_node->_lft_idx];
        } else {
            K -= lft_count;
            from_node = &nodes[from_node->_rit_idx];
            to_node = &nodes[to_node->_rit_idx];
            lca_node = &nodes[lca_node->_rit_idx];
            if (parent_node)
                parent_node = &nodes[parent_node->_rit_idx];
        }
    }
    
    return 0;   // never happen
}

int main()
{
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", A+i);
        compressed[A[i]];
    }
    
    int from, to;
    for (int i = 1; i < N; ++i) {
        scanf("%d %d", &from, &to);
        -- from;
        -- to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    
    // compress value to its order
    // because value may be same, so compressed.size() <= A.size()
    int id = 0;
    for (map<int, int>::iterator iter = compressed.begin(); iter != compressed.end(); ++iter) {
        kth_value[id] = iter->first;
        compressed[iter->first] = id++;
    }
    
    nodes.reserve(MAXN * 19);
    base_root.construct(0, (int)compressed.size());
    
    DFS(0, -1); // node 0 as root
    
    // build ST
    for (int depth = 1; depth < 20; ++depth) {
        int len = 1 << depth;
        for (int i = 0; i+len <= tm; ++i) {
            if (first_access_tm[ST[depth-1][i]] < first_access_tm[ST[depth-1][i+(len>>1)]]) {
                ST[depth][i] = ST[depth-1][i];
            } else {
                ST[depth][i] = ST[depth-1][i+(len>>1)];
            }
        }
    }
    
    int K;
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d", &from, &to, &K);
        -- from;
        -- to;
        printf("%d\n", solve_fast(from, to, K));
    }
    
    return 0;
}
