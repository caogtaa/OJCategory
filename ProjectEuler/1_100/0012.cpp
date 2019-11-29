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

using namespace std;

#define PRIME_N 2000001

bool notPrime[PRIME_N + 1];
void initPrime()
{
	int end = sqrt(PRIME_N);
	int i, j;
	for (i = 2; i <= end; ++i) {
		if (notPrime[i])
			continue;

		for (j = i * i; j <= PRIME_N; j += i)
			notPrime[j] = true;
	}
}

inline bool isPrime(int x)
{
	return !notPrime[x];
}

class Solution {
	vector<int> primes;

public:
	bool isPalindromic(int N) {
		auto s = to_string(N);
		for (int i = 0; i < s.size() / 2; ++i) {
			if (s[i] != s[s.size()-1-i])
				return false;
		}

		return true;
	}

	int factorCount(int n) {
		int result = 0;
		int k = 0;
		while (n > 1) {
			while (n % primes[k] == 0) {
				++ result;
				n /= primes[k];
			}

			++ k;
		}

		return result;
	}

	int solve(int require) {
		int n = 0;
		for (int i = 1; ; ++i) {
			n += i;
			if (factorCount(n) >= require) {
				return n;
			}
		}

		return n;
	}

	void init() {
		initPrime();
		primes.reserve(100000);
		for (int i = 2; i <= PRIME_N; ++i) {
			if (isPrime(i))
				primes.push_back(i);
		}
	}
};

const int N = 500;
int factorCount(int n) {
	int result = 0;
	for (int i = 1; i <= (int)sqrt(n); ++i) {
		if (n % i == 0) {
			++ result;
			if (n / i != i)
				++result;
		}

		if (result > N)
			break;
	}

	return result;
}

int main() {
	int X = 0;
	int k = 0;
	
	for (int i = 1; ; ++i) {
		X += i;
		if (X <= N)
			continue;

		if (factorCount(X) > N) {
			cout << X << endl;
			break;
		}
	}

	return 0;
}

// Brute Force
// 76576500