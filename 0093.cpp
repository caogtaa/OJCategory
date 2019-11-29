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

double add(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

double mul(double a, double b) {
	return a * b;
}

double dv(double a, double b) {
	return a / b;
}

vector<function<double(double, double)>> op_func = {add, sub, mul, dv};

#define STEP(op, a, b, ans)	\
	ans = op_func[op](a, b);

#define MARK(ans, seq)	\
	if (ans - (int)ans <= 1e-9) {	\
		int v = (int)ans;	\
		if (v > 0 && v <= MAXV)	\
			appear[v] = seq;	\
	}

#define MAXV 3024
int appear[MAXV+1];	// 6*7*8*9=3024 is max value we can get

void calc(const vector<int>& n, const vector<int>& op, int s) {
	// n : nums
	// o : ops
	// s : seq

	// arrange parenthis
	double v1, v2, v3;
	do {
		STEP(op[0], n[0], n[1], v1);
		STEP(op[1], v1, n[2], v2);
		STEP(op[2], v2, n[3], v3);
		MARK(v3, s);
	} while (0);

	do {
		STEP(op[0], n[0], n[1], v1);
		STEP(op[2], n[2], n[3], v2);
		STEP(op[1], v1, v2, v3);
		MARK(v3, s);
	} while (0);
	
	do {
		STEP(op[1], n[1], n[2], v1);
		STEP(op[0], n[0], v1, v2);
		STEP(op[2], v2, n[3], v3);
		MARK(v3, s);
	} while (0);

	do {
		STEP(op[1], n[1], n[2], v1);
		STEP(op[2], v1, n[3], v2);
		STEP(op[0], n[0], v2, v3);
		MARK(v3, s);
	} while (0);

	// same as {0, 2, 1}
	// do {
	// 	STEP(op[2], n[2], n[3], v1);
	// 	STEP(op[0], n[0], n[1], v2);
	// 	STEP(op[1], v2, v1, v3);
	// 	MARK(v3, s);
	// } while (0);

	do {
		STEP(op[2], n[2], n[3], v1);
		STEP(op[1], n[1], v1, v2);
		STEP(op[0], n[0], v2, v3);
		MARK(v3, s);
	} while (0);
}

int check(const vector<int>& nums) {
	auto cp = nums;
	vector<int> ops;
	static int seq = 0;
	++ seq;
	do {
		for (int x = 0; x < 4; ++x) {
			ops.push_back(x);
			for (int y = 0; y < 4; ++y) {
				ops.push_back(y);
				for (int z = 0; z < 4; ++z) {
					ops.push_back(z);
					calc(cp, ops, seq);
					ops.pop_back();
				}
				ops.pop_back();
			}
			ops.pop_back();
		}
	} while (next_permutation(cp.begin(), cp.end()));

	for (int i = 1; i <= MAXV; ++i) {
		if (appear[i] != seq) {
			return i-1;
		}
	}

	return MAXV;
}

int best = 0;
vector<int> final_result;
void C94(vector<int>& nums, int x) {
	if (nums.size() == 4) {
		int r = check(nums);
		if (r > best) {
			best = r;
			final_result = nums;
		}
		return;
	}

	if (x > 9)
		return;

	// include x
	nums.push_back(x);
	C94(nums, x+1);
	nums.pop_back();
	
	// skip x
	C94(nums, x+1);
}

class Solution
{
public:
	int solve()
	{
		vector<int> nums;
		C94(nums, 1);

		// check final_result
		return 0;
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=93
// max possible value we can get is 6*7*8*9=3024
// number of permutations:
// operator: 4^3 = 64
// numbers selection: C(9,4) = 126
// brackets: different order to operate = 6
// 4 number permutation: 4! = 24
// the whold complexity is about 1 million, which can be solved by bruteforce
// note that intermedia non-integer is acceptable. e.g. 1/2*3*4
