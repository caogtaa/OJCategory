#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 线段树，Merge Sort Tree, MST
// 题意：一个数组有N个元素(N <= 1e5), 现有Q个query(Q <= 5000), 每个query查询数组[L, R]区间内第K大的数字
// 思路：构造MST，MST的结构类似线段树，每个节点保存所有孩子元素排序后的数组，使用归并排序进行处理。空间要求O(NlogN)，排序时间O(NlogN)
// 对于每个query，查询过程如下：
// 1. 对数组N排序
// 2. 猜想[L, R]范围内第K大的数字是X，X的取值通过二分从排序后的数组中获取
// 3. 在线段树内查询[L, R]范围内 <=X 的元素个数，在本节点内vector二分查找(如果范围匹配)或者在子节点查找，深度O(logN)，查询复杂度O(logN)
// 4. 如果step-3 查出 <= X的元素个数count < K，说明X取值太小，返回step-2对右半部进行二分猜想；如果count >= K则对左半部进行二分猜想；需要注意的是即使count == K不能说明X就是所求的数字，因为X可能压根不在[L, R]区域内。距离[L, R]区域是[5 2 7 3]，第3大的数字是5，但是猜想是6时，同样有 <= 6的数字个数=3。过程类似lower_bound，step-2需要跑满logN次
// 整体复杂度 O(NlogN + Q*logN*logN*logN)

#define MAXN    100000
int N, Q;
int A[MAXN];
int sorted_A[MAXN];

struct Node{
    int m_sp, m_ep;
    Node* m_pl;
    Node* m_pr;
    vector<int> m_arr;
    void Construct(int sp, int ep);
    int Count_Number_LE_Than_V(int sp, int ep, int v);
};

Node STree[MAXN * 2];
int treesize;

void Node::Construct(int sp, int ep){
    m_sp = sp;
    m_ep = ep;
    if(sp+1 == ep){
        m_pl = NULL;
        m_pr = NULL;
        m_arr.push_back(A[sp]);
        return;
    }
    int mid = (sp+ep)>>1;
    m_pl = &STree[treesize++];
    m_pr = &STree[treesize++];
    
    m_pl->Construct(sp, mid);
    m_pr->Construct(mid, ep);
    
    // merge sort
    int lenl = (int)m_pl->m_arr.size();
    int lenr = (int)m_pr->m_arr.size();
    m_arr.reserve(lenl + lenr);
    std::merge(m_pl->m_arr.begin(), m_pl->m_arr.end(), m_pr->m_arr.begin(), m_pr->m_arr.end(), back_inserter(m_arr));
}

int Node::Count_Number_LE_Than_V(int sp, int ep, int v)
{
    if (sp == m_sp && ep == m_ep) {
        return (int)(upper_bound(m_arr.begin(), m_arr.end(), v) - m_arr.begin());
    }
    
    int result = 0;
    if (sp < m_pl->m_ep) {
        result += m_pl->Count_Number_LE_Than_V(sp, std::min(ep, m_pl->m_ep), v);
    }
    
    if (ep > m_pr->m_sp) {
        result += m_pr->Count_Number_LE_Than_V(std::max(sp, m_pr->m_sp), ep, v);
    }
    
    return result;
}

int solve(int L, int R, int K)
{
    int lft = 0, rit = N;
    int mid;
    while (lft < rit) {
        mid = (lft + rit) >> 1;
        auto v = sorted_A[mid];
        auto count = STree[0].Count_Number_LE_Than_V(L, R, v);
        if (count < K) {
            // number too small
            lft = mid + 1;
        } else {
            rit = mid;
        }
    }
    
    return sorted_A[lft];
}

int main()
{
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", A+i);
        sorted_A[i] = A[i];
    }
    
    sort(sorted_A, sorted_A+N);
    
    treesize = 1;
    STree[0].Construct(0, N);
    int L, R, K;
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d", &L, &R, &K);
        -- L;
        printf("%d\n", solve(L, R, K));
    }
    
    return 0;
}
