
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common_headers.h"
#include "helper.h"

using namespace std;

int F[10][10];
int color[10];
bool appear[10];

#define WHITE	0
#define GRAY	1
#define BLACK	2

class Solution
{
public:
	void peekDepends(int n) {
		auto D = Util::getDigits(n);
		F[D[0]][D[1]] = 1;
		F[D[0]][D[2]] = 1;
		F[D[1]][D[2]] = 1;
		appear[D[0]] = appear[D[1]] = appear[D[2]] = true;
	}

	void DFS(int k) {
		color[k] = GRAY;
		for (int i = 0; i < 10; ++i) {
			if (!F[k][i])
				continue;

			if (color[i] == BLACK)
				continue;

			if (color[i] == GRAY) {
				int xx = 0;
				// find conflict
			}

			DFS(i);
		}

		color[k] = BLACK;
		_topSortResult.push_back(k);
	}

	int solve()
	{
		for (int n : _input) {
			peekDepends(n);
		}

		for (int i = 0; i < 10; ++i) {
			if (appear[i] && color[i] == WHITE)
				DFS(i);
		}
		return 0;
	}

	vector<int> _input = {
		129, 160, 162, 168, 180, 289, 290, 316, 318, 319, 
		362, 368, 380, 389, 620, 629, 680, 689, 690, 710, 
		716, 718, 719, 720, 728, 729, 731, 736, 760, 762, 
		769, 790, 890
	};

	vector<int> _topSortResult;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=79
// simple DFS, top sort the numbers
// it's lucky that no number appear twice, which means the dependency tree has no circle

