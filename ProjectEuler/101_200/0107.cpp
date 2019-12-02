
#include <common_headers.h>
#include <helper.h>
#include <sstream>
#include <iostream>
#include "union_find_set.h"

using namespace std;

FILE* pf = freopen("./0107_input.txt", "r", stdin);
vector<tuple<int, int, int>> edges;

class Solution {
public:
	long long solve() {
		int len;
		string line;
		int N = 40;
		int total = 0;
		for (int i = 0; i < N; ++i) {
			cin >> line;
			// std::getline(std::cin, line);
			replace(line.begin(), line.end(), '-', '0');
			replace(line.begin(), line.end(), ',', ' ');
			istringstream iss(line);

			for (int k = 0; k < N; ++k) {
				iss >> len;
				if (k <= i)
					continue;

				if (len > 0) {
					edges.emplace_back(i, k, len);
					total += len;
				}
			}
		}

		sort(edges.begin(), edges.end(), [](auto& v1, auto& v2) {
			return get<2>(v1) < get<2>(v2);
		});

		UnionFindSet ufs(40);
		int count = 0;
		int sum = 0;
		int s1, s2;
		for (auto& e : edges) {
			if (ufs.find(get<0>(e)) != ufs.find(get<1>(e))) {
				ufs.union2(get<0>(e), get<1>(e));
				sum += get<2>(e);
				if (++count == N-1) {
					break;
				}
			}
		}

		return total - sum;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=107
// 最小生成树，kruskal+union find set
