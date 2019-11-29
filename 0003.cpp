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

#define PRIME_N 775200

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
public:
	long long solve(long long N) {
		for (long long i = sqrt(N); i >= 2; --i) {
			if (isPrime(i) && N % i == 0)
				return i;
		}

		return 1;
	}
};

int main() {
	auto s = new Solution();
	initPrime();
	long long N = 600851475143LL;
	double x = sqrt(N);
	cout << s->solve(N) << endl;

	// = 6857
	return 0;
}
