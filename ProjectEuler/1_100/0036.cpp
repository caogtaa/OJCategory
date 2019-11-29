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
	int solve(int N)
	{
		int sum = 0;
		for (int i = 0; i < N; ++i) {
			if (Util::isPalindromic(i, 10) && Util::isPalindromic(i, 2)) {
				sum += i;
			}
		}

		return sum;
	}
};

int main()
{
	Solution s;
	cout << s.solve(1000000) << endl;

	return 0;
}
