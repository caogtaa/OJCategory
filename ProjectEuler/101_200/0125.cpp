
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	long long solve() {
		int MAX_N = 100000;
		long long LMT = 100000000;
		vector<long long> sum(MAX_N+1);
		sum[0] = 0;
		for (long long i = 1; i <= MAX_N; ++i) {
			sum[i] = sum[i-1] + i*i;
		}

		unordered_set<long long> cache;
		long long result = 0;
		long long num;
		for (int i = 0; i <= MAX_N; ++i) {
			for (int k = i+2; k <= MAX_N; ++k) {
				num = sum[k] - sum[i];
				if (num >= LMT)
					break;

				if (Util::isPalindromic(num)) {
					if (!cache.count(num)) {
						cache.insert(num);
						result += num;
					}
				}
			}
		}

		return result;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=125
// 暴力
// 枚举序列的起始位置和结束位置，判断和是否回文数
// 时间复杂度O(N^2)，N的数量级是sqrt(10^8) = 10^4
