
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

long long F[4000];

class Solution
{
public:
	inline long long addition(long long n, long long m) {
		// F(n, m+1) - F(n, m)
		return (m+1) * n * (n+1) / 2;
	}

	void checkSolution(long long f, long long area) {
		if (abs(_twoMillion - f) < _best) {
			_best = abs(_twoMillion - f);
			_result = area;
		}
	}

	int solve()
	{
		_best = INT64_MAX;
		_result = INT64_MAX;
		_twoMillion = 2000000;

		F[1] = 1;
		long long n = 1, m = 1;
		for (m = n+1; ; ++m) {
			// F[n][m]
			F[m] = F[m-1] + addition(n, m-1);
			checkSolution(F[m], n*m);
			if (F[m] > _twoMillion)
				break;
		}

		for (n = 2; ; ++n) {
			// F[n][n] = F[n][n-1]+add(n,n-1) = F[n-1][n]+add(n,n-1)
			// with 1st dimension compressed
			F[n] = F[n] + addition(n, n-1);
			checkSolution(F[n], n*n);
			if (F[n] > _twoMillion)
				break;

			for (m = n+1; ; ++m) {
				F[m] = F[m-1] + addition(n, m-1);
				checkSolution(F[m], n*m);
				if (F[m] > _twoMillion)
					break;
			}
		}

		return (int)_result;
	}

	long long _best;
	long long _result;
	long long _twoMillion;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=85
// 计算出F(n,m) -> F(n,m+1)的递推公式即可
// 更简单的方法：F(n,m) = (n+1)n/2 * (m+1)m/2
