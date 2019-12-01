/*
题意：直线上N个点，划分出N+1个区域。两个点之间的道路会播放音乐。一个人打算选择一个起点P，走M长度的路，走路过程中将听到不同的音乐，要求每种音乐最多听Hmax长度，最少听Hmin长度。输出任意一个可选的起点P。题目数据保证至少有一个可行解。
思路：如果A[x]和A[y]被M覆盖并且是两个端点，需要满足M-2*Hmax<=A[y]-A[x]<=M-2*Hmin，这个公式可以理解为，超出x点左侧和超出y点右侧的长度相加在[2*Hmin, 2*Hmax]范围内。线性查找满足这样性质的区域，在查找过程中如果发现两个点之间距离 < Hmin直接跳过。每找到满足上述性质的一个范围后，检测其左右两侧和附近点距离是否有足够空间能容纳超出端点的部分，满足后则用简单逻辑分配左右超出的部分，左侧端点-左侧超出部分长度就是P点位置

额外处理一个特殊情况，如果M<=Hmax，直接把P点设置在A[0]-Hmax处
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// https://www.hackerrank.com/contests/w26/challenges/street-parade-1
long long Hmin;
long long Hmax;
long long M;
int N;

long long A[1000000];

bool check(int sp, int ep)
{
    if (sp > 0) {
        long long lft = A[sp] - A[sp-1];
        if (lft < Hmin/* || Hmax < lft*/)
            return false;
    }
    
    if (ep < N-1) {
        long long rit = A[ep+1] - A[ep];
        if (rit < Hmin/* || Hmax < rit*/)
            return false;
    }
    
    return true;
}

void output(int sp, int ep)
{
    long long rest = M - (A[ep] - A[sp]);
    long long lft = rest - Hmin;
    if (lft > Hmax)
        lft = Hmax;

    if (sp > 0 && A[sp] - A[sp-1] < lft) {
        lft = A[sp] - A[sp-1];
    }
    
    cout << A[sp] - lft;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    
    cin >> M >> Hmin >> Hmax;
    if (M <= Hmax) {
        // listen to a single music
        cout << A[0] - Hmax;
        return 0;
    }
    
    long long X = M - 2 * Hmax;
    long long Y = M - 2 * Hmin;
    
    int sp = 0;
    int ep = 0;
    while (true) {
        // initialize ep to a state that cross >= X
        while (ep < N-1 && A[ep] - A[sp] < X) {
            ++ ep;
            if (A[ep]-A[ep-1] < Hmin || A[ep]-A[ep-1] > Hmax) { // now sure ep > sp and ep-1 >= sp
                sp = ep;
                ep = sp;
            }
        }
        
        // move ep until cross > Y
        bool skip = false;
        while (A[ep] - A[sp] <= Y) {
            // check solution
            if (check(sp, ep)) {
                output(sp, ep);
                return 0;
            }
            
            if (ep >= N-1)
                break;

            ++ ep;
            if (A[ep]-A[ep-1] < Hmin || A[ep]-A[ep-1] > Hmax) { // now sure ep > sp and ep-1 >= sp
                sp = ep;
                ep = sp;
                skip = true;
                break;
            }
        }
        
        if (skip) {
            // do nothing
        } else {
            // move sp by 1
            ++ sp;
            ep = max(sp, ep);
        }
    }
    
    
    return 0;
}

//}

