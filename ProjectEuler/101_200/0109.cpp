
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	int Func(int s) {
		int result = 0;
		for (int i = 0; i < scores.size(); ++i) {
			for (int k = i; k < scores.size(); ++k) {
				if (scores[i]+scores[k] < s) {
					++ result;
				}
			}
		}

		return result;
	}

	long long solve() {
		long long result = 0;
		scores.reserve(20 * 3 + 2);
		for (int i = 1; i <= 20; ++i) {
			scores.push_back(i);
			scores.push_back(i*2);
			scores.push_back(i*3);
		}
		scores.push_back(0);	// outside board
		scores.push_back(25);
		scores.push_back(25*2);
		sort(scores.begin(), scores.end());

		for (int i = 1; i <= 20; ++i) {
			result += Func(100-i*2);
		}
		result += Func(100-25*2);

		return result;
	}

private:
	vector<int> scores;
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=109
// 题意：掷飞镖3次，以double结尾
// 思路：先确定第3次的double，枚举前两次
// 暴力