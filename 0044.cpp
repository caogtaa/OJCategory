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
	int solve() {
		vector<int> pentagons;
		pentagons.reserve(3000);
		for (int i = 1; i <= 3000; ++i) {
			pentagons.push_back(i*(3*i-1)/2);
		}

		int D;
		int pk, pj;
		for (int i = 0; i < pentagons.size(); ++i) {
			D = pentagons[i];
			for (int j = 0; j < pentagons.size(); ++j) {
				pj = pentagons[j];
				pk = D + pj;
				// check if pk exists in pentagons
				auto iter = lower_bound(pentagons.begin(), pentagons.end(), pk);
				if (iter == pentagons.end() || *iter != pk)
					continue;

				// check if pk+pj exists in pentagons
				iter = lower_bound(pentagons.begin(), pentagons.end(), pj+pk);
				if (iter == pentagons.end() || *iter != pj+pk)
					continue;

				return D;
			}
		}

		return -1;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// brute force
// try each D and pj, check if D+pj=pk is pentagon and pj+pk is pentagon