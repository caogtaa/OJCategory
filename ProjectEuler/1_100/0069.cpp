
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
		int result = 1;
		double best = 1.0;
		int N = 1000000;

		PrimeHelper helper;
		helper.initPhi(N);

		for (int i = 2; i <= N; ++i) {
			auto phi = helper.phi(i);
			if ((double)i / phi > best) {
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

// Another simple solution is make multiplication of small primes
// to make x/phi(x) large and phi(x) small, 
// it's nice to have every 2nd, 3nd and 5th number not be relatively prime to x
// which means x should be composite of primes, and as many primes as possible