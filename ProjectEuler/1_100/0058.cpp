#include "common_headers.h"
#include "helper.h"

using namespace std;

class Solution
{
public:
	bool isPrimeSafe(int n, const std::vector<int>& primes) {
		if (n <= 1000000)
			return helper.isPrime(n);

		int limit = (int)sqrt(n);
		int p;
		for (int i = 0; i < primes.size(); ++i) {
			p = primes[i];
			if (p > limit) {
				return true;
			}

			if (n % p == 0) {
				return false;
			}
		}

		_ASSERT(false);	// too large number 10^12
		return false;
	}

	int solve() {
		helper.init(1000000);
		int total = 1;
		int primeCount = 0;

		auto primes = helper.getPrimes(2, 1000000);
		for (int round = 1; ; ++round) {
			int base = (round*2-1) * (round*2-1);
			for (int i = 0; i < 3; ++i) {
				base += round * 2;
				if (isPrimeSafe(base, primes)) {
					++ primeCount;
				}
			}

			total += 4;

			if (primeCount * 10 < total) {
				return round * 2 + 1;
			}
		}

		return -1;
	}

	PrimeHelper helper;
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// final fraction is 5248/52481
// number may exceed 10^6