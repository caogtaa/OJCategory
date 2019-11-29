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
	bool haveSameDigit(long long n, int count) {	// d for digit count
		unordered_set<int> s;
		int d;
		for (int i = 0; i < count; ++i) {
			d = n % 10;
			if (s.count(d)) {
				return true;
			}

			s.insert(d);
			n /= 10;
		}

		return false;
	}

	vector<long long> updateSuffix(const vector<long long>& suffix, int digitCount, int prime) {
		vector<long long> result;
		long long base = (long long)pow(10, digitCount);

		long long nxt;
		long long top3;
		for (auto n : suffix) {
			for (int i = 0; i < 10; ++i) {
				nxt = i * base + n;
				top3 = nxt / (base / 100);
				if (top3 % prime == 0 && !haveSameDigit(nxt, digitCount+1)) {
					result.push_back(nxt);
				}
			}
		}

		return result;
	}

	int digitCount(long long n) {
		return (int)log10(n) + 1;
	}

	long long solve() {
		vector<long long> suffix;
		for (int i = 10; i < 1000; ++i) {
			if (i % 17 == 0 && !haveSameDigit(i, 3)) {
				suffix.push_back(i);
			}
		}

		vector<int> primes{1,2,3,5,7,11,13};
		int base;
		int digitCount;
		for (int i = primes.size()-1; i >= 0; --i) {
			// reset digits = i + 1
			// previous suffix digits = primes.size()-1-i + 3
			digitCount = primes.size()-i+2;
			suffix = updateSuffix(suffix, digitCount, primes[i]);
		}

		long long sum = 0LL;
		for (auto v : suffix) {
			if (this->digitCount(v) == 10)
				sum += v;
		}
		return sum;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;
	return 0;
}

// search from back to front, append one digit at front each time