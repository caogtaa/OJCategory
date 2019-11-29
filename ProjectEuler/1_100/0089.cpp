
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

FILE* pf = freopen("0089_input.txt", "r", stdin);

class Solution
{
public:
	int solve()
	{
		int result = 0;
		string s;
		while (cin >> s) {
			int num = Util::romanToInt(s);
			string s2 = Util::intToRoman(num);
			if (s != s2)
				result += s.size() - s2.size();
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

// https://projecteuler.net/problem=89