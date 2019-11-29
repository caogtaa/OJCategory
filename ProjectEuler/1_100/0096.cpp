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

FILE* pf = freopen("0096_input.txt", "r", stdin);

class Solution
{
public:
	int getResult() {
		if (!helper->solve()) {
			int k = 0;
		}

		return G[0][0] * 100 + G[0][1] * 10 + G[0][2];
	}

	long long solve()
	{
		for (int i = 0; i < 9; ++i) {
			G.push_back({});
			G.back().resize(9);
		}

		helper = make_unique<SuDokuHelper>(G);
		long long result = 0;
		string grid, kase;
		while (cin >> grid >> kase) {
			string line;
			for (int i = 0; i < 9; ++i) {
				cin >> line;
				for (int k = 0; k < 9; ++k) {
					G[i][k] = line[k] - '0';
				}
			}

			result += getResult();
		}

		return result;
	}

	vector<vector<int>> G;
	unique_ptr<SuDokuHelper> helper;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=96
// backtrace to search, use bit compress to speedup
