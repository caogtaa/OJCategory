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
		int result = 0;
		for (int i = 999; i >= 100; --i) {
			for (int k = 999; k >= 100; --k) {
				if (isPalindromic(i * k)) {
					result = max(result, i * k);
				}
			}
		}

		return result;
	}
};

int main() {
	auto s = new Solution();
	// initPrime();
	// long long N = 600851475143LL;
	cout << s->solve() << endl;
	// = 906609
	return 0;
}
