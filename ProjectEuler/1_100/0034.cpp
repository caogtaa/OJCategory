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
		vector<int> result;
		for (int i = 10; i <= N; ++i) {
			if (i == Util::digitFactorialSum(i)) {
				result.push_back(i);
			}
		}

		int sum = 0;
		for_each(result.begin(), result.end(), [&sum](int v) { sum += v; });
		return sum;
	}
};

int main()
{
	Solution s;
	cout << s.solve(2540160) << endl;

	return 0;
}

// when should brute force algorithm halt ?
// 9! = 362880
// 7 * 9! = 2540160
// the upper bound of possible number is 2540160
// number after this always satisfy "digit factorials < number"

// only 2 numbers satisfy n == digitFactorialSum(n)
// 145, 40585
