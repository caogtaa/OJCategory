
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

	int solve()
	{
		set<int> records;
		int lmt = 50000000 - 1;
		PrimeHelper helper;
		helper.init(sqrt(lmt)*2);
		auto primes = helper.getPrimes(2, sqrt(lmt)*2);

		int maxz = (int)pow(lmt, 0.25);
		int zid = upper_bound(primes.begin(), primes.end(), maxz) - primes.begin() - 1;

		int result = 0;
		while (zid >= 0) {
			// find (x, y) that x^2 + y^3 + z^4 < 50000000;
			int maxy = (int)pow(lmt - (int)pow(primes[zid], 4.0), 1.0/3);
			int yid = upper_bound(primes.begin(), primes.end(), maxy) - primes.begin() - 1;
			while (yid >= 0) {
				int acc = (int)pow(primes[zid], 4.0) + (int)pow(primes[yid], 3.0);
				int rest = lmt - acc;
				int maxx = (int)sqrt(rest);
				int xid = upper_bound(primes.begin(), primes.end(), maxx) - primes.begin() - 1;
				while (xid >= 0) {
					records.insert(acc + primes[xid] * primes[xid]);
					-- xid;
				}

				// 没有考虑重复数字，错误答案
				// if (rest >= 4) {
				// 	int maxx = (int)sqrt(rest);
				// 	int xid = upper_bound(primes.begin(), primes.end(), maxx) - primes.begin() - 1;
				// 	int xxxx = primes[zid]*primes[zid]*primes[zid]*primes[zid] + primes[yid]*primes[yid]*primes[yid] + primes[xid]*primes[xid];
				// 	int xxxy = primes[zid]*primes[zid]*primes[zid]*primes[zid] + primes[yid]*primes[yid]*primes[yid] + primes[xid+1]*primes[xid+1];
				// 	if (xxxx >= lmt || xxxy < lmt) {
				// 		int k = 0;
				// 	}
				// 	result += xid + 1;
				// }
				-- yid;
			}

			-- zid;
		}

		return records.size();
	}
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=87
// get prime table, bruteforce to find all possible number and unique