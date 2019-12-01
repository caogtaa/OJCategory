/*
题意：Emma喜欢自拍，她有N个朋友和X张胶卷。如果Emma和N个朋友的任意不同组合分别合影一次，X张胶卷还剩多少张，如果不够要缺多少张？
思路：排列组合问题，需要的总胶片数量sum=C(N,1)+C(N,2)+…+C(N,N)。求|sum-X|。

Editorial: 根据帕斯卡三角性质，题目即求(2^n) - 1
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int N, x;
    cin >> N >> x;
    long long result = 0;
    long long C = 1;
    for (int i = N; i >= 1; --i) {
        C *= i;
        C /= (N-i+1);
        result += C;
    }
    
    cout << abs(x-(int)result) << endl;
    return 0;
}
