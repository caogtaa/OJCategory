
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
	int solve()
	{
		int MAXD = 12000;
		int result = 0;

		int N;
		int G;
		double delta;
		for (int D = MAXD; D >= 4; --D) {
			N = D / 2;
			while (N * 2 >= D)
				-- N;

			while (N * 3 > D) {
				if (Util::gcd(N, D) == 1)
					++ result;

				-- N;
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

// https://projecteuler.net/problem=73
// bruteforce
// for each d, find all n that 1/3 < n/d < 1/2

