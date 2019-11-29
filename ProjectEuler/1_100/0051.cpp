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
	int countPrime(int x, int delta) {
		int result = 0;
		for (int i = 0; i < 10; ++i) {
			if (helper.isPrime(x + delta * i)) {
				++result;
			}
		}

		if (delta > x && helper.isPrime(x)) {
			// do not count new primes that has leading zero, when p' = x + delta * 0 and x < delta
			-- result;
		}

		return result;
	}

	bool check(int p, const vector<int>& digits, const vector<int>& index) {
		// index contain digit index that <= 2
		int minus = 0;
		int delta = 0;
		for (int k = 1; k <= index.size(); ++k) {
			// k digits being replaced
			vector<bool> choose(index.size());
			fill(choose.end()-k, choose.end(), true);
			do {
				minus = 0;
				delta = 0;
				for (int i = 0; i < choose.size(); ++i) {
					if (choose[i]) {
						minus += digits[index[i]] * base[index[i]];
						delta += base[index[i]];
					}
				}

				if (countPrime(p - minus, delta) >= 8)
					return true;
			} while (next_permutation(choose.begin(), choose.end()));
		}

		return false;
	}

	int solve() {
		helper.init(1000000);
		auto primes = helper.getPrimes(50000, 1000000);

		base[0] = 1;
		for (int i = 1; i < 10; ++i) {
			base[i] = base[i-1]*10;
		}

		long long result = 0;
		for (auto p : primes) {
			auto digits = Util::getDigits(p);
			reverse(digits.begin(), digits.end());
			vector<int> qu;
			for (int i = 1; i < digits.size(); ++i) {
				if (digits[i] <= 2) {
					qu.push_back(i);
				}
			}

			if (qu.size() >= 3 && check(p, digits, qu)) {
				return p;
			}
		}
		return 0;
	}

	PrimeHelper helper;
	vector<long long> S;
	int base[10];
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// = 

// 0. assume the number is less than 1,000,000
// 1. do not touch the last digit, because we are looking for eight prime value family, even number will appear
// 2. when replacing digits, always enlarge the number. otherwise another prime will be better answer
// 3. according to previous restriction, digit being replaced should <= 2
// 4. digits begin replaced should be group of 3, otherwise at least 3 of the new primes will be divisible by 3
// then bruteforce