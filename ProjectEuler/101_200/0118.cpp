
#include <common_headers.h>
#include <helper.h>

using namespace std;

const long long lmt = 1000000;
const long long maxK = 6;
const int maxS = 512-1;

long long F[maxS+1][maxK+1];

class BitCombiner {
public:
	BitCombiner(vector<int>& result) :
		result(result) {}

	void _find(int spos, int curS, int k) {
		if (spos == sbit.size() || k == 0) {
			if (F[lowBit+curS][1] > 0) {
				result.push_back(lowBit+curS);
			}

			return;
		}

		// use current bit
		_find(spos+1, curS+sbit[spos], k-1);

		// ignore current bit
		_find(spos+1, curS, k);
	}

	void find(int s, int rest) {
		// split s into bits
		lowBit = Util::lowBit(s);
		s -= lowBit;

		sbit.resize(0);
		int b = 1;
		while (b <= s) {
			if (s & b)
				sbit.push_back(b);

			b <<= 1;
		}

		_find(0, 0, sbit.size()-rest);
	}

private:
	vector<int>& result;
	vector<int> sbit;
	int lowBit;
};

class Solution {
public:
	bool isPrime(long long n) {
		if (n <= lmt)
			return helper.isPrime(n);

		return PrimeHelper::millerRabinPrimeTest(n);
	}

	void initF_s_1(int s) {
		int originS = s;
		vector<int> digits;
		digits.reserve(9);

		int n = 1;
		int digitSum = 0;
		while (s) {
			if (s & 1) {
				digits.push_back(n);
				digitSum += n;
			}

			s >>= 1;
			++ n;
		}

		if (digits.size() > 1 && digitSum % 3 == 0) {
			F[originS][1] = 0;
			return;
		}

		// permutate digits, digits is already sorted
		long long count = 0;
		long long p = 0;
		do {
			p = 0;
			for (int d : digits) {
				p *= 10;
				p += d;
			}

			count += isPrime(p);
		} while (next_permutation(digits.begin(), digits.end()));
		F[originS][1] = count;
	}

	void initDPEdge() {
		// initialize F[s][1] for all s
		memset(F, -1, sizeof(F));

		for (int s = 1; s <= maxS; ++s) {
			F[s][0] = 0;
		}
		for (int k = 1; k <= maxK; ++k) {
			F[0][k] = 0;
		}
		F[0][0] = 1;

		// pandigit with 9 digits (s = 512-1) is not prime, because all digit sum % 3 = 0
		F[maxS][1] = 0;
		for (int s = 1; s <= maxS; ++s) {
			initF_s_1(s);
		}
	}

	vector<int> possibleGroupsWithLowBit(int s, int rest) {
		// 对lowBit和s-lowBit的剩余数字取所有可能组合
		// 至少要剩余rest个数（减枝）
		// 取出的组合如果F[x][1] == 0，则可以不返回
		vector<int> result;

		BitCombiner combiner(result);
		combiner.find(s, rest);

		return result;
	}

	long long Func(int s, int k) {
		long long& ret = F[s][k];
		if (ret != -1)
			return ret;

		ret = 0;
		auto group = possibleGroupsWithLowBit(s, k-1);
		for (auto g : group) {
			ret += F[g][1] * Func(s-g, k-1);
		}

		return ret;
	}

	long long solve() {
		helper.init(lmt);

		initDPEdge();

		long long result = 0;
		for (int k = 1; k <= maxK; ++k) {
			result += Func(maxS, k);
		}

		return result;
	}

private:
	PrimeHelper helper;
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=118
// 动态规划，状态压缩

// 题意：1~9这9个数字进行组合，组合成的数字要求都是素数，求有多少种组合方法
// 举例：{2,5,47,89,631} 这个组合方法种，所有数字都是素数

// 思路：
// 对1~9这9个数字位压缩成一个9位数字s，当9个数字同时出现时s=512-1
// F[s][k]表示状态为s的集合组成k个素数，有多少种方法
// 递推的时候先取s中的最小位lowbit（即最小的数字），在剩余位中挑选出若干位和lowbit进行组合，设这个组合是s'
// 则F[s][k] = sigma{F[s'][1] + F[s-s'][k-1]} for all s'
// 递推的边界条件:
// 	F[0][k] = 0, (k > 0)
// 	F[s][0] = 0, (s > 0)
// 	F[0][0] = 1
//  F[s][1]通过排列s中的数字+素数测试先计算好，复杂度是8!=40320，还可以接受。9位的不用计算，因为数字和是3的倍数
//    F[s][1]也表示s中的数字任意排列组合，能组成素数的个数

// 优化：
// 1. 计算F[s][1]的时候如果s中的所有数字和为3的倍数则F[s][1] = 0
// 2. 遍历所有s'时，由于s-s'中还需要组成k-1个数字，所以获取s'的所有可能性时根据k-1进行减枝