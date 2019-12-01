#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include <string.h>

using namespace std;

// Modified Fibonacci Number
// https://www.hackerrank.com/contests/sears-dots-arrows/challenges/modified-fibonacci-1
// Fibonacci数列变种
// Bib(n) = Bib(n-1) + Bib(n-2) + 1
// 给定一个序列A = {A1, A2, A3, ... An}
// 求S = sigma{Bib(Ai + A(i+1) + ... + Aj)} (1 <= i <= j <= N)
// 不大容易看懂，假设A = {1, 2, 3}, 展开后就是
// S = Bib(1) + Bib(2) + Bib(3) + Bib(1, 2) + Bib(2, 3) + Bib(1, 2, 3)

// 1 <= Ai <= 10^9，所以不能保存所有的Bib(Ai)
// 另外A组合排列展开后有N*(N+1)/2项，而 1 <= N <= 10^5，光做这个展开就会超时

// 思路:
// 求Bib(Ai)的时候势必需要用矩阵乘法＋快速求幂
// 不难构造出矩阵初始值Bib(1) =>
// [1 1 1] 表示 [Bib(1), Bib(0), 常数1]

// Transform Matrix T =>
// [1 1 0
//  1 0 0
//  1 0 1]

// Bib(1) * T = Bib(2)
// Bit(x + y) = Bit(x) * T^y

// 接下来考虑如何高效累加Bib(Ai)得到S
// 将所有A的连续子串排列后会看出一些规律，如果按照加数个数来排列
// A1
// A2   A1+A2
// A3   A2+A3    A1+A2+A3

// 稍微变化一下
//               A1
//      A2       A1+A2
// A3   A2+A3    A1+A2+A3
//
// 实际求的是Bib(Ai)，即 =>
//
//                          Bib(A1)
//           Bib(A2)        Bib(A1+A2)
// Bib(A3)   Bib(A2+A3)     Bib(A1+A2+A3)
//
// 规律性很强
// 列2 ＝ 列1每项 * T^(A2)，增加一项 Bib(A2)
// 列3 ＝ 列2每项 * T^(A1)，增加一项 Bib(A1)
// =>
// 列2总和 ＝ 列1总和 * T^(A2)，再加 Bib(A2)
// 列3总和 ＝ 列2总和 * T^(A1)，再加 Bib(A1)
// ...
// 题目要求的S = 列1总和＋列2总和＋列3总和＋...

// 迭代N次，每次求T^(A2)和Bib(A2)即可，通过快速求幂在 O(log(Max(Ai)))时间复杂度内求得
// 整体时间复杂度是 O(N * log(Max(Ai)))

int N;
int M = 100000000;
int A[100001];

typedef vector<vector<long long>> vector2D;

class Matrix
{
public:
    Matrix() {
        
    }

    Matrix(int r, int c) {
        memset(data, 0, sizeof(data));
        row = r;
        column = c;
    }
    
    Matrix(int r, int c, const vector2D &d) {
        row = r;
        column = c;
        for (int i = 0; i < r; ++i) {
            for (int k = 0; k < c; ++k) {
                data[i][k] = d[i][k];
            }
        }
    }

    Matrix(const Matrix &m) {
        memcpy(data, m.data, sizeof(data));
        row = m.row;
        column = m.column;
    }
    
public:
    void operator += (const Matrix &m) {
        for (int i = 0; i < row; ++i) {
            for (int k = 0; k < column; ++k) {
                data[i][k] += m.data[i][k];
            }
        }
    }
    
    Matrix operator *(const Matrix &m) const {
        Matrix result(row, m.column);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < m.column; ++j) {
                long long v = 0;
                for (int k = 0; k < column; ++k) {
                    v += data[i][k] * m.data[k][j];
                    v %= M;
                }
                
                result.data[i][j] = v;
            }
        }
        
        return result;
    }
    
public:
    long long data[3][3];
    int row;
    int column;
};

Matrix T(3, 3, {{1, 1, 0}, {1, 0, 0}, {1, 0, 1}});
Matrix one(3, 3, {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
Matrix B_1(1, 3, {{1, 1, 1}});   // {B(1), B(0), 1})

Matrix OP(const Matrix &base, long long x)
{
    Matrix result = base;
    Matrix t = T;
    while (x > 0) {
        if (x & 1) {
            result = result * t;
        }
        
        t = t * t;
        x >>= 1;
    }
    
    return result;
}

Matrix Bib(long long x)
{
    // result * T (x-1) times
    return OP(B_1, x - 1);
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    
    long long total = 0;
    Matrix step(1, 3, {{0, 0, 0}});
    Matrix temp(3, 3);
    for (int i = N-1; i >= 0; --i) {
        temp = OP(one, A[i]-1);
        step = step * temp * T;
        //step = OP(step, A[i]);
        step += B_1 * temp;
        //step = step + Bib(A[i]);
        
        total += step.data[0][0];
        total %= M;
    }
    
    cout << total << endl;
    
    return 0;
}
