#include "common_headers.h"
#include "helper.h"

using namespace std;

class Solution
{
public:
	long long solve() {
		long long x = 1;
		long long y = 1;

		// solution with x > 0 && y > 0
		long long tx, ty;
		while (y <= 1000000000000) {
			tx = x;
			ty = y;

			x = tx * 3 + ty * 2 - 2;
			y = tx * 4 + ty * 3 - 3;
		}

		long long result = x;

		// solution with x < 0
		// x = y = 0;
		// while (y <= 1000000000000) {
		// 	tx = x;
		// 	ty = y;

		// 	x = tx * 3 - ty * 2;
		// 	y = tx * -4 + ty * 3 + 1;
		// }

		// result = min(result, y);
		return result;
	}
};

int main()
{
	Solution* s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=100
// 二元二次丢番图等式求解
// https://www.alpertron.com.ar/QUAD.HTM
// x/y * (x-1)/(y-1) = 1/2 等价于求解以下丢番图等式，取y > 10^12时的x解即可
// 2x^2 - y^2 - 2x + y = 0

// 论坛中的解法是将其转换成Pell Equation
/*
S -- number of blue disks
T -- total number of disks
(S/T) * (S-1)/(T-1) =1/2
2S(S-1)-T(T-1)=0
2(S^2-S+1/4-1/4)-(T^2-T+1/4-1/4)=0
2(S-1/2)^2-(T-1/2)^2-1/4=0
substitute u/2=s-1/2, v/2=t-1/2
2u^2/4-v^2/4-1/4=0
2u^2-v^2-1=0

即 v^2-2u^2=-1
*/
// Pell Equation的解法可以用连分数求解法
// https://www.yuque.com/caomou/mgxqtg/melatw#d2SMO