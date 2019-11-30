
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	void initU() {
		U.resize(12);
		// F(n) = 1-n+n^2-n^3+n^4-n^5+n^6-n^7+n^8-n^9+n^10
		vector<long long> coef {
			1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1
		};

		for (int x = 0; x < U.size(); ++x) {
			long long base = 1;
			long long result = coef[0];
			// start from coef[1], becaose coef[0] is constant
			for (int c = 1; c < coef.size(); ++c) {
				base *= x;
				result += base * coef[c];
			}

			U[x] = result;
		}
	}

	// sample U(x)
	// void initU() {
	// 	U.resize(6);
	// 	// F(n) = n^3

	// 	for (int x = 1; x < U.size(); ++x) {
	// 		U[x] = (long long)pow(x, 3.0);
	// 	}
	// }

	long long BOP(int n) {
		// 用n-1次项式F拟合U
		// 即F(1) = U(1), F(2) = U(2), ... ,F(n) = U(n)
		// 返回首个无法拟合的F(k)，通常为F(n+1)
		if (n <= 1) {
			// 0次项拟合没有自变量，BOP = U(1)
			return U[1];
		}

		// 构造增广矩阵，n*(n+1)
		vector<vector<long long>> M;
		M.resize(n);
		for (int i = 0; i < n; ++i) {
			M[i].resize(n+1);
		}

		for (int x = 1; x <= n; ++x) {
			auto& row = M[x-1];

			long long base = 1;
			for (int c = 0; c < n; ++c) {
				row[c] = base;
				base *= x;
			}

			row.back() = U[x];
		}

		// 消元
		for (int i = 0; i < M.size()-1; ++i) {
			// 所有行减去第i行，消除第i元
			for (int j = i+1; j < M.size(); ++j) {
				long long lcm = Util::lcm(M[i][i], M[j][i]);
				long long mi = lcm / M[i][i];
				long long mj = lcm / M[j][i];
				for (int k = i; k < M[j].size(); ++k) {
					M[j][k] = M[j][k] * mj - M[i][k] * mi;
				}
			}
		}

		// 反向代入
		vector<long long> coef(n);
		for (int i = M.size()-1; i >= 0; --i) {
			// 将M[i+1:]代入行i
			long long S = M[i].back();
			for (int j = i+1; j < M.size(); ++j) {
				S -= M[i][j] * coef[j];
			}

			if (S % M[i][i] != 0) {
				int k = 0;
			}
			coef[i] = S / M[i][i];
		}

		// 求F(n+1)
		long long result = 0;
		long long base = 1;
		for (auto c : coef) {
			result += base * c;
			base *= (n+1);
		}

		return result;
	}

	// x, y满足y = F(x)
	// 使用拉格朗日插值法构造一个n-1次多项式Q拟合x=>y映射的前n项，并返回Q(k)
	// x不一定从1开始，可以是离散的。也可以将(x,y)理解成点坐标，Q是拟合前n个点的n-1次曲线
	// 需要简单评估pow(xi, len(x))最坏情况下是否会数值溢出，不确定的情况下建议用高精度库
	// 参考资料：https://www.zhihu.com/question/58333118
	long long BOP2(int n) {
		vector<long long> x;
		for (int i = 1; i <= n; ++i)
			x.push_back(i);
	
		return Util::lagrangeInterpolation(x, vector<long long>(U.begin()+1, U.begin()+n+1), n, n+1);
	}

	long long solve() {
		initU();

		long long result = 0;
		for (int i = 1; i <= 10; ++i) {
			result += BOP2(i);
		}

		return result;
	}

	vector<long long> U;
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// 高斯消元
// 先求出U(n)前10项，作为增广矩阵
// 用高斯消元求OP(1,n) ~ OP(10,n)的各系数
// OP(1,n)对应0次项，OP(10,n)对应的是9次项，OP(11,n)等价于Un
// note: 这里没有处理无法推到唯一解的情况

// 拉格朗日插值
// https://www.zhihu.com/question/58333118
