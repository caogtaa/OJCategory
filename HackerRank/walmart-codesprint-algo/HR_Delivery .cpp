/*
题意: 在完全二叉树表示的图中送外卖。每个节点能生产一些食物，外卖小哥必须按照顺序从节点拿到对应食物然后送到目的地。节点个数N <= 10^5, 食物种类 M <= 10^4, 外卖单数量Q <= 10^5，同1种食物最多能在11个地方被生产
思路: 本题接近暴力方法，只要能快速求得完全二叉树中节点的距离即可
完全二叉树中两点x, y距离等于distance(x, lcp(x, y)) + distance(y, lcp(x, y)), 即路径经过公共祖先
如果用二进制观察x, y,  lcp(x,y)就是x,y二进制表达中的公共前缀
x和lcp之间的距离就是它们的depth差值，在二进制表达中，depth差值就是数字的位数差
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int nCity, nFood, nReq;

vector<int> food[10001];

int digits(int x)
{
    return (int)(log(x*1.0) / log(2.0)) + 1;
}

int LCP(int a, int b)
{
    if (a == b)
        return a;
    
    if (a > b) {
        int temp = b;
        b = a;
        a = temp;
    }
    
    // a is always smaller
    b >>= (digits(b) - digits(a));
    while (a != b) {
        a >>= 1;
        b >>= 1;
    }
    
    return a;
}

int vdist(int p, int v)
{
    if (p == v)
        return 0;

    return digits(v) - digits(p);
}

int pathdist(int a, int b)
{
    if (a == b)
        return 0;
    
    int lcp = LCP(a, b);
    return vdist(lcp, a) + vdist(lcp, b);
}

int main()
{
    cin >> nCity >> nFood >> nReq;
    
    int temp, loc;
    for (int i = 1; i <= nFood; ++i) {
        cin >> temp;
        for (int k = 0; k < temp; ++k) {
            cin >> loc;
            food[i].push_back(loc);
        }
    }
    
    int foodid, to;
    int cur = 1;
    int best;
    long long total = 0LL;
    for (int i = 0; i < nReq; ++i) {
        cin >> foodid >> to;
        best = 1000000000;
        for (int v : food[foodid]) {
            best = min(best, pathdist(cur, v) + pathdist(v, to));
        }
        
        total += best;
        cur = to;
    }
    
    cout << total << endl;
    return 0;
}
