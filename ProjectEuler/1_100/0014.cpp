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

using namespace std;

class Solution {
public:
	long long solve() {
		long long nxt;
		long long result = 1;
		long long best = 1;
		long long largest = 1;
		vector<long long> qu;
		_cache.reserve(4000000);
		_cache[1] = 1;
		for (long long i = 2; i < 1000000; ++i) {
			nxt = i;

			do {
				qu.push_back(nxt);
				if (nxt & 1) {
					nxt = nxt * 3 + 1;
					largest = max(largest, nxt);
				} else {
					nxt >>= 1;	
				}

				auto iter = _cache.find(nxt);
				if (iter != _cache.end()) {
					long long len = iter->second + qu.size();
					if (len > best) {
						best = len;
						result = i;
					}

					for (auto x : qu) {
						_cache[x] = len--;
					}
					qu.resize(0);
					break;
				}
			} while (true);
		}

		return result;
	}

	unordered_map<long long, long long> _cache;
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;

	return 0;
}

// https://projecteuler.net/problem=14
// bruteforce
// cache size is 2,168,611
// largest number in chain is 56,991,483,520