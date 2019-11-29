
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
		int MAXD = 1000000;
		int result = 1;
		double threeOnSeven = 3.0/7;
		double bestDelta = threeOnSeven - 1.0/MAXD;

		int N;
		int G;
		double delta;
		for (int D = MAXD; D >= 1; --D) {
			N = 3 * D / 7;
			if (N * 7 >= 3 * D)
				continue;

			delta = threeOnSeven - 1.0 * N / D;
			if (delta < bestDelta) {
				bestDelta = delta;

				G = Util::gcd(N, D);
				result = N / G;
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

// to find closest n/d to 3/7
// try each d, with n < 3d/7, we get n directly. Test its distance to 3/7.