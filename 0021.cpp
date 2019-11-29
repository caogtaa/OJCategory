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
	int sumOfDivisor(int x) {
		int result = 0;
		for (int i = 2; i <= (int)sqrt(x); ++i) {
			if (x % i == 0) {
				result += i;
				if (x / i != i)
					result += x / i;
			}
		}

		return result + 1;	// +1 to include number 1
	}

	int solve() {
		int k;
		int result = 0;
		for (int i = 2; i < 10000; ++i) {
			k = sumOfDivisor(i);
			if (k != i && sumOfDivisor(k) == i)
				result += i;
		}

		return result;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	// Brute Force

	return 0;
}
