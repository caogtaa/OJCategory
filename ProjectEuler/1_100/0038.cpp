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
	int pandigitalMultiple(int x) {
		int v;	// product value
		int d;	// digit
		vector<bool> visited(10);
		int result = 0;
		int digitCount;
		for (int n = 1; n <= 9; ++n) {
			v = x * n;
			digitCount = Util::digitCount(v);
			if (Util::digitCount(result) + digitCount > 9)
				return -1;

			result *= (int)pow(10, digitCount);
			result += v;

			while (v > 0) {
				d = v % 10;
				v /= 10;
				if (d == 0)
					return -1;

				if (visited[d])
					return -1;

				visited[d] = true;
			}

			if (Util::digitCount(result) == 9)
				return result;
		}

		return -1;	// will not happen
	}
	int solve()
	{
		int result = 123456789;	// with x = 1 and n = 9
		for (int x = 2; x <= 9999; ++x) {
			result = max(result, pandigitalMultiple(x));
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

/* possible solutions:
digit_1 * (1~9)
digit_2 * (1~4)
digit_3 * (1~3)
digit_4 * (1~2)
so the upper bound of such number is 9999
*/