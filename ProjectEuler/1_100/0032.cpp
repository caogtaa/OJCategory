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
	void check(int A, int B) {
		static int id = 0;
		++ id;

		int product = A * B;
		int d;
		if (Util::digitCount(A) + Util::digitCount(B) + Util::digitCount(product) != 9)
			return;

		while (product) {
			d = product % 10;
			if (d == 0 || visited[d] || checkAppear[d] == id)
				return;

			checkAppear[d] = id;
			product /= 10;
		}

		// find a valid Pandigital product
		collection.insert(A * B);
	}

	void combineB(int A, int cb, int preB) {
		if (cb == 0) {
			check(A, preB);
			return;
		}
		for (int i = 1; i <= 9; ++i) {
			if (visited[i])
				continue;

			visited[i] = true;
			combineB(A, cb-1, preB*10 + i);
			visited[i] = false;
		}
	}
	
	void combineA(int ca, int preA, int cb) {
		if (ca == 0) {
			combineB(preA, cb, 0);
			return;
		}

		for (int i = 1; i <= 9; ++i) {
			if (visited[i])
				continue;

			visited[i] = true;
			combineA(ca-1, preA*10 + i, cb);
			visited[i] = false;
		}
	}

	int solve(int N)
	{
		visited.resize(10);
		checkAppear.resize(10);
		int cc;
		for (int ca = 1; ca <= 9; ++ca) {
			for (int cb = ca; cb <= 9; ++cb) {
				cc = 9 - ca - cb;
				if (ca + cb == cc+1 || ca + cb == cc) {
					combineA(ca, 0, cb);
				}
			}
		}

		int result = 0;
		for (auto x : collection)
			result += x;

		return result;
	}

public:
	vector<bool> visited;
	set<int> collection;

	// only used in function check(), check duplicate digit in number itself
	vector<int> checkAppear;
};

int main()
{
	Solution s;
	cout << s.solve(9) << endl;

	return 0;
}

/* 
all possible products are: [4396, 5346, 6952, 7254, 7632, 7852]
the total digit count is 9, so possible digit distribution are:
1. digit_1 * digit_4 = digit_4
2. digit_2 * digit_3 = digit_4
use brute force.
*/
