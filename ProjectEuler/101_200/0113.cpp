
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	long long inc(int n, int k) {
		if (k >= 9)
			return 1;
		if (n <= 1)
			return 10-k;

		long long& ret = INC[n][k];
		if (ret != -1)
			return ret;

		ret = 0;
		for (int i = k; i <= 9; ++i) {
			// choose i as nth digit
			ret += inc(n-1, i);
		}

		return ret;
	}

	long long dec(int n, int k) {
		if (k <= 0)
			return 1;
		if (n <= 1)
			return k+1;

		long long& ret = DEC[n][k];
		if (ret != -1)
			return ret;

		ret = 0;
		for (int i = k; i >= 0; --i) {
			// choose i as nth digit
			ret += dec(n-1, i);
		}

		return ret;
	}

	long long solve() {
		memset(INC, -1, sizeof(INC));
		memset(DEC, -1, sizeof(DEC));
		
		int digits = 100;
		long long result = 0;
		
		for (int i = 1; i <= digits; ++i) {
			// i位数中同时为increasing和decreasing的数是11111111,2222222,3333333这种，总共9个
			// 0000000出现在dec中，它不是正整数，所以多减去一次
			result += inc(i, 1) + dec(i, 9) - 10;
		}

		return result;
	}

private:
	long long INC[101][10];
	long long DEC[101][10];
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=113
// 动态规划
// inc[n][k]表示n位数下最高位不小于k的increasing number有多少
// dec[n][k]表示n位数下最高位不大于k的decreasing number有多少
// n固定的情况下，同时为increasing number和decreasing number的数有9个
// 另外dec[n][k]中计数了000000的情况，需要移除
// 状态空间大小O(n*k)，事件复杂度O(n*k*k)，k<=9

// 数论分析
// LatticePath
// http://mathworld.wolfram.com/LatticePath.html
// https://projecteuler.net/best_posts=113
// increasing number最多有8次increase机会，decreasing number最多有9次decrease机会
// 将increase机会看成纵向移动，将位数看成横向移动，每次移动都是这两者之一
// 套用LatticePath，inc[n][k]=C(n+8,	); dec[n][k]=C(n+9,9)
