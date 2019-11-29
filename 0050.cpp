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
	/*int mostConsecutivePrimeCount(int p, const vector<int>& primes) {
		auto iter = lower_bound(S.begin(), S.end(), p);

		long long sum = *iter;
		int count = iter - S.begin() + 1;
		
		int head = 0, tail = count;
		while (sum != p) {
			if (sum < p) {
				sum += primes[tail++];
				++ count;
			} else {
				sum -= primes[head++];
				-- count;
			}
		}

		return count;
	}
	
	long long solve_1() {
		int best = 0;
		int result = 0;
		int count;

		helper.init(1000000-1);
		auto primes = helper.getPrimes(2, 1000000-1);

		S.resize(primes.size());
		S[0] = primes[0];
		for (int i = 1; i < primes.size(); ++i) {
			S[i] = S[i-1] + primes[i];
		}

		for (int i = primes.size()-1; i >= 0; --i) {
			count = mostConsecutivePrimeCount(primes[i], primes);
			if (count > best) {
				best = count;
				result = primes[i];
			}
		}
		
		return result;
	}*/

	int solve() {
		int best = 21;
		int result = 953;
		int count;

		helper.init(1000000-1);
		auto primes = helper.getPrimes(2, 1000000-1);

		S.resize(primes.size());
		S[0] = primes[0];
		for (int i = 1; i < primes.size(); ++i) {
			S[i] = S[i-1] + primes[i];
		}

		// find largest H-L which S[H]-S[L] < 1,000,000 and S[H]-S[L] is prime
		// check each sequence that end with Hth prime
		for (int H = S.size()-1; H >= 0; --H) {
			auto iter = lower_bound(S.begin(), S.end(), S[H]-(1000000-1));
			int L = iter - S.begin();
			while (H-L > best) {
				if (helper.isPrime(S[H] - S[L])) {
					break;
				}

				++ L;
			}

			if (H-L > best) {
				best = H-L;
				result = S[H] - S[L];
			}
		}
		
		return result;
	}

	PrimeHelper helper;
	vector<long long> S;
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// solution 1:
// working but low efficient
// use slide window to find consecutive prime count
// optimize 1: use binary search on "prefix sum" to initialize slide window
// optimize 2: greedy, smaller numbers has longger chain, so if more than one slide window satisfied, take leftmost one

// solution 2:
// program terminated in 1s
// calculate prefix sum S of all primes, our goal is to find longest H-L that S[H]-S[L] is prime
// enum each H, loop L for it, update best H-L each time to minimize search work for H-1

// solution 3:
// https://projecteuler.net/best_posts=050
// one pass through O(N) algo, but I couldn't understand it
