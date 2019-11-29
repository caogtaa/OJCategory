
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common_headers.h"
#include "helper.h"

using namespace std;

#define MAXN 12000
#define DOUBLE_MAXN (MAXN << 1)
long long F[MAXN+1];
bool appear[DOUBLE_MAXN+1];
long long ccc = 0;

class Solution
{
public:
	void Func(int count, long long product, int sum, int x) {
		++ ccc;
		long long newProduct = product * x;
		if (newProduct > DOUBLE_MAXN)
			return;

		long long delta = newProduct - sum - x;
		long long k = count + delta + 1;
		if (k > MAXN)
			return;

		F[k] = min(F[k], newProduct);

		// do not use x
		Func(count, product, sum, x+1);

		// use x
		Func(count+1, newProduct, sum+x, x);
	}

	long long solve()
	{
		long long result = 0;
		fill(F, F+MAXN+1, INT64_MAX);

		int lmt = (int)sqrt(MAXN);
		for (int i = 2; i <= lmt; ++i) {
			Func(1, i, i, i);
		}

		for (int i = 2; i <= MAXN; ++i) {
			if (appear[F[i]])
				continue;

			result += F[i];
			appear[F[i]] = true;
			if (F[i] == INT64_MAX) {
				int k = 0;
			}
		}		
		return result;
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=88
// My 1st 40% difficulty rating problem
// Kind of bruteforce solution:
// 设k对应的最小积和数（minimal product-sum number）为F[k]
// 确定问题的范围：
// 1. 通过观察样例，得到一种简单构造积和数的方法：保留2和k，其余的部分用1填充
// 这种构造法作为最差情况可以得到F[k] = 2*k，所以最小积和F[k] <= 2*k
// 2. 2^15 = 32,768 > 12000*2。以此确认组成F[k]的数中>1的数最多出现14个
// 算法：
// 通过递归形式暴力求解所有乘积 <= 12000*2的序列，并且更新序列对应的F[k]
// 由于乘积增长非常迅速，算法复杂度不会呈现指数趋势。实测过程中统计递归函数的调用次数为36W+
// 需要注意的是栈容易溢出
// 算法和论坛的高分回答类似