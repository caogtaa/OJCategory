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
	bool checkEqual(int a, int b, int x, int y) {
		int gcd = Util::gcd(a, b);
		a /= gcd; b /= gcd;

		gcd = Util::gcd(x, y);
		x /= gcd;
		y /= gcd;
		return a == x && b == y;
	}

	bool check(int a, int b) {
		if (a % 10 == 0 || b % 10 == 0)
			return false;

		int gcd = Util::gcd(a, b);
		if (gcd == 1)
			return false;

		if (a%10 == b%10 && checkEqual(a, b, a/10, b/10)) {
			return true;
		}
		if (a%10 == b/10 && checkEqual(a, b, a/10, b%10)) {
			return true;
		}
		if (a/10 == b%10 && checkEqual(a, b, a%10, b/10)) {
			return true;
		}
		if (a/10 == b/10 && checkEqual(a, b, a%10, b%10)) {
			return true;
		}

		return false;
	}

	int solve()
	{
		// 2 digits
		// less than one in value, so b > a
		vector<pair<int,int>> fractions;
		for (int a = 11; a <= 99; ++a) {
			for (int b = a + 1; b <= 99; ++b) {
				if (check(a, b)) {
					fractions.emplace_back(make_pair(a, b));
				}
			}
		}

		int x = 1, y = 1;
		for (auto& f : fractions) {
			x *= f.first;
			y *= f.second;
		}

		int gcd = Util::gcd(x, y);
		return y / gcd;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;
	// = 100, superisingly
	// [(16,64),(19,95),(26,65),(49,98)]


	return 0;
}
