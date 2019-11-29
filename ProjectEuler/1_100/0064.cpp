
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

class Solution
{
public:
	int solve()
	{
		int period;
		int result = 0;
		for (int i = 2; i <= 10000; ++i) {
			auto fraction = Util::sqrtContinuedFraction(i);
			auto period = fraction.size() - 1;
			if (period & 1)
				++ result;
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

// https://www.yuque.com/caomou/mgxqtg/melatw