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

	bool isAbundantNumber(int x) {
		return sumOfDivisor(x) > x;
	}

	int solve() {
		vector<int> target;
		for (int i = 2; i <= N; ++i) {
			if (isAbundantNumber(i)) {
				target.push_back(i);
			}
		}

		int sum = 0;
		memset(F, 0, sizeof(F));
		for (int i = 0; i < target.size(); ++i) {
			for (int k = 0; k < target.size(); ++k) {
				int v = target[i] + target[k];
				if (v > N)
					continue;
				
				F[v] = true;
			}
		}

		for (int i = 1; i <= N; ++i) {
			if (!F[i])
				sum += i;
		}

		return sum;
	}

public:
	static const int N = 28123;
	bool F[N+1];
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	// = 
	// find out all abundant number less than N
	// use O(N^2) to find all target number
	// sum up all target number

	delete s;
	return 0;
}
