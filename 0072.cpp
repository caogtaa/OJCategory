
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

class Solution
{
public:
	long long solve()
	{
		int n = 1000000;
		PrimeHelper helper;
		helper.initPhi(n);

		long long result = 0;
		for (int i = 2; i <= n; ++i) {
			result += helper.phi(i);
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

// https://projecteuler.net/problem=72
// number of n < d and GCD(n, d) = 1 equals phi(d)
// sigma(phi(d)) {2 <= d <= 1000000} is the result
