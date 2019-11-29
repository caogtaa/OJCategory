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

#define PRIME_N 1000000

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
	bool isPalindromic(int N) {
		auto s = to_string(N);
		for (int i = 0; i < s.size() / 2; ++i) {
			if (s[i] != s[s.size()-1-i])
				return false;
		}

		return true;
	}

	int solve() {
		initPrime();
		int cnt = 0;
		for (int i = 2; i < PRIME_N; ++i) {
			if (isPrime(i) && ++cnt == 10001)
				return i;
		}

		return -1;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	// = 104743
	return 0;
}
