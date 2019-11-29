#include "common_headers.h"
#include "helper.h"

using namespace std;

#define MAXN 10000
#define CHAIN_LEN	5

int dfs_count[5];	// DFS performance check

class Solution
{
public:
	bool isPrime(int p) {
		if (p <= MAXN) {
			return helper.isPrime(p);
		}

		return PrimeHelper::millerRabinPrimeTest(p);
	}

	bool chainable(int x) {
		for (auto c : chain) {
			if (candidates[c].count(x) == 0)
				return false;
		}

		return true;
	}

	int search(int p, int rest) {
		++ dfs_count[rest];
		if (rest == 0) {
			return accumulate(chain.begin(), chain.end(), 0);
		}

		int result = INT_MAX;
		if (candidates[p].size() >= rest-1) {
			for (auto x : candidates[p]) {
				if (!chainable(x))
					continue;

				chain.push_back(x);
				result = min(result, search(x, rest-1));
				chain.pop_back();
			}
		}

		return result;
	}

	int solve() {
		helper.init(MAXN);
		auto primes = helper.getPrimes(2, MAXN);

		int nxt;
		for (int i = 0; i < primes.size(); ++i) {
			for (int k = i + 1; k < primes.size(); ++k) {
				if (isPrime(primes[i] + primes[k] * pow(10.0, Util::digitCount(primes[i]))) &&
					isPrime(primes[k] + primes[i] * pow(10.0, Util::digitCount(primes[k])))) {
					candidates[primes[i]].insert(primes[k]);
				}
			}
		}

		int result = INT_MAX;
		for (auto p : primes) {
			chain.push_back(p);
			result = min(result, search(p, CHAIN_LEN-1));
			chain.pop_back();
		}

		return result;
	}

	PrimeHelper helper;
	unordered_set<int> candidates[MAXN+1];
	vector<int> chain;
};

int main()
{
	Solution* s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=60
// get all primes <= 10000, and check all combinations
// DFS to search all possible set with size 5, check each number with current set before adding to set
// the search branch converge quickly
// with primes in [2,10000], DFS function invoke count with depth [0:4] = [1229, 18040, 9866, 294, 1]
// with primes in [0,20000], DFS function invoke count with depth [0:4] = [2262, 47471, 29189, 769, 2]
// use Miller_Rabin to test big prime
