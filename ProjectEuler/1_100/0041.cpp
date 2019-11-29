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
	bool isPrime(int n) {
		int limit = (int)sqrt(n);
		for (int i = 0; i < primes.size() && primes[i] <= limit; ++i) {
			if (n % primes[i] == 0)
				return false;
		}

		return true;
	}

	int getDigit(const vector<int>& digits) {
		int result = 0;
		for (auto d : digits) {
			result *= 10;
			result += d;
		}

		return result;
	}

	int solve()
	{
		helper.init(10000);
		primes = helper.getPrimes(2, 10000);

		vector<int> digits{7,6,5,4,3,2,1};
		int n;
		do {
			n = getDigit(digits);
			if (isPrime(n)) {
				return n;
			}
		} while (prev_permutation(digits.begin(), digits.end()));

		return -1;
	}

	vector<int> primes;
	PrimeHelper helper;
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// n-pandigital use all the digits 1 to n exactly once
// sigma(d) % 3 == 0 for d in {2,3,5,6,8,9}
// so number of digits of n-pandigital prime has to be 4 or 7

// upper limit:
// number of 7-pandigitals = 7! = 5040
// prime check complexity = O(sqrt(pow(10, 8))) = O(10000), pick all primes in range [2,10000], count=1229
// final complexity = 5040 * 1229