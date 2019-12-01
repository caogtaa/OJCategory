/*
题意：给出N，3<=N<=3*10^6，求所有满足a+b+c=N的tuple(a,b,c)中，sin(a)+sin(b)+sin(c)的最大值
思路：O(N^2)的暴力法没有拿满分，从editorial中学习了O(N)的算法。
需要用到三角函数和差化积公式sin(a)+sin(b) = 2 * sin((a+b)/2) * cos((a-b)/2)。
所以F = sin(a)+sin(b)+sin(c) = 2 * sin((a+b)/2) * cos((a-b)/2) + sin(c)
枚举c, 所以每个迭代中a+b的值也是固定的，上式中sin((a+b)/2)和sin(c)都是固定值，所以只要枚举cos((a-b)/2)的值就可以求得F的最大值。cos((a-b)/2)在所有a,b情况下的取值范围可以用DP求得:
a+b=2时，a-b={0}
a+b=3时，a-b={-1,1}
a+b=4时，a-b={-2,0,2}
a+b=5时，a-b={-3,-1,1,3}
以此类推，注意a+b=s和a+b=s+2的取值范围，刚好是上下限分别+1和-1
由于cos(x)=cos(-x)，上下限的cos值其实是一样的
*/
//
//  by caogtaa
//

#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;

#define MAXN    3000000

double cosMax[MAXN+1];

void init(int N)
{
    cosMax[2] = cos(0);
    cosMax[3] = cos(1 / 2.0);
    int mx;
    for (int s = 4; s <= N; ++s) {
        mx = s - 2;
        cosMax[s] = fmax(cosMax[s-2], cos(mx / 2.0));
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    int C;
    
    init(N);
    
    double best = numeric_limits<double>::lowest();
    int ApB;
    for (C = 1; C <= N-2; ++C) {
        ApB = N - C;
        best = fmax(best, 2.0 * sin(ApB / 2.0) * cosMax[ApB] + sin(C));
    }
    
    printf("%.9lf", best);
    return 0;
}
