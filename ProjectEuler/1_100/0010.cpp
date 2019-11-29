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
public:
	bool isPalindromic(int N) {
		auto s = to_string(N);
		for (int i = 0; i < s.size() / 2; ++i) {
			if (s[i] != s[s.size()-1-i])
				return false;
		}

		return true;
	}

	long long solve(int N) {
		initPrime();
		long long result = 0;
		for (int i = 2; i < N; ++i) {
			if (isPrime(i))
				result += i;
		}

		return result;
	}
};

int main() {
	auto s = new Solution();
	
	cout << s->solve(2000000) << endl;
	// = 142913828922
	return 0;
}
