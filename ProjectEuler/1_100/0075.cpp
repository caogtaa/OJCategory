
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
		int MAXN = 1500000;
		int lmt = (int)sqrt(MAXN);

		vector<int> primitive;		
		primitive.resize(MAXN+1);

		vector<int> result;
		result.resize(MAXN+1);

		// generate all primitive Pythagorean triple
		// time complexity: O(N)
		for (int n = 1; n <= lmt; ++n) {
			for (int m = n+1; m <= lmt; ++m) {
				if (2*m*(m+n) > MAXN)
					break;

				if (Util::gcd(m, n) > 1)
					continue;

				if ((m & 1) && (n & 1))
					continue;

				++primitive[2*m*(m+n)];
			}
		}

		// time complexity: O(N^2 / M)
		// where M is number of primitive Pythagorean triple
		int sum = 0;
		for (int i = 12; i <= MAXN; ++i) {
			if (primitive[i] > 0) {
				for (int k = i; k <= MAXN; k+=i) {
					result[k] += primitive[i];
				}
			}

			if (result[i] == 1)
				++ sum;
		}

		return sum;
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=75
// find all primitive triple by Euclid's formula
// https://en.wikipedia.org/wiki/Pythagorean_triple

