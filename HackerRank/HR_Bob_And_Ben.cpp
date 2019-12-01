// Sprague-Grundy定理
// 题意：Bob Ben玩游戏。有N棵树，每次可以从一棵树上移除一个节点，如果移动的是叶子结点，剩下的结点可以继续玩，否则整棵树消失
// Bob先手，问最后谁能赢
// 计算单棵树在不同大小下的SG值:
// SG(0) = 0
// SG(1) = MEX(SG(0)) = 1
// SG(2) = MEX(SG(1), SG(1)) = 0  => 题目中叶子结点的定义是：只有一条边相连的点。所以两个节点的树所有点都是叶子
// SG(3) = MEX(SG(2), SG(0)) = MEX(0, 0) = 1
// SG(4) = MEX(SG(3), SG(0)) = MEX(1, 0) = 2
// SG(5) = MEX(SG(4), SG(0)) = MEX(2, 0) = 1
// SG(6) = 2， 后面开始 1 <-> 2循环
// XOR 所有树的SG值求得最重的SG值, SG > 0时先手胜

// 另：题目中的K纯粹是误导变量
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int SG(int M)
{
    if (M == 0)
        return 0;
    if (M == 1)
        return 1;
    if (M == 2)
        return 0;
   
    return (M & 1) ? 1 : 2;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        int M, K;
        int sg = 0;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &M, &K);
            sg ^= SG(M);
        }
       
        if (sg) {
            printf("BOB\n");
        } else {
            printf("BEN\n");
        }
    }
   
    return 0;
}