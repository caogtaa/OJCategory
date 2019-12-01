/*
题意: 一个N位的数字，如果其中有一位比它相邻的位数都大，则是一个Max Digit；如果比相邻的位数都小，则是一个Min Digit。比如101中的0室Min Digit，293中的9是Max Digit。
给定一个区间[A，B]，求该区间内所有数字上的Max Digit和Min Digit数量和

思路：本次比赛中最难的题目，想不出简单的算法
以数字 5432为例子，按顺序考虑如下数字里的Max/Min Digit
5432,5431,5430
542X,541X,540X
53XX,52XX,51XX,50XX
4XXX,3XXX,2XXX,1XXX
所有3位数的Max/Min Digit数量
其中X表示可以取任何数字

对于每个数字，枚举每个位，单独考虑在该位上可能出现的Max/Min Digit个数，分以下4中case:
L、M、R都表示是’0’~’9’之间的一个固定数字, X表示是’0’~’9’范围的可变数字
1.XXX, maxd = mind = 9*9 + 8*8 + … + 1*1
2.LXX, maxd = Sn(L+1, 9); mind = Sn(10-L, 9)
3.LMX, 根据LM的关系，maxd =M, mind = 9-M
4.LMR, 根据LMR的关系， maxd = 1, mind = 1
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

typedef pair<long long, long long> llpair;

long long sum[13];
long long XX = 1LL;

long long Sn(long long a1, long long an)
{
    // Sn = a1 + (a1+1) + ... + an = n * (a1 + an) / 2
    long long n = abs(an - a1 + 1);
    return n * (a1 + an) / 2;
}

long long Possible(const string &s, int k)
{
    char c = s[k];
    long long multLeft = 1LL;
    long long multRight = 1LL;
    for (int i = 0; i < k-1; ++i) {
        if (s[i] == 'X')
            multLeft *= 10;
    }

    for (int i = k+2; i < (int)s.size(); ++i) {
        if (s[i] == 'X')
            multRight *= 10;
    }

    llpair result = make_pair(0LL, 0LL);
    if (c == 'X') {
        if (s[k-1] == 'X' && s[k+1] == 'X') {
            long long m = XX;
            result.first += m * multLeft * multRight;
            result.second += m * multLeft * multRight;
        } else {
            // s[k-1] != 'X' && S[k+1] == 'X'
            result.first += Sn(s[k-1] - '0' + 1, 9) * multLeft * multRight; // for max
            result.second += Sn(9 - (s[k-1]-'0') + 1, 9) * multLeft * multRight;
        }
    } else {
        // C != 'X'
        if (s[k-1] != 'X' && s[k+1] != 'X') {
            if (s[k-1] < c && s[k+1] < c)
                result.first += 1 * multLeft * multRight;
            if (s[k-1] > c && s[k+1] > c)
                result.second += 1 * multLeft * multRight;
        } else {
            // s[k-1] != 'X' && s[k+1] == 'X'
            if (s[k-1] < c) {
                result.first += (s[k] - '0') * multLeft * multRight;
            }
            if (s[k-1] > c) {
                result.second += (9 - (s[k]-'0')) * multLeft * multRight;
            }
        }
    }
    
    return result.first + result.second;
}

long long V(int n)
{
    // all min-max numbers in 1XXXX ... 9XXXX
    string s = "0";
    for (int i = 0; i < n-1; ++i)
        s.push_back('X');
    
    long long result = 0LL;
    for (char c = '1'; c <= '9'; ++c) {
        s[0] = c;
        for (int k = 1; k < n-1; ++k) {
            result += Possible(s, k);
        }
    }
    
    return result;
}

long long Solve(long long x)
{
    if (x <= 0LL)
        return 0LL;
    
    char ch[20];
    sprintf(ch, "%lld", x);
    string s = ch;
    if (s.size() <= 2)
        return 0LL;
    
    long long result = 0LL;
    for (int i = (int)s.size()-1; i > 0; --i) {
        while (s[i] >= '0') {
            for (int k = 1; k < (int)s.size()-1; ++k) {
                result += Possible(s, k);
            }
            --s[i];
        }
        s[i] = 'X';
        --s[i-1];
    }
    
    while (s[0] >= '1') {
        for (int k = 1; k < (int)s.size()-1; ++k) {
            result += Possible(s, k);
        }
        --s[0];
    }
    
    result += sum[s.size()-1];
    return result;
}

int main()
{
    XX = 0LL;
    for (int i = 1; i <= 9; ++i) {
        XX += i * i;
    }

    sum[0] = sum[1] = sum[2] = 0LL;
    for (int i = 3; i <= 12; ++i) {
        sum[i] = sum[i-1] + V(i);
    }
    
    //auto test = Possible("123XX", 3);
    long long A, B;
    cin >> A >> B;
    
    //// test
    cout << Solve(B) - Solve(A-1) << endl;
    return 0;
}
