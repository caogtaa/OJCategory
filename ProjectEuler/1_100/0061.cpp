#include "common_headers.h"
#include "helper.h"

using namespace std;

class Solution
{
public:
	typedef function<int(int)> ValueFunc;

	void collect(int p, const ValueFunc& func) {
		int v;
		for (int i = 1; ; ++i) {
			v = func(i);
			if (v >= 10000)
				return;

			if (v >= 1000 && v % 100 >= 10)		// last 2-digits have no heading zeros
				table.insert(make_pair(v / 100, make_pair(p, v)));
		}
	}

	bool search(int rest, int pre_num) {
		int prefix = pre_num % 100;
		auto range = table.equal_range(prefix);
		for (auto iter = range.first; iter != range.second; ++iter) {
			auto p = iter->second;
			if (visited[p.first])
				continue;

			visited[p.first] = true;
			result.push_back(p);
			if (rest == 1 && p.second % 100 == origin_prefix)
				return true;
			else if (search(rest-1, p.second))
				return true;

			result.pop_back();
			visited[p.first] = false;
		}

		return false;
	}

	int solve() {
		collect(3, [](int n) { return n * (n+1) / 2; });
		collect(4, [](int n) { return n * n; });
		collect(5, [](int n) { return n * (3*n-1) / 2; });
		collect(6, [](int n) { return n * (2*n-1); });
		collect(7, [](int n) { return n * (5*n-3) / 2; });
		collect(8, [](int n) { return n * (3*n-2); });

		memset(visited, 0, sizeof(visited));

		// choose one number as start number
		for (auto iter : table) {
			origin_prefix = iter.first;
			visited[iter.second.first] = true;
			result.push_back(iter.second);
			if (search(5, iter.second.second))
				break;

			result.pop_back();
			visited[iter.second.first] = false;
		}

		int sum = accumulate(result.begin(), result.end(), 0, [](int sum, const auto& p) {
			return sum + p.second;
		});

		return sum;
	}

private:
	// 2-digits prefix -> pair<polygonal-type, number>
	unordered_multimap<int, pair<int, int>> table;
	bool visited[10];
	int origin_prefix;
	vector<pair<int, int>> result;	// pair<polygonal-type, number>
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

// cache all polygonal numbers (total number is 302, ignore numbers that 3rd digit is 0)
// bruteforce search for the answer