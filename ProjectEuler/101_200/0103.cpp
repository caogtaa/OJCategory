
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	long long solve() {
        long long result = 0;
		result = accumulate(candidate.begin(), candidate.end(), 0);
		

		return result;
	}

    vector<int> candidate = {20, 31, 38, 39, 40, 42, 45};
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=103
// 方案检查计算量 C(7,1)+C(7,2)+C(7,3)+...+C(7,6) = 216
// 方案搜索下界 {11, 18, 19, 20, 22, 25, 26}，方案数 = 245,565,918