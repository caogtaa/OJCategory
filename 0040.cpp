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

class Solution
{
public:
	int solve()
	{
		// init();
		int result = 1;
		for (int i=1; i <= 1000000; i*=10) {
			result *= Util::kthDigitOfIDF(i-1);
		}

		return result;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;
	return 0;
}
