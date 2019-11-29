#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common_headers.h"
#include "helper.h"

using namespace std;

int F[10000000];

int digitsSquareSum(int n) {
	int result = 0;
	int d;
	while (n) {
		d = n % 10;
		result += d * d;
		n /= 10;
	}

	return result;
}

class Solution
{
public:

	int solve()
	{
		F[1] = 1;
		F[89] = 89;

		int result = 0;
		vector<int> seq;
		int nxt;
		for (int i = 2; i < 10000000; ++i) {
			if (F[i] == 0) {
				seq.push_back(i);
				nxt = digitsSquareSum(i);
				while (F[nxt] == 0) {
					seq.push_back(nxt);
					nxt = digitsSquareSum(nxt);
				}

				for (auto k : seq) {
					F[k] = F[nxt];
				}

				seq.clear();
			}

			result += (F[i] == 89);
		}
		return result;
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=92
// bruteforce
