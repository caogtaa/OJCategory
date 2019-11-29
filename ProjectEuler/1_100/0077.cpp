
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

int F[1001][1001];

class Solution
{
public:
	int Func(int n, int k) {
		// split n with max number be kth prime
		if (n == 0)
			return 1;
		
		if (k < 0)
			return 0;

		if (F[n][k] != -1)
			return F[n][k];

		F[n][k] = Func(n, k-1);
		if (primes[k] <= n) {
			F[n][k] += Func(n-primes[k], k);
		}

		return F[n][k];
	}

	int solve()
	{
		memset(F, -1, sizeof(F));
		helper.init(1000000);
		primes = helper.getPrimes(2, 1000000);
		
		int result = -1;
		for (int i = 2; i <= 1000; ++i) {
			if (Func(i, 1000) >= 5000)
				return i;
		}

		return -1;
	}

	PrimeHelper helper;
	vector<int> primes;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=77
// simple DP to find number of combinations
// the result is suprisingly small
