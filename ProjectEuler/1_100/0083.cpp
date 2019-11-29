
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

FILE* pf = freopen("0083_input.txt", "r", stdin);
int mat[80][80];
int dist[80][80];
int dir[4][2] = {
	{0, -1},
	{0, 1},
	{1, 0},
	{-1, 0}
};

class Solution
{
public:
	void inputRow(int r) {
		string line;
		cin >> line;
		line += ',';

		int sp = 0, ep = 0;
		string token;
		int c = 0;
		while ((ep = line.find(',', sp+1)) != string::npos) {
			token = line.substr(sp, ep-sp);
			dist[r][c] = INT32_MAX;
			mat[r][c++] = stoi(token);
			sp = ep+1;
		}
	}

	int solve()
	{
		for (int i = 0; i < 80; ++i) {
			inputRow(i);
		}

		struct triple {
			int r;
			int c;
			int v;

			triple(int r=0, int c=0, int v=0) {
				this->r = r;
				this->c = c;
				this->v = v;
			}
		};

		// 自定义cmp方法，pop过程中较大的越早出现（和排序cmp直观理解相反）
		// 即：返回true时左侧早出现
		auto cmp = [](const triple& left, const triple& right) {
			return left.v > right.v;
		};

		std::priority_queue<triple, std::vector<triple>, decltype(cmp)> qu(cmp);
		dist[0][0] = mat[0][0];
		qu.emplace(triple(0, 0, mat[0][0]));

		while (true) {
			auto node = qu.top();
			qu.pop();
			if (node.r == 79 && node.c == 79) {
				return node.v;
			}

			if (node.v > dist[node.r][node.c]) {
				// ignore this node, because it's outdated
				continue;
			}

			triple nxt;
			int d;
			for (int i = 0; i < 4; ++i) {
				nxt.r = node.r + dir[i][0];
				nxt.c = node.c + dir[i][1];
				if (nxt.r >= 0 && nxt.r < 80 && nxt.c >= 0 && nxt.c < 80) {
					nxt.v = node.v + mat[nxt.r][nxt.c];
					if (nxt.v >= dist[nxt.r][nxt.c]) {
						// ignore it, a better path from (0,0) to (r,c) already exist
						continue;
					}

					// update better path
					dist[nxt.r][nxt.c] = nxt.v;
					qu.emplace(nxt);
				}
			}
		}

		return 0;
	}

	vector<int> _dist;
};

int main()
{
	Solution s;
	// s.solve();
	cout << s.solve() << endl;

	return 0;
}

// https://projecteuler.net/problem=83
// shortest path, use priority_queue + BFS to implement

