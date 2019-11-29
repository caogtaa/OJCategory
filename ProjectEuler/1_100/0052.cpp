#include "common_headers.h"
#include "helper.h"

using namespace std;

class Solution
{
public:
	vector<int> getAppear(int n) {
		vector<int> result(10);
		while (n) {
			++ result[n % 10];
			n /= 10;
		}

		return result;
	}

	bool check(int n) {
		auto appear = getAppear(n);
		auto digitCount = Util::digitCount(n);
		if (digitCount != Util::digitCount(n*6))
			return false;

		for (int i = 6; i >= 2; --i) {
			if (getAppear(n*i) != appear)
				return false;
		}

		return true;
	}

	int solve() {
		int base = 100;
		while (true) {
			for (int i = 0; i < base; ++i) {
				if (check(base + i)) {
					return base + i;
				}
			}
			base *= 10;
		}

		return -1;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// solution 1: brute force

// solution 2: nice solution in forum
// https://projecteuler.net/thread=52#96