
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

class Solution
{
public:
	bool isPermutationOf(int a, int b) {
		static int appear[10];
		memset(appear, 0, sizeof(appear));
		while (a) {
			++ appear[a%10];
			a /= 10;
		}

		while (b) {
			-- appear[b%10];
			b /= 10;
		}

		for (int i = 0; i < 10; ++i) {
			if (appear[i] != 0)
				return false;
		}

		return true;
	}

	int solve()
	{
		int result = 1;
		double best = 87109.0 / 79180.0;	// example from question
		int N = 10000000;

		PrimeHelper helper;
		helper.initPhi(N);

		for (int i = 2; i <= N; ++i) {
			auto phi = helper.phi(i);
			if (Util::digitCount(phi) != Util::digitCount(i))
				continue;

			if (!isPermutationOf(phi, i))
				continue;

			if ((double)i / phi < best) {
				best = (double)i/phi;
				result = i;
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

// 一些优化思路：
// https://projecteuler.net/best_posts=070
// 1. 过滤素数，因为显然phi(p) = p-1，p和p-1之间无法互为排列
// 2. 由于phi(n)=n(1-1/p1)(1-1/p2)...(1-1/pk)，每次乘法都会减少phi(n)的大小
//    所以弱要n/phi(n)尽量小，应该让乘法数量减少，即n的素因数数目尽量少
// 3. 需要1-1/pk尽量小，所以需要pk尽量大，所以可在10^7附近求解
// 4. 综上只需要寻找两个素因数构成的合数，并可简化phi(n)计算为phi(p1xp2)=p1xp2(1-1/p1)(1-1/p2)=(p1-1)(p2-2)

// 以上2、3两点更多是需要直觉，缺少严格的论证。