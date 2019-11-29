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

#define CHECK(s)	\
	if ((s) * (s+2) == target && (s) % 3 != 0) {	\
		if ((s) * 2 > 1000000000)	\
			break;	\
		result += (s)*2;	\
		continue;	\
	}

class Solution
{
public:
	long long solve()
	{
		long long result = 0;
		long long s;
		long long r;
		long long target;
		for (long long i = 2; ; ++i) {
			target = i * i * 3;
			s = sqrt(target);
			if (s > 1000000000)
				break;

			// in case r(r+2) == target
			// s=r
			r = s;
			if (r % 3 != 0 && r*(r+2) == target) {
				if (r*2 > 1000000000)
					break;
				result += r*2;
				continue;
			}

			r = s-1;
			if (r % 3 != 0 && r*(r+2) == target) {
				if (r*2 > 1000000000)
					break;
				result += r*2;
				continue;
			}

			// in case r(r-2) == 3*target
			// s=r-2
			r = s+2;
			if (r % 3 != 0 && r*(r-2) == target) {
				if (r*2 > 1000000000)
					break;
				result += r*2;
				continue;
			}

			r = s+1;
			if (r % 3 != 0 && r*(r-2) == target) {
				if (r*2 > 1000000000)
					break;
				result += r*2;
				continue;
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

// https://projecteuler.net/problem=94
// 根据海伦公式求三角形面积
// A = sqrt(s(s-a)(s-b)(s-c))，A是三角形面积，S是半周长，(a,b,c)分别为三边
// a,b等边，则A = sqrt(s(s-a)(s-a)(s-c))
// 要使A为整数，则表达式必须为完全平方数，则两项(s-a)可以忽略，只考虑s(s-c)为完全平方数
// 设s(s-c) = SQ，其中SQ为某个完全平方数
// 由于abs(c-a) = 1，c接近2*s/3。分两种情况考虑
// 1. c较长，c-a=1，则c=(2*s+2)/3
//	代入得s(s-2) = 3*SQ
// 2. c较短，a-c=1，则c=(2*s-2)/3 
//	代入得s(s+2) = 3*SQ
// 分别求解上面两个式子尝试s即可，注意s%3!=0，否则三边就同长度了

// 518408346
// 论坛里有个更加数学的做法，可以演变为求Pell公式的解
// https://projecteuler.net/thread=94