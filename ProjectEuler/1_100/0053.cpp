#include "common_headers.h"
#include "helper.h"

using namespace std;

class Solution
{
public:
	long long c[101][101];
	long long C(int n, int m) {
		if (m == 0)
			return 1;
		if (m == 1)
			return n;
		if (m > n/2)
			return C(n, n-m);

		long long& ret = c[n][m];
		if (ret != -1)
			return ret;

		// C[n][m] = C[n-1][m-1] + C[n-1][m]
		ret = C(n-1, m-1) + C(n-1, m);
		if (ret > 1000000) {
			// prevent from overflow
			ret = 1000001;
		}

		return ret;
	}

	int solve() {
		memset(c, -1, sizeof(c));

		int result = 0;
		for (int n = 1; n <= 100; ++n) {
			for (int m = 0; m <= n; ++m) {
				int x = C(n, m);
				if (C(n, m) > 1000000) {
					++ result;
				}
			}
		}
		
		return result;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}
