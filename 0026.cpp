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
#include "helper.h"

using namespace std;

class Solution {
public:
	void init() {

	}

	int solve(int N) {
		int best = 0;
		int result = 1;
		for (int i = 2; i < N; ++i) {
			int tmp = Util::fractionCycleLength(i);
			if (tmp > best) {
				best = tmp;
				result = i;
			}
		}

		return result;
	}

public:
	// members

};

int main() {
	Solution s;
	s.init();
	cout << s.solve(1000) << endl;

	return 0;
}
