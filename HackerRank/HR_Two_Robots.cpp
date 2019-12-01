#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP
// 题意：有M个袋子排成一排，相邻袋子之间距离是1，每个袋子里有无限个糖果。有两个机器人可搬运糖果。现有N个query，要求从Ma袋子搬运一颗糖果到Mb袋子，必须按顺序执行，求最佳调度方式下，两个机器人需要行走的距离总和最小是多少。1 <= M, N <= 1000
// 思路：根据题目规模算法复杂度应该是O(N^2)
// F[i][k]表示robot_1处理最后一个任务是i，robot_2处理最后一个任务是k，所用的最少时间
// 题目所求是min(min(F[Q][k]), min(F[k][Q])) [k=0...Q-1]
// 状态转移有两种情况：
// 1. F[i][k]中 i >= k-2，很显然robot_2处理了query k，robot_1处理了query i-1和query i，所以F[i][k]很容易从F[i-1][k]中酸楚
// 2. F[i][k]中 i == k-1，不容易知道最优情况下robot_1的上一个任务是哪个，所以F[i][k] = min(F[v][k]+delta(v,i)) [v=0...i-2]
// case 2计算一次是O(N)时间，但是case 2本身状态数量只有N个，所以时间复杂度是O(N^2)。除此之外的其余F[i][k]计算，每次是O(1)，状态数是N^2个，所以整体复杂度是O(N^2)
// 上述状态中同样有 k >= i-2和k == i-1的情况，所以F矩阵应该是对角线对称的，算法中没有针对这块进行优化，而是直接做了计算

#define MAXN    1000
int pos[MAXN+1];
int F[MAXN+1][MAXN+1];
pair<int, int> query[MAXN+1];

int Q, M;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &M, &Q);
        for (int i = 1; i <= Q; ++i) {
            scanf("%d %d", &query[i].first, &query[i].second);
        }
        
        F[0][1] = F[1][0] = abs(query[1].first - query[1].second);
        for (int i = 2; i <= Q; ++i) {
            // 全部给某一个robot处理
            F[0][i] = F[0][i-1] + abs(query[i-1].second - query[i].first) + abs(query[i].first - query[i].second);
            F[i][0] = F[0][i];
        }
        
        for (int i = 1; i <= Q; ++i) {
            for (int k = 1; k <= Q; ++k) {
                if (i == k)
                    // nerver happen
                    continue;
                
                if (k > i) {
                    if (k - i == 1) {
                        int best = F[i][0] + abs(query[k].first - query[k].second);
                        for (int v = k-2; v >= 1; --v) {
                            best = min(best, F[i][v] + abs(query[v].second - query[k].first) + abs(query[k].first - query[k].second));
                        }
                        F[i][k] = best;
                    } else {
                        F[i][k] = F[i][k-1] + abs(query[k-1].second - query[k].first) + abs(query[k].first - query[k].second);
                    }
                } else {    // i > k
                    if (i - k == 1) {
                        int best = F[0][k] + abs(query[i].first - query[i].second);
                        for (int v = i-2; v >= 1; --v) {
                            best = min(best, F[v][k] + abs(query[v].second - query[i].first) + abs(query[i].first - query[i].second));
                        }
                        F[i][k] = best;
                    } else {
                        F[i][k] = F[i-1][k] + abs(query[i-1].second - query[i].first) + abs(query[i].first - query[i].second);
                    }
                }
            }
        }
        
        int result = F[0][Q];
        for (int i = 1; i <= Q-1; ++i) {
            result = min(result, F[i][Q]);
            result = min(result, F[Q][i]);
        }
        printf("%d\n", result);
    }
    return 0;
}
