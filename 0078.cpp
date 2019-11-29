
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

int F[1000001];

class Solution
{
public:
	int solve()
	{
		F[0] = 1;
		long long m1, m2;
		int sign;
		for (long long n = 1; n <= 1000000; ++n) {
			for (long long k = 1; k <= n; ++k) {
				m1 = n-k*(k*3-1)/2;
				m2 = n-k*(k*3+1)/2;
				if (k & 1)
					sign = 1;
				else
					sign = -1;

				if (m1 >= 0)
					F[n] = (F[n] + F[m1] * sign) % 1000000;
				if (m2 >= 0)
					F[n] = (F[n] + F[m2] * sign) % 1000000;
				
				while (F[n] < 0)
					F[n] += 1000000;

				if (m2 < 0 || m1 < 0) {
					// because m1 and m2 is decreasing for fixed n
					break;
				}
			}

			if (F[n] == 0) {
				return n;
			}
		}

		return -1;
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=78
// bruteforce according to following fomular
// http://mathworld.wolfram.com/PartitionFunctionP.html (item 11)
