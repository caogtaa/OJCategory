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
		int a, b, c, c2;
		vector<int> count(N+1);
		for (a = 1; a <= N; ++a) {
			for (b = a; b <= N; ++b) {
				c2 = a * a + b * b;
				c = (int)sqrt(c2);
				if (a+b+c <= N && c * c == c2) {
					++ count[a+b+c];
				}
			}
		}
		
		int best = 0;
		int result = 0;
		for (int i = 1; i <= N; ++i) {
			if (count[i] > best) {
				best = count[i];
				result = i;
			}
		}

		return result;
	}
};

int main()
{
	Solution s;
	cout << s.solve(1000) << endl;
	return 0;
}

// enum a, b in range [1,1000], count each integer c
// O(N^2) for N <= 1000