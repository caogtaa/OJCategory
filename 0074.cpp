
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
	int chainLength(int n) {
		if (_chainLen[n] != -1)
			return _chainLen[n];

		unordered_map<int, int> cache;
		cache[n] = 0;

		int next;
		int copyn;
		while (1) {
			next = 0;
			copyn = n;
			while (copyn) {
				next += _factorial[copyn % 10];
				copyn /= 10;
			}

			if (_chainLen[next] != -1) {
				for (auto iter = cache.begin(); iter != cache.end(); ++iter) {
					_chainLen[iter->first] = cache.size() + _chainLen[next] - cache[iter->first];
				}

				return cache.size() + _chainLen[next];
			}

			if (cache.find(next) != cache.end()) {
				// find a loop
				int loopStart = cache[next];
				int loopSize = cache.size() - loopStart;
				for (auto iter = cache.begin(); iter != cache.end(); ++iter) {
					if (iter->second >= loopStart)
						_chainLen[iter->first] = loopSize;
					else
						_chainLen[iter->first] = cache.size() - cache[iter->first];
				}

				return cache.size();
			}

			cache[next] = cache.size();
			n = next;
		}

		// impossible
		return -1;
	}

	int solve()
	{
		int result = 0;
		_factorial[0] = _factorial[1] = 1;
		for (int i = 2; i < 10; ++i) {
			_factorial[i] = i * _factorial[i-1];
		}

		_chainLen.resize(3000001);
		fill(_chainLen.begin(), _chainLen.end(), -1);

		for (int i = 1; i < 1000000; ++i) {
			if (60 == chainLength(i))
				++ result;
		}

		return result;
	}

	int _factorial[10];
	vector<int> _chainLen;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=74
// bruteforce cost too much time
// cache chain length once calculated

