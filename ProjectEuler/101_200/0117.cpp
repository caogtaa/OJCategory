
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:

	long long solve() {
		F[0] = F[1] = 1;
		for (int i = 2; i <= 50; ++i) {
			F[i] = F[i-1];
			for (int k = 2; k <= 4; ++k) {
				if (i-k >= 0) {
					F[i] += F[i-k];
				}
			}
		}

		return F[50];
	}

private:
	long long F[51];
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=117
// 动态规划
// 同0116
