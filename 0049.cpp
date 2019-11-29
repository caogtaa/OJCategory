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
	long long check(int p, const vector<int>& primes) {
		auto digits = Util::getDigits(p);
		set<int> candidates;
		while (next_permutation(digits.begin(), digits.end())) {
			int nxt = Util::getNumber(digits);
			if (!helper.isPrime(nxt))
				continue;

			candidates.insert(nxt);
		}

		for (int p2 : candidates) {
			if (candidates.count(p2 + p2 - p) > 0) {
				return ((long long)p) * 100000000 + p2 * 10000 + (p2+p2-p);
			}
		}

		return -1;
	}

	long long solve() {
		helper.init(10000);
		auto primes = helper.getPrimes(1488, 9999);

		long long check;
		for (auto p : primes) {
			check = this->check(p, primes);
			if (check != -1)
				return check;
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

// enum prime p in [1000,9999], find its prime permutation as p2
// enum p2 to check if p3 exists