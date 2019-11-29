#include "common_headers.h"
#include "helper.h"

using namespace std;

vector<vector<string>> input = {
	{"INTRODUCE", "REDUCTION"},
	{"CREATION", "REACTION"},
	{"CENTRE", "RECENT"},
	{"COURSE", "SOURCE"},
	{"CREDIT", "DIRECT"},
	{"DANGER", "GARDEN"},
	{"EXCEPT", "EXPECT"},
	{"FORMER", "REFORM"},
	{"IGNORE", "REGION"},
	{"ARISE", "RAISE"},
	{"BOARD", "BROAD"},
	{"EARTH", "HEART"},
	{"LEAST", "STEAL"},
	{"NIGHT", "THING"},
	{"PHASE", "SHAPE"},
	{"QUIET", "QUITE"},
	{"SHEET", "THESE"},
	{"SHOUT", "SOUTH"},
	{"THROW", "WORTH"},
	{"CARE", "RACE"},
	{"DEAL", "LEAD"},
	{"EARN", "NEAR"},
	{"EAST", "SEAT"},
	{"FILE", "LIFE"},
	{"FORM", "FROM"},
	{"HATE", "HEAT"},
	{"ITEM", "TIME"},
	{"MALE", "MEAL"},
	{"MEAN", "NAME"},
	{"NOTE", "TONE"},
	{"POST", "SPOT", "STOP"},	// 低概率刚好这个位置是答案，先忽略这3个一组
	{"RATE", "TEAR"},
	{"SHUT", "THUS"},
	{"SIGN", "SING"},
	{"SURE", "USER"},
	{"ACT", "CAT"},
	{"DOG", "GOD"},
	{"EAT", "TEA"},
	{"HOW", "WHO"},
	{"ITS", "SIT"},
	{"NOW", "OWN"},
	{"NO", "ON"}
};

vector<long long> SQ[10];
vector<int> rep(26);

class Solution
{
public:
	int digitCount(long long n) {
		return (int)log10(n) + 1;
	}

	vector<int> getDigits(long long n) {
		int d = digitCount(n);
		vector<int> result(d);
		while (d--) {
			result[d] = n % 10;
			n /= 10;
		}
		return result;
    }

	bool make_replacement(const vector<int>& digits, const string& s) {
		fill(rep.begin(), rep.end(), -1);	// char-'A' -> digit
		char mp[10];		// digit -> char
		fill(mp, mp+10, 0);

		for (int i = 0; i < s.size(); ++i) {
			// digit already mapped
			if (mp[digits[i]]) {
				if (mp[digits[i]] != s[i])
					return false;
			}

			// char already mapped
			if (rep[s[i]-'A'] != -1) {
				if (rep[s[i]-'A'] != digits[i])
					return false;
			}
			rep[s[i]-'A'] = digits[i];
			mp[digits[i]] = s[i];
		}

		return true;
	}

	bool check(const vector<int>& rep, const string& s) {
		// leading zero not allowed
		if (rep[s[0]-'A'] == 0)
			return false;

		long long n = 0;
		for (char c : s) {
			n *= 10;
			n += rep[c-'A'];
		}
		return SpecialNumber::isSquareNumber(n);
	}

	bool test(long long sq, const vector<string>& ls) {
		auto digits = Util::getDigits(sq);
		// get replacement of ls[0], check ls[1]
		if (make_replacement(digits, ls[0]) && check(rep, ls[1]))
			return true;
		
		// get replacement of ls[1], check ls[0]
		if (make_replacement(digits, ls[1]) && check(rep, ls[0]))
			return true;

		return false;
	}

	long long solve() {
		for (long long i = 1; digitCount(i*i) <= 9; ++i) {
			long long k = i*i;
			SQ[digitCount(k)].push_back(k);
		}

		for (auto ls : input) {
			int len = ls[0].size();
			for (int i = SQ[len].size()-1; i >= 0; --i) {
				if (test(SQ[len][i], ls)) {
					return SQ[len][i];
				}
			}
		}

		return 0;
	}
};

int main()
{
	Solution* s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=98
// 先筛选输入，2000个单词过滤后只有42个有效单词对
// 寻找所有的平方数
// 所有的单词和其等长的平方数做映射，然后把映射结果应用到其配对的单词上检查是否构成平方数
// 映射的时候注意字母、数字是一一映射
// 映射结果应用到配对单词时注意是否有前缀0

