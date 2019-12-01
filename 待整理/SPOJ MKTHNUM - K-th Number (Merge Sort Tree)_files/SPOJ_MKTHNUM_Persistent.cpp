#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 主席树，Persistent Segment Tree
// 题意：一个数组A有N个元素(N <= 1e5), 现有Q个query(Q <= 5000), 每个query查询数组[L, R]区间内第K大的数字
// 思路（解法2）：
// 创建一个计数用数组B，长度和A相同，B[i] = 1时，表示A[i]元素已经出现
// 在数组B上建立线段树，按照A[i]数字从小到大顺序更新B的相应位置，总共会更新N次；初始状态B = [0,0,...,0], 更新N次后B = [1,1,...,1]
// 线段树上支持查询Count(L, R)，返回sigma(B[i]) [i=L...R]，即对[L, R]区间内的元素进行计数，看有多少元素已经出现
// 比如对于数组 A=[3,2,1,4]
//    第一次更新后B=[0,0,1,0], Count(1,2)=0, Count(1,3)=1
//    第二次更新后B=[0,1,1,0], Count(1,2)=1, Count(1,3)=2
// 线段树总共更新N次，假如我们能够访问任意一次更新(设为第K次)后Count(L, R)的值，就能够使用二分法确定使Count(L, R) == X的K值，即线段树在进行完第K次更新后，刚好使Count(L, R) == X，即[L, R]区域内刚好有X个数字出现过。这个时候，我们可以判定第K次更新的数字，就是在[L, R]区域内第X大的数字
// 所得即题目的Q(L, R, X)
// 如何能够访问任意一次更新后的线段树？
// 使用Persistent Segment Tree，可在O(NlogN)的时间和空间复杂度内，完成对线段树各版本的记录。所有版本的入口记录在root[]数组中，root[0]表示未更新的线段树入口，即B = [0,0,...,0]，root[1]表示更新一次后的线段树入口
// 一次Query需要进行二分猜测K值，O(logN)；每次猜测后需要O(logN)时间计算Count
// 整体复杂是 O(NlogN + M * logN * logN)

#define MAXN    100000
int N, Q;
int A[MAXN];
int sorted_A_index[MAXN];   // sorted_A_index[0] is the index of 0th element in A

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
    int lft = 0, rit = N;
    int mid;    // mid is the Tth update, access root[mid+1]
    while (lft < rit) {
        mid = (lft + rit) >> 1;
        auto count = root[mid+1].query(L, R);
        if (count < K) {
            // number too small
            lft = mid + 1;
        } else {
            rit = mid;
        }
    }
    
    return A[sorted_A_index[lft]];
}

int main()
{
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", A+i);
        sorted_A_index[i] = i;
    }
    
    sort(sorted_A_index, sorted_A_index+N, [](int idx1, int idx2) {
        return A[idx1] < A[idx2];
    });
    
    nodes.reserve(MAXN * 19);
    root[0].construct(0, N);
    
    for (int i = 1; i <= N; ++i) {
        root[i] = root[i-1];
        root[i].update(sorted_A_index[i-1]);
    }

    int L, R, K;
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d", &L, &R, &K);
        -- L;
        printf("%d\n", solve(L, R, K));
    }
    
    return 0;
}
