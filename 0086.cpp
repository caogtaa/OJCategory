
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

class TripleFinder {
public:
	TripleFinder(int M): _M(M) {}

	int check(int a, int b) {
		// a, b are short edges of right triangle
		// a < b, and a, b, sqrt(a^2+b^2) is primitive Pythagorean triple
		int result = 0;
		int copya = a;
		int copyb = b;

		// find all a, x, y that 
		// 1. b = x+y
		// 2. a > x > y
		// 3. x+y <= 2a
		while (copya <= _M && copyb <= 2*copya) {
			// fix copya
			int halfb = copyb/2 + (copyb&1);
			result += min(copya-halfb+1, copyb/2);
			copya += a;
			copyb += b;
		}

		copya = a;
		copyb = b;

		// find all b, x, y that 
		// 1. a = x+y
		// 2. b > x > y
		// 3. x+y <= 2b
		while (copyb <= _M && copya <= 2*copyb) {
			int halfa = copya/2 + (copya&1);
			result += min(copyb-halfa+1, copya/2);
			copya += a;
			copyb += b;
		}

		return result;
	}

	int find(int a, int b, int c) {
		int result = check(a, b);

		if (result > 0) {
			result += find(a-2*b+2*c, 2*a-b+2*c, 2*a-2*b+3*c);
			result += find(a+2*b+2*c, 2*a+b+2*c, 2*a+2*b+3*c);
			result += find(-a+2*b+2*c, -2*a+b+2*c, -2*a+2*b+3*c);
		}

		return result;
	}

	int find2(int a, int b, int c) {
		int result = 0;
		for (int n = 1; n <= 1000; ++n) {
			for (int m = n+1; m <= 1000; ++m) {
				if (Util::gcd(m, n) > 1)
					continue;

				int a = m*m - n*n;
				int b = 2*m*n;

				if ((m & 1) && (n & 1))
					continue;

				result += check(a, b);
			}
		}

		return result;
	}

	int _M;
};

int Func(int m) {
	int result = TripleFinder(m).find(3, 4, 5);
	return result;
}

class Solution
{
public:
	int upper_bound_on_function(int first, int last, function<int(int)> f, int val) {
		int count = last - first;
		while (0 < count) { // divide and conquer, find half that contains answer
			int c2 = count >> 1;
			int mid = first + c2;
			if (f(mid) > val) {
				count = c2;
			} else {
				first = mid + 1;
				count -= c2 +1;
			}
		}

		return first;
	}

	int solve()
	{
		// find 1st x that Func(x) > 2000000
		int m = upper_bound_on_function(0, 10000, Func, 1000000);
		return m;
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=86
// https://www.yuque.com/caomou/mgxqtg/asq7iu