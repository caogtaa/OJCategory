
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	long long solve() {
		const long long MAXP = 1000000;
		PrimeHelper helper;
		helper.init(MAXP);

		long long result = 0;
		for (long long x = 1; ; ++x) {
			long long delta = (long long)(pow(x+1, 3) - pow(x, 3));
			if (delta >= MAXP)
				break;

			if (helper.isPrime(delta)) {
				++ result;
			}
		}

		return result;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=131
// 分析
// 暴力
// 题目求满足 n^3 + n^p = x^3 的素数p的个数
// 等式等价于 n^2 (n+p) = x^3
// 由于p是素数，p和p+n都不可能是n的倍数，所以n不能整除x，x的因数中不包含n。可以推断n^2和(n+p)分别是一个立方数，所以n也是一个立方数
// 设 n = a^3, n+p = b^3 => p = b^3-a^3 = (b-a)(a^2 + ab + b^2)
// 得出p一定是两个立方数的距离，并且由于p = b^3-a^3 = (a-b)(a^2 + ab + b^2)，p是素数，所以(b-a) = 1
// 所以p一定是两个相邻立方数的距离，时间复杂度O(pow(N, 1/3))