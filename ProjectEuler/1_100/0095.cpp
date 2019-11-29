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

#define MAXN 1000000
long long S[MAXN+1];
int visited[MAXN+1];
int chainLen[MAXN+1];

class Solution
{
public:
	void Func(int x, int pid) {
		// add factor primes[pid] in to num
		long long nxt;
		int p;
		int pre;
		for (; pid < _primes.size(); ++pid) {
			nxt = p = _primes[pid];
			nxt *= x;			
			if (nxt > MAXN)
				return;

			pre = x;
			while (nxt <= MAXN) {
				S[nxt] = S[pre] * p + S[x];
				Func(nxt, pid+1);
				pre = nxt;
				nxt *= p;
			}
		}
	}

	// non-recursive version, but not faster
	// void Func3() {
	// 	int k = 0;
	// 	int x;

	// 	qu[quLen].first = 1;
	// 	qu[quLen++].second = 0;

	// 	int pk;
	// 	long long nxt;
	// 	int p;
	// 	int pid;
	// 	int pre;
	// 	while (k < quLen) {
	// 		x = qu[k].first;
	// 		pid = qu[k].second;
	// 		for (; pid < primes.size(); ++pid) {
	// 			nxt = primes[pid];
	// 			nxt *= x;
	// 			if (nxt > MAXN)
	// 				break;

	// 			p = primes[pid];
	// 			pre = x;
	// 			while (nxt <= MAXN) {
	// 				S[nxt] = S[pre]*p + S[x];
	// 				qu[quLen].first = nxt;
	// 				qu[quLen++].second = pid+1;
	// 				pre = nxt;
	// 				nxt *= p;
	// 			}
	// 		}

	// 		++k;
	// 	}
	// }

	
	int findAmicableChain(int x) {
		static int seq = 0;
		++seq;

		if (chainLen[x] != 0)
			return chainLen[x];

		vector<int> qu;
		visited[x] = seq;
		qu.push_back(x);

		long long nxt = x;
		while (true) {
			nxt = S[nxt];
			if (nxt <= 0 || nxt > MAXN) {
				// find ray
				for (auto n : qu) {
					chainLen[n] = -1;
				}
				return chainLen[x];
			}

			if (visited[nxt] == seq) {
				// find chain
				int i = qu.size() - 1;
				while (i >= 0) {
					if (qu[i] == nxt)
						break;
					--i;
				}

				for (int k = i; k < qu.size(); ++k) {
					chainLen[qu[k]] = qu.size() - i;
				}

				while (--i >= 0) {
					chainLen[qu[i]] = -1;
				}

				return chainLen[x];
			}

			if (visited[nxt] != 0) {
				// find ray
				for (auto n : qu) {
					chainLen[n] = -1;
				}
				return chainLen[x];
			}
			
			visited[nxt] = seq;
			qu.push_back(nxt);
		}
	}

	long long solve()
	{
		PrimeHelper helper;
		helper.init(MAXN);
		_primes = helper.getPrimes(2, MAXN);

		S[1] = 1;
		Func(1, 0);

		for (int i = 1; i <= MAXN; ++i) {
			if (S[i] > 0)
				S[i] -= i;
		}

		long long result = -1;
		int best = 0;
		for (int i = 2; i <= MAXN; ++i) {
			if (S[i] > 0 && S[i] <= MAXN) {
				auto t = findAmicableChain(i);
				if (t > best) {
					best = t;
					result = i;
				}
			}
		}

		return result;
	}

	vector<int> _primes;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=95
// 算法关键在于高效打表求出所有数的因子和S(x)
// 通过素数构造的方式递推求出所有数的因子和，简单起见求得因子和中包含1和数字本身
// 以 6 = 1*2*3举例，S(6) = 6
// 加入因子5时，30=1*2*3*5，S(30)=1+2+3+(1*5)+(2*5)+(3*5)，于是S(6*5)=S(6)+S(6)*5
// 加入另一个因子5时，150=1*2*3*5^2，S(150)=1+2+3+(1*5)+(2*5)+(3*5)+(1*25)+(2*25)+(3*25)
// S(6*5*5)=S(6)+S(6)*(5+5^2)=S(6)*(1+5^1+5^2)
// 递推：S(6*5*5)=S(6*5)*5+S(6)
// 以此类推所有的数字

// 简单分析可知，这种方法可以枚举到所有的数字
// 在已经得到素数表的前提下，时间复杂度是O(N)，递归算法的深度是O(logN)
// 基于S(x)来求每个数所在的amicable chain长度就比较简单了
