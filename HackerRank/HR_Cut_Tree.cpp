#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

// DP, 记忆化搜索
// 题意：有一颗N个节点的树(N <= 50)，扣出一棵子树使其和剩余部分最多有K条边相连(K <= 50)，求有多少棵这样的子树
// 思路：最多有K条边相连，可以简化成刚好有k条边相连(k = 0...K)
// 有k条边相连也可以看成是切断k条边
// 算法显然是DP，但是状态和转移过程不是这么简明，最后还是看了editorial才做出来，加上BFS过程出了个bug
// 将k分到子树中将是一个排列组合问题，对于比较扁平但是度较高的结构，复杂度极高。通过将子树拆分成当前focus的子树和剩余子树将问题简化。
// 令F(u, c, k, choose)为，“当前根节点是u，忽略左侧c个子树，在以u为根的树中还需要切k条边，u点本身的选中状态是choose”所对应的状态下，u树能够提取的不同子树个数
// 状态转移公式：
// 1. 当u点choose = true时
//    1.1 考虑切掉当前子树(序号c，被忽略的c个子树序号是0...c-1), 后续状态为 F(u, c+1, k-1, true)
//    1.2 考虑不切当前子树，并放e个切割任务在当前子树中(e = 0...k)，后续状态为 F(sub, 0, e, true)； 同时剩余子树的状态为 F(u, c+1, k-e, true)。根据组合性质两者相乘
// 2. 当u点choose = false
//    2.1 分配到c子树，选中节点c，u和c之间切一刀，即 F(sub, 0, k-1, true)
//    2.2 分配到c子树，不选中节点c，递归，即 F(sub, 0, k, false)

long long F[51][51][51][2];
vector<int> edge[51];
vector<int> children[51];
bool visited[51];
int N, K;

void BFS()
{
    visited[0] = true;
    vector<int> qu;
    qu.push_back(0);
    int cur = 0;
    while (cur < qu.size()) {
        for (auto nxt : edge[qu[cur]]) {
            if (visited[nxt])
                continue;
            
            visited[nxt] = true;
            children[qu[cur]].push_back(nxt);
            qu.push_back(nxt);
        }
        ++ cur;
    }
}

long long Func(int root, int ignore_children, int restk, bool choose)
{
    if (restk == 0)
        // root点选，则所有子节点选
        // root点不选，则所有子节点不选
        return 1LL;
    
    if (children[root].size() == 0) {
        // leaf node but restk > 0
        return 0LL;
    }
    
    if (ignore_children == children[root].size())
        return restk == 0 ? 1LL : 0LL;
    
    long long &ret = F[root][ignore_children][restk][choose];
    if (ret != -1)
        return ret;
    
    ret = 0LL;
    if (choose) {
        // 切掉当前子树，当前子树choose = false
        ret += Func(root, ignore_children+1, restk-1, choose);
        for (int e = 0; e <= restk; ++e) {
            // e 次切割分配在当前子树，restk - e次分割分配在剩余子树
            ret += Func(children[root][ignore_children], 0, e, true) * Func(root, ignore_children+1, restk-e, true);
        }
    } else {
        // ignore_children is always 0
        for (auto nxt : children[root]) {
            // 分配到nxt子树，root和nxt之间切一刀
            ret += Func(nxt, 0, restk-1, true);
            // 分配到nxt子树，nxt子树自己也不选择，递归
            ret += Func(nxt, 0, restk, false);
        }
    }
    
    return ret;
}

int main()
{
    scanf("%d %d", &N, &K);
    int from, to;
    for (int i = 1; i < N; ++i) {
        scanf("%d %d", &from, &to);
        -- from;
        -- to;
        
        edge[from].push_back(to);
        edge[to].push_back(from);
    }
    
    BFS();
    memset(F, -1, sizeof(F));
    long long result = 0LL;
    for (int i = 0; i <= K; ++i) {
        result += Func(0, 0, i, false);
        result += Func(0, 0, i, true);
    }
    printf("%lld\n", result);
    
    return 0;
}
