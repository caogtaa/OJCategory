
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	long long solve() {
		PrimeHelper helper;
		helper.init(1000000);
		auto primes = helper.getPrimes(2, 1000000);

		long long n;
		long long pn;
		long long sum;
		long long lmt = (long long)1e10;
		for (int i = 0; i < primes.size(); i += 2) {
			n = i+1;
			pn = primes[i];
			sum = pn * n * 2;
			if (sum > lmt)
				return n;
		}

		return -1;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=123
// 数论分析
// 二项式展开
// https://www.yuque.com/caomou/mgxqtg/eagl0b