/*
参考Modified Fibonacci Number (Matrix Exponential, 矩阵乘法, 快速求幂)
更改初始矩阵和转置矩阵即可
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include <string.h>

using namespace std;

int N;
const long long M = 1000000007;
long long A[100001];

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
    long long data[2][2];
    int row;
    int column;
};

//Matrix T(3, 3, {{1, 1, 0}, {1, 0, 0}, {1, 0, 1}});
//Matrix one(3, 3, {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
//Matrix B_1(1, 3, {{1, 1, 1}});   // {B(1), B(0), 1})

Matrix T(2, 2, {{1, 1}, {1, 0}});
Matrix one(2, 2, {{1, 0}, {0, 1}});
Matrix F_1(1, 2, {{1, 0}});   // {F(1), 0}

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

Matrix Fibo(long long x)
{
    // result * T (x-1) times
    return OP(F_1, x - 1);
}

int main() {
    int kase;
    cin >> kase;
    while (kase-- > 0) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        long long total = 0;
        Matrix step(1, 2, {{0, 0}});
        Matrix temp(2, 2);
        for (int i = N-1; i >= 0; --i) {
            temp = OP(one, A[i]-1);
            step = step * temp * T;
            //step = OP(step, A[i]);
            step += F_1 * temp;
            //step = step + Bib(A[i]);
            
            total += step.data[0][0];
            total %= M;
        }
        
        cout << total << endl;
    }
    
    return 0;
}
