
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	int A(int n) {
		int x = 1;
		int result = 1;
		while (true) {
			x %= n;
			if (x == 0)
				return result;

			x *= 10;
			++ x;
			++ result;
		}

		return -1;
	}

	long long solve() {
		PrimeHelper helper;
		helper.init(1000000);

		int sum = 0;
		int counter = 0;
		for (int n = 91; n <= 1000000; ++n) {
			if (helper.isPrime(n))
				continue;

			if (Util::gcd(n, 10) != 1)
				continue;

			if ((n-1) % A(n) == 0) {
				sum += n;
				if (++counter >= 25)
					break;
			}
		}

		return sum;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=130
// 暴力
// 虽然是45%的题目但是比想象中简单很多
// 满足 n-1能被A(n)除尽的第25个数是149253
