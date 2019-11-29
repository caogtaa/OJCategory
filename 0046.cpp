#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"

using namespace std;

class Solution
{
public:
	int solve() {
		helper.init(1000000);
		auto primes = helper.getPrimes(3, 1000000);

		int n = 35;
		int k = 0;
		while (true) {
			if (primes[k+1] <= n) {
				// find the largest prime that <= n
				++ k;
				continue;
			}

			if (primes[k] == n) {
				n += 2;
				continue;
			}

			bool establish = false;
			for (int i = k; i >= 0; --i) {
				if (SpecialNumber::isSquareNumber((n-primes[i]) / 2)) {
					establish = true;
					break;
				}
			}

			if (!establish)
				return n;

			n += 2;
		}

		return -1;
	}

	PrimeHelper helper;
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// brute force