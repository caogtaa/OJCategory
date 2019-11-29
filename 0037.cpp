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
	int solve()
	{
		int cnt = 0;
		int sum = 0;

		helper.init(1000000);
		auto primes = helper.getPrimes(11, 1000000);

		for (auto p : primes) {
			if (helper.isTruncatablePrime(p)) {
				cout << p << endl;
				++ cnt;
				sum += p;
				if (cnt == 11)
					break;
			}
		}

		return sum;
	}

	PrimeHelper helper;
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}
