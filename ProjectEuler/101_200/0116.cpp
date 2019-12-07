
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:

	long long solve() {
		long long result = 0;
		for (int len = 2; len <= 4; ++len) {
			for (int i = 0; i < len; ++i) {
				F[len][i] = 1;
			}
			F[len][len] = 2;
			for (int i = len+1; i <= 50; ++i) {
				F[len][i] = F[len][i-1] + F[len][i-len];
			}

			result += F[len][50] - 1;	// -1 to ignore empty solution
		}

		return result;
	}

private:
	// long long F[51][20];
	long long F[5][51];
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=116
// 动态规划
// 同0114
// F[len][n]表示长度n格子能容纳长度为len的线段的方案数
