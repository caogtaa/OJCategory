
#include <common_headers.h>
#include <helper.h>

using namespace std;

class Solution {
public:
	// long long solve() {
	// 	long long Fn_2 = 1;
	// 	long long Fn_1 = 1;
	// 	// long long head_mod = (long long)1e19;

	// 	long long Fn_2_tail = 1;
	// 	long long Fn_1_tail = 1;
	// 	long long tail_mod = (long long)1e9;

	// 	long long k = 3;
	// 	long long Fn;
	// 	long long Fn_tail;
	// 	long long Fn_head;

	// 	int digits;
	// 	long long base;
	// 	int tailing_digits = 0;
	// 	do {
	// 		Fn = Fn_2 + Fn_1;
	// 		Fn_tail = (Fn_2_tail + Fn_1_tail) % tail_mod;

	// 		digits = Util::digitCount(Fn);
	// 		if (digits > 9) {
	// 			Fn_head = Fn / (long long)pow(10, digits - 9);
	// 		} else {
	// 			Fn_head = Fn;
	// 		}
			
	// 		if (digits >= 9 && SpecialNumber::isPandigital(Fn_tail) && 
	// 			SpecialNumber::isPandigital(Fn_head)) {
	// 			return k;
	// 		}

	// 		++ k;

	// 		if (digits > 18) {
	// 			tailing_digits += digits - 18;
	// 			base = (long long)pow(10, digits - 18);
	// 			Fn /= base;
	// 			Fn_1 /= base;
	// 		}

	// 		Fn_2_tail = Fn_1_tail;
	// 		Fn_1_tail = Fn_tail;

	// 		Fn_2 = Fn_1;
	// 		Fn_1 = Fn;
	// 	} while (true);

	long long solve() {
		long long Fn_2 = 1;
		long long Fn_1 = 1;
		long long mod = (long long)1e9;

		long long n = 3;
		long long Fn;
		do {
			Fn = (Fn_2 + Fn_1) % mod;
			if (Util::digitCount(Fn) >= 9 && SpecialNumber::isPandigital(Fn) &&
				SpecialNumber::isPandigital(SpecialNumber::topKDigitsOfFibonacciN(9, n))) {
				return n;
			}

			++ n;
			Fn_2 = Fn_1;
			Fn_1 = Fn;
		} while (true);

		return -1;	// will not happen
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=104
// keep 1st 18 digits and last 9 digits when iterating
