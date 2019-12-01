// https://www.hackerrank.com/challenges/xor-and-sum
// DP
// 题意：给定两个2进制数A, B（位数 <= 100000)
// 求以下公式的结果：sigma(A xor (B << i) [i=0:314159]

// 思路：先确定314159应该以314160处理，因为sigma运算是[0, 314159]闭区间
// 虽然是数字运算，但是位数较大，只能用字符串待为处理，暴力方法时间复杂度为 314160 * O(N)，常数太大
// 分析求和公式，每一项等于A的1被置0或者0被置1，然后所有修改后的A相加
// 这个效果等价于：先将所有A叠加得到A'，再将所有B<<i叠加得到B'，对它们两个进行“批量XOR”操作
// B'“批量XOR”A'，会将所有A'上>0的位值减少，所有=0的位值增加，减少或者增加幅度等于B'上对应位的数值（没有具体证明方法，脑补过程）
// A'比较容易得到，所有bit 1变成314160
// B'通过模拟几种case也比较容易找到规律
//   case 1: 2 * len(B) <= 314160
//   case 2: len(B) + 314160 <= 314160 < 2 * len(B)
// 整理后的算法步骤是
//   1. 用DP计算lsum[k], rsum[k]，分别表示左侧、右侧k位中1的出现次数
//   2. 叠加B'，算法根据evernote图示得到
//   3. 右对齐A', B'，做“批量XOR"

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXB    100000
#define CONS    314160
#define MOD     1000000007

//#define MAXB    6
//#define CONS    3

int lsum[MAXB];
int rsum[MAXB];
int tbl[MAXB+CONS-1];

string A, B;
int na, nb;
int tlen;
int repeat;

int main()
{
    cin >> A >> B;
    na = (int)A.size();
    nb = (int)B.size();
    repeat = CONS;
    tlen = repeat + nb - 1;
    
    lsum[0] = (B[0] == '1');
    for (int i = 1; i < nb; ++i) {
        lsum[i] = lsum[i-1] + (B[i] == '1');
    }
    
    rsum[nb-1] = (B[nb-1] == '1');
    for (int i = nb-2; i >= 0; --i) {
        rsum[i] = rsum[i+1] + (B[i] == '1');
    }
    
    int k = 0;
    // fill head
    for (; k < nb; ++k) {
        tbl[k] += lsum[k];
        if (k >= repeat)
            tbl[k] -= lsum[k-repeat];
    }
    
    // fill middle with max overlapped 1
    for (; k < tlen - nb; ++k) {
        tbl[k] = lsum[nb-1];
    }
    
    // fill tail
    for (; k < tlen; ++k) {
        tbl[k] = rsum[nb - tlen + k];
    }
    
    // right align na with tbl
    for (int i = 0; i < na; ++i) {
        if (A[i] == '1') {
            tbl[tlen-na+i] = CONS - tbl[tlen-na+i];
        }
    }
    
    long long result = 0LL;
    for (int i = 0; i < tlen; ++i) {
        result <<= 1;
        result += tbl[i];
        result %= MOD;
    }
    
    cout << result;
    
    return 0;
}
