#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Solution {
public:
	bool isPalindromic(int N) {
		auto s = to_string(N);
		for (int i = 0; i < s.size() / 2; ++i) {
			if (s[i] != s[s.size()-1-i])
				return false;
		}

		return true;
	}

    long long Func(int x, int y) {
		if (x >= input.size())
			return 0;

		if (y >= input[x].size())
			return 0;

        long long& ret = F[x][y];
        if (ret != -1)
            return ret;
        
        ret = input[x][y] + max(Func(x+1, y), Func(x+1, y+1));
        return ret;
    }

	long long solve() {
		memset(F, -1, sizeof(F));
		return Func(0, 0);
	}

	void init() {
	}

public:
	vector<vector<int>> input;
	long long F[100][100];
	int N;
};

int main() {
	auto s = new Solution();
	s->init();

	// s->input = {
	// 	{3},
	// 	{7,4},
	// 	{2,4,6},
	// 	{8,5,9,3}
	// };

	s->input = {
		{75},
		{95,64},
		{17,47,82},
		{18,35,87,10},
		{20,4,82,47,65},
		{19,1,23,75,3,34},
		{88,2,77,73,7,63,67},
		{99,65,4,28,6,16,70,92},
		{41,41,26,56,83,40,80,70,33},
		{41,48,72,33,47,32,37,16,94,29},
		{53,71,44,65,25,43,91,52,97,51,14},
		{70,11,33,28,77,73,17,78,39,68,17,57},
		{91,71,52,38,17,14,91,43,58,50,27,29,48},
		{63,66,4,68,89,53,67,30,73,16,69,87,40,31},
		{4,62,98,27,23,9,70,98,73,93,38,53,60,4,23},
	};
	cout << s->solve() << endl;
	// = 1074
	// simple DP

	return 0;
}
