#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"

using namespace std;

class Solution
{
public:
	bool isAscDigits(int p) {
		int d = 9;
		while (p) {
			if (p % 10 > d)
				return false;

			d = p % 10;
			p /= 10;
		}

		return true;
	}

	bool isCircularPrime(int p) {
		int len = Util::digitCount(p);
		for (int i = 0; i < len; ++i) {
			if (!helper.isPrime(p))
				return false;

			p = p / 10 + (int)pow(10, len-1) * (p % 10);	// rotate
		}

		return true;
	}

	int solve(int N)
	{
		vector<int> result;
		helper.init(N);
		auto primes = helper.getPrimes(2, N-1);		// all rotation will not excceed N when N = 100 or 1,000,000
		for (auto p : primes) {
			if (isCircularPrime(p)) {
				result.push_back(p);
			}
		}

		return result.size();
	}

public:
	PrimeHelper helper;
};

int main()
{
	Solution s;
	cout << s.solve(1000000) << endl;

	return 0;
}
