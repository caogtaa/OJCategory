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

#define m2(x)	(x)*(x)

class Solution
{
public:
	int check(int x1, int y1, int x2, int y2) {
		// OA is long side
		if (m2(x1) + m2(y1) == m2(x2) + m2(y2) + m2(x1-x2) + m2(y1-y2))
			return 1;

		// OB is long side
		if (m2(x2) + m2(y2) == m2(x1) + m2(y1) + m2(x1-x2) + m2(y1-y2))
			return 1;

		// AB is long side
		if (m2(x1-x2) + m2(y1-y2) == m2(x1) + m2(y1) + m2(x2) + m2(y2))
			return 1;

		return 0;
	}

	int solve()
	{
		int lmt = 50;
		int result = 0;
		for (int x1 = 0; x1 <= lmt; ++x1) {
			for (int y1 = 0; y1 <= lmt; ++y1) {
				if (x1 == 0 && y1 == 0)
					continue;

				for (int x2 = x1; x2 <= lmt; ++x2) {
					for (int y2 = 0; y2 <= lmt; ++y2) {
						if (x2 == 0 && y2 == 0)
							continue;

						// let (x2, y2) always be right to (x1, y1), or upper to (x1, y1) if x1==x2
						if (x2 == x1 && y2 <= y1)
							continue;

						result += check(x1, y1, x2, y2);
					}
				}
			}
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

// https://projecteuler.net/problem=91
// bruteforce
// let (x2, y2) always be right to (x1, y1), or upper to (x1, y1) if x1==x2
// there are 3 kind of right triangle:
// OA be the long side, OB be the long side or AB be the long side
