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
#include "helper.h"

using namespace std;

class Solution {
public:
	int Func(int k, int n) {
		if (n == 0)
			return 1;

		if (k >= 8)
			return 0;

		int& ret = F[k][n];
		if (ret != -1)
			return ret;
		
		ret = Func(k+1, n);	// without current coin
		if (coins[k] <= n)
			ret += Func(k, n-coins[k]);

		return ret;
	}

	int solve(int N) {
		coins = vector<int>{1, 2, 5, 10, 20, 50, 100, 200};
		memset(F, -1, sizeof(F));
		return Func(0, N);
	}

public:
	vector<int> coins;
	int F[8][201];
};

int main() {
	Solution s;
	cout << s.solve(200) << endl;
	// simple DP

	return 0;
}
