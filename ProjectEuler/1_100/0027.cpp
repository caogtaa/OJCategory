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

class Solution {
public:
	int getChainLength(int a, int b) {
		int result = 0;
		int tmp;
		for (int n = 0; n <= b; ++n) {
			tmp = n*n + n*a + b;
			if (tmp <= 1 || !helper.isPrime(n*n + n*a + b))
				return result;

			++ result;
		}

		return result;
	}

	int solve(int N) {
		int result = 0;
		int best = 0;
		int limit = N * N + 100000;
		helper.init(limit);
		auto primes = helper.getPrimes(41, N);
		for (auto b : primes) {
			for (int a = -N+1; a <= N-1; ++a) {
				int tmp = getChainLength(a, b);
				if (tmp > best) {
					best = tmp;
					result = a * b;
				}
			}
		}

		return result;
	}

public:
	PrimeHelper helper;
};

int main() {
	Solution s;
	cout << s.solve(1000) << endl;

	return 0;
}

// for fomular n^2 + an + b, b should always be positive prime (consider when n = 0)
// for each prime b, enum -N < a < N