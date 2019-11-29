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
	int primeFactorCount(int n, const vector<int>& primes) {
		int originN = n;
		int result = 0;
		int limit = (int)sqrt(n);
		for (auto p : primes) {
			if (helper.isPrime(n))
				break;

			if (p > limit)
				break;

			if (n % p == 0) {
				while (n % p == 0) {
					n /= p;
				}
				++ result;
			}
		}

		if (n > 1)
			++ result;

		return result;
	}

	int solve() {
		helper.init(1000000);
		auto primes = helper.getPrimes(2, 1000000);

		int count = 0;
		for (int i = 2; i <= 1000000; ++i) {
			if (primeFactorCount(i, primes) == 4) {
				if (++count == 4)
					return i - 3;
			} else {
				count = 0;
			}
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