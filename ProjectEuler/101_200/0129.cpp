
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	int A(int n) {
		int x = 1;
		int result = 1;
		while (true) {
			x %= n;
			if (x == 0)
				return result;

			x *= 10;
			++ x;
			++ result;
		}

		return -1;
	}

	long long solve() {
		for (int n = 1000000; n <= 2000000; ++n) {
			if (Util::gcd(n, 10) != 1)
				continue;

			if (A(n) > 1000000)
				return n;
		}

		return -1;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=129
// 暴力
// 数据范围分析
// R(k)是长度为k的整数，每一位都是1
// R(k)是否能整除n，可以用长除法进行运算，从1开始除不尽则对余数补一位1，直到除尽
// A(n)表示能整除n的最小R(k)对应的k，即整除n的数R(k)的长度
// 用长除法的过程中可以观察到，每次除不尽时的余数都应该不同，否则会进入无限循环
// n的余数数量 = n
// 题目已经给出对于gcd(n,10)==1的所有n都有解，所以可以认定长除法最多迭代n次，即A(n) <= n
// 如果寻找n使A(n) >= 1,000,000，可以从n >= 1,000,000开始
