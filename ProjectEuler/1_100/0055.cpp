#include "common_headers.h"
#include "helper.h"

using namespace std;

class BigNumber
{
public:
	void AddReverseSelf() {
		int tmp;
		for (int i = 0; i < _len/2; ++i) {
			tmp = _digits[i];
			_digits[i] += _digits[_len-i-1];
			_digits[_len-i-1] += tmp;
		}

		if (_len & 1) {
			_digits[_len/2] <<= 1;
		}

		for (int i = 0; i < _len; ++i) {
			_digits[i+1] += _digits[i] / 10;
			_digits[i] %= 10;
		}

		if (_digits[_len] > 0)
			_digits[++_len] = 0;	// keep leading zero
	}

	bool isPalindormic() const {
		for (int i = 0; i < _len/2; ++i) {
			if (_digits[i] != _digits[_len-i-1])
				return false;
		}

		return true;
	}

public:
	explicit BigNumber(int n) {
		if (n == 0) {
			_len = 1;
			_digits[0] = 0;
			return;
		}

		_len = 0;
		while (n) {
			_digits[_len++] = n % 10;
			n /= 10;
		}

		_digits[_len] = 0;
	}

private:
	int _len;
	int _digits[600];
};

class Solution
{
public:
	bool isLychrelNumber(int n) {
		BigNumber num(n);
		for (int i = 1; i < 50; ++i) {
			num.AddReverseSelf();
			if (num.isPalindormic()) {
				return false;
			}
		}

		return true;
	}

	int solve() {
		int result = 0;
		for (int i = 1; i < 10000; ++i) {
			if (isLychrelNumber(i)) {
				++ result;
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

// brute force