
#include <common_headers.h>
#include <helper.h>

using namespace std;

long long lmt = (long long)1e16;

class Solution {
public:
	long long solve() {
		vector<long long> records;

		for (long long i = 2; i <= 135; ++i) {
			long long n = i;
			while (n <= lmt) {
				if (n >= 10 && Util::digitSum(n) == i) {
					records.push_back(n);
				}

				n *= i;
			}
		}

		sort(records.begin(), records.end());
		return records[30-1];
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=119
// 暴力
// 问题范围确定，先假设a[30]在long long能表达的范围内
// 假设a[30]是15位，各个位相加后，最大是135
// 遍历1~135，取<=15位数的幂，对结果进行排序即可