#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using std::vector;
using std::cout;

const double PI = acos(-1);

struct Complex
{
    Complex(double read = 0.0, double img = 0.0) : _real(read), _img(img) {}
    
    static Complex W(int n, int k = 1) {
        // 第k个n次单位复数根, 0 <= k <= n-1
        // W(n,k) = W^(i*2pi*k/n)
        // 满足W(n,k) ^ n = 1
        // 根据e^(ix) = cos(x) + i*sin(x)转换成复数
        double t = PI * 2 * k / n;
        return Complex(cos(t), sin(t));
    }
    
    void operator *= (const Complex &rhs) {
        double r = _real;
        double i = _img;
        _real = r * rhs._real - i * rhs._img;
        _img = i * rhs._real + r * rhs._img;
    }
    
    void operator += (const Complex &rhs) {
        _real += rhs._real;
        _img += rhs._img;
    }
    
    void operator /= (double n) {
        _real /= n;
        _img /= n;
    }
    
    Complex operator / (double n) const {
        return Complex(_real / n, _img / n);
    }
    
    Complex operator + (const Complex &rhs) const {
        return Complex(_real + rhs._real, _img + rhs._img);
    }
    
    Complex operator - (const Complex &rhs) const {
        return Complex(_real - rhs._real, _img - rhs._img);
    }
    
    Complex operator * (const Complex &rhs) const {
        Complex result(_real, _img);
        result *= rhs;
        return result;
    }
    
    double _real;
    double _img;
};
    
inline int bit_revert(int n, int len)
{
    int result = 0;
    while (len--) {
        result <<= 1;
        result += n & 1;
        n >>= 1;
    }
    
    return result;
}



// 递归形式的FFT，基于递归代码便于推算出迭代形式的FFT
// P是多项式的系数表达式，需满足P的长度是2的幂
vector<Complex> FFTRecursive(const vector<Complex> &P)
{
    int n = (int)P.size();
    if (n == 1) {
        return {{P[0]}};
    }

    auto Wn = Complex::W(n);
    Complex W(1);
    vector<Complex> A0, A1;
    for (size_t i = 0; i < P.size(); i+=2) {
        A0.push_back(P[i]);
        A1.push_back(P[i+1]);
    }

    auto Y0 = FFTRecursive(A0);
    auto Y1 = FFTRecursive(A1);
    vector<Complex> Y;
    Y.resize(P.size());

    for (int k = 0; k < n >> 1; ++k) {
        Y[k] = Y0[k] + W * Y1[k];
        Y[k+(n>>1)] = Y0[k] - W * Y1[k];
        W *= Wn;
    }

    return Y;
}

// 迭代形式的FFT
vector<Complex> FFT(const vector<Complex> &P, bool forward = true)
{
    int n = (int)P.size();
    int level = (int)(log(n) / log(2.0));
    
    vector<Complex> A(n);
    for (int i = 0; i < n; ++i) {
        A[bit_revert(i, level)] = P[i];
    }
    
    int wfactor = forward ? 1 : -1;
    
    // 叶子层L = 0，在初始化A的时候已经计算完毕，因为长度为1的多项式FFT等于自己
    // L = 1 to level，逐层向上更新
    // 每一层有 p = n >> L个部分，每个部分长度 m = 1 << L
    for (int L = 1; L <= level; ++L) {
        int m = 1 << L;
        auto wm = Complex::W(m, wfactor);
        for (int sp = 0; sp < n; sp += m) {     // sp 是每个部分的开始下标
            Complex w(1);
            for (int k = 0; k < m >> 1; ++k) {
                // 蝴蝶运算
                // 每次只更新 A[sp+k] 和 A[sp+k+(m>>1)]，没有其他项参与
                Complex u = A[sp+k];
                Complex t = w * A[sp+k+(m>>1)];
                A[sp+k] = u + t;
                A[sp+k+(m>>1)] = u - t;
                w *= wm;
            }
        }
    }
    
    if (!forward) {
        for (auto &x : A)
            x /= n;
    }
    
    return A;
}

int extended_length(int len)
{
    if (len == 1)
        return 2;   // double it
    
    auto x = log(len-1.0) / log(2.0) + 1;
    return 1 << ((int)x + 1);   // +1 to double
}

// 两个多项式相乘
// A, B先补足长度到2的幂，然后再将长度翻倍，均用0填充扩展部分
vector<double> poly_mult(const vector<double> &A, const vector<double> &B)
{
    vector<double> C;
    if (A.size() > 0 && B.size() > 0) {
        int len = (int)std::max(A.size(), B.size());
        auto ext = extended_length(len);
        vector<Complex> Adup(ext);
        vector<Complex> Bdup(ext);
        for (size_t i = 0; i < A.size(); ++i) {
            Adup[i]._real = A[i];
        }
        
        for (size_t i = 0; i < B.size(); ++i) {
            Bdup[i]._real = B[i];
        }
        
        auto Adot = FFT(Adup);
        auto Bdot = FFT(Bdup);
        for (size_t i = 0; i < Adot.size(); ++i) {
            Adot[i] += Bdot[i];
        }
        
        auto Cdot = FFT(Adot, false);
        vector<double> C(Cdot.size());
        
        // C的次数界 = A的次数界 + B的次数界 - 1
        for (size_t i = 0; i < std::min(Cdot.size(), A.size() + B.size() - 1); ++i) {
            C[i] = Cdot[i]._real;
        }
    }
    
    return C;
}

int main()
{
    vector<Complex> v{{0, 1, 2, 3}};
    auto t = FFT(v);
    auto tt = FFT(t, false);

    return 0;
}
