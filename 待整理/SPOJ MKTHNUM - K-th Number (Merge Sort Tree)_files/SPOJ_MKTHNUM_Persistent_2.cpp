#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 解法3：基于解法2，通过合并线段树优化查询时间，理论上查询时间复杂度从 O(M * logN * logN) 变成 O(M * logN)
// 但是可能由于compressed map的构造比较费事，运行反而增加了

#define MAXN    100000
int N, Q;
int A[MAXN];

map<int, int> compressed;
int kth_value[MAXN];

struct Node {
    int _sp, _ep;
    int _lft_idx;
    int _rit_idx;
    
    // data
    int _count;
    
    // function
    void construct(int sp, int ep);
    void update(int pos);
    int query(int sp, int ep);
};

Node root[MAXN+1];          // entrance of each segment tree, 1 root each update, plus original one
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

int Node::query(int sp, int ep)
{
    if (_sp == sp && _ep == ep)
        return _count;
    
    int mid = (_sp+_ep) >> 1;
    int result = 0;
    if (sp < mid) {
        result += nodes[_lft_idx].query(sp, min(mid, ep));
    }
    
    if (ep > mid) {
        result += nodes[_rit_idx].query(max(mid, sp), ep);
    }
    
    return result;
}

int solve(int L, int R, int K)
{
    Node *r = &root[R];
    Node *l = L <= 1 ? nullptr : &root[L-1];
    while (true) {
        if (r->_sp + 1 == r->_ep)
            return kth_value[r->_sp];
        
        int lft_count = nodes[r->_lft_idx]._count;
        if (l)
            lft_count -= nodes[l->_lft_idx]._count;
        
        if (lft_count >= K) {
            r = &nodes[r->_lft_idx];
            if (l)
                l = &nodes[l->_lft_idx];
        } else {
            K -= lft_count;
            r = &nodes[r->_rit_idx];
            if (l)
                l = &nodes[l->_rit_idx];
        }
    }
    
    return 0;
}

int main()
{
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", A+i);
        compressed[A[i]];
        // sorted_A_index[i] = i;
    }
    
    int id = 0;
    for (auto& iter : compressed) {
        kth_value[id] = iter.first;
        iter.second = id++;
    }
    
    
    nodes.reserve(MAXN * 19);
    root[0].construct(0, N);
    
    for (int i = 1; i <= N; ++i) {
        root[i] = root[i-1];
        root[i].update(compressed[A[i-1]]);
    }
    
    int L, R, K;
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d", &L, &R, &K);
        // root is 1-based
        printf("%d\n", solve(L, R, K));
    }
    
    return 0;
}
