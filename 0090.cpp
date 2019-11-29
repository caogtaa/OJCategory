
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

#define CHECKN(x, y)	\
	if (!(appearL[x] == seq && appearR[y] == seq) && !(appearL[y] == seq && appearR[x] == seq)) { \
		return 0;	\
	}

#define CHECKN_2(x)	\
	if (!(appearL[x] == seq && (appearR[6] == seq || appearR[9] == seq)) && !(appearR[x] == seq && (appearL[6] == seq || appearL[9] == seq))) { \
		return 0;	\
	}

int check(const vector<int>& L, const vector<int>& R) {
	static int seq = 0;
	static int appearL[10];
	static int appearR[10];

	++ seq;
	for (auto x : L) {
		appearL[x] = seq;
	}

	for (auto y : R) {
		appearR[y] = seq;
	}

	CHECKN(0, 1);
	CHECKN(0, 4);
	CHECKN_2(0);	// check 09
	CHECKN_2(1);	// check 16
	CHECKN(2, 5);
	CHECKN_2(3);	// check 36
	CHECKN_2(4);	// check 49
	// CHECKN_2(4);	// check 64
	CHECKN(8, 1);

	return 1;
}

int F(vector<int>& L, vector<int>& R, int x, int y) {
	if (L.size() == 6 && R.size() == 6) {
		return check(L, R);
	}

	int result = 0;
	if (L.size() < 6) {
		int restX = 9-x+1;
		if (restX > 0) {
			// try add x to L
			L.push_back(x);
			result += F(L, R, x+1, y);
			L.pop_back();

			// try L skip x 
			if (6-L.size() < restX) {
				result += F(L, R, x+1, y);
			}
		}
	} else {
		int restY = 9-y+1;
		if (restY > 0) {
			R.push_back(y);
			result += F(L, R, x, y+1);
			R.pop_back();

			// try R skip y
			if (6-R.size() < restY) {
				result += F(L, R, x, y+1);
			}
		}
	}

	return result;
}

class Solution
{
public:
	int solve()
	{
		int result = 0;
		vector<int> L, R;
		result = F(L, R, 0, 0);
		return result / 2;
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
// bruteforce
// 一个可行解，把两个骰子互换得到另一个可行解，这个解不重复计数。这是题目中未描述清楚的点。
// 另外实测发现，不存左右筛子相同的可行解。
// 进行测试的解数量为 44100（即check方法调用次数）
// 非递归写法可以使用2^10的枚举 + bitCount测试，时间复杂度相同。都为O(2^20 * C)，其中C为解的测试耗时