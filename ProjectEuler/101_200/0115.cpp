
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:

	long long solve() {
		int m = 50;
		for (int i = 0; i < 50; ++i) {
			F[i] = 1;
		}

		F[m] = 2;
		int i;
		for (i = m+1; ; ++i) {
			F[i] = F[i-1];	// put grey
			for (int k = i-m-1; k >= 0; --k) {
				F[i] += F[k];	// put red with different length, with a following grey grid, k is the rest grid length
			}

			F[i] += 1;		// fill all red
			if (F[i] > 1000000)
				break;
		}

		return i;
	}

private:
	// long long F[51][20];
	long long F[1000];
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=115
// 动态规划
// 同0115
// F[n]表示长度n能容纳线段的方案数
// F(n) = F(n-1) + {F(n-4)+F(n-5)+...+F(0)} + 1, (F(0)=F(1)=F(2)=1, F(3)=2)

// 数论分析
// https://projecteuler.net/thread=114#3306
// https://oeis.org/A005252
// 递推式 a(n) = 2a(n-1) - a(n-2) + a(n-4)，但是不知道怎么求的