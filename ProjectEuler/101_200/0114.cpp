
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	// long long Func(int n, int rest) {
	// 	if (rest * 4 - 1 > n)
	// 		// no enough grids
	// 		return 0;

	// 	if (rest <= 1) {
	// 		// sum(1,2,...,n-3+1)
	// 		return (n-2)*(n-1)/2;
	// 	}

	// 	long long& ret = F[n][rest];
	// 	if (ret != -1)
	// 		return ret;

	// 	ret = Func(n-1, rest);
	// 	for (int i = 3; i <= n; ++i) {
	// 		ret += Func(n-i-1, rest-1);
	// 	}
		
	// 	return ret;
	// }

	// long long solve() {
	// 	memset(F, -1, sizeof(F));
	// 	int len = 50;
	// 	long long result = 0;
	// 	for (int rest = 1; rest*4-1 <= len; ++rest) {
	// 		result += Func(len, rest);
	// 	}

	// 	result += 1;	// +1 for empty solution
	// 	return result;
	// }

	long long solve() {
		F[0] = F[1] = F[2] = 1;
		F[3] = 2;
		for (int i = 4; i <= 50; ++i) {
			F[i] = F[i-1];	// put grey
			for (int k = i-4; k >= 0; --k) {
				F[i] += F[k];	// put red with different length, with a following grey grid, k is the rest grid length
			}

			F[i] += 1;		// fill all red
		}

		return F[50];
	}

private:
	// long long F[51][20];
	long long F[51];
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=114
// 动态规划1
// F[n][k]长度n内容纳k个线段的方案数
// 求解 sum(F(50,1), F(50,2), ..., F(50,(len+1)/4)) + 1

// 动态规划2
// F[n]表示长度n能容纳线段的方案数
// F(n) = F(n-1) + {F(n-4)+F(n-5)+...+F(0)} + 1, (F(0)=F(1)=F(2)=1, F(3)=2)

// 数论分析
// https://projecteuler.net/thread=114#3306
// https://oeis.org/A005252
// 递推式 a(n) = 2a(n-1) - a(n-2) + a(n-4)，但是不知道怎么求的