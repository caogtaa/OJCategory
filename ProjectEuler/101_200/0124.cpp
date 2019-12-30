
#include <common_headers.h>
#include <helper.h>

using namespace std;

#define MAXN 100000

class Solution {
public:
	long long solve() {
		PrimeHelper helper;
		helper.init(MAXN);
		auto radicals = helper.getRadicals(MAXN);

		vector<int> index(MAXN+1);
		for (int i = 0; i < index.size(); ++i) {
			index[i] = i;
		}

		sort(index.begin(), index.end(), [&radicals](int i, int j) {
			if (radicals[i] == radicals[j])
				return i < j;

			return radicals[i] < radicals[j];
		});

		return index[10000];
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=124
// 筛法