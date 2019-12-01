// https://www.hackerrank.com/challenges/substring-diff
// DP
// 题意：两个字符串A, B，A.substr(i, L)和B.substr(k, L)做比较，记不匹配字符数为 M(i, k, L)
// 给定S，求所有(i, k)对中，使M(i, k, L) <= S的最大L。len(A) == len(B) <= 1500

// 思路：暴力法是枚举(i, k)，延伸L使 M(i, k, L) == S，复杂度O(N^3)
// 优化方法是，先给i, k定一个固定偏移offset，再同时累加i, k。可以利用DP在O(N)的时间内遍历一个(i, offset)对，整体时间复杂度降低为O(N^2)
// 令F(i, offset)是能使M(i, i+offset, L) <= S的最大L
// i从0开始，k = i+offset。沿途记录字符比较后的same[]数组并累加当前diff
// 尝试追加当前字符到子串中，如果diff数 > S，则从左侧开始删减字符，直到diff <= S

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int T;
int S;
bool same[1600];

int Func(const string &A, const string &B, size_t offset)
{
    int result = 0;
    int L = 0;
    int diff = 0;
    for (int i = 0, k = (int)offset; k < A.size(); ++i, ++k) {
        ++ L;
        
        same[i] = (A[i] == B[k]);
        if (!same[i]) {
            ++ diff;
            if (diff > S) {
                // move head until diff <= S
                int sp = i - L + 1;
                while (sp <= i && diff > S) {
                    -- L;
                    if (!same[sp])
                        -- diff;
                    
                    ++ sp;
                }
            }
        }
        
        result = max(result, L);
    }
    
    return result;
}

// M(i, j, L) <= S
int main()
{
    cin >> T;
    while (T--) {
        string A, B;
        cin >> S >> A >> B;
        
        int best = 0;
        for (size_t i = 0; i < A.size(); ++i) {
            best = max(Func(A, B, i), best);
            best = max(Func(B, A, i), best);
        }
        
        printf("%d\n", best);
    }
    return 0;
}
