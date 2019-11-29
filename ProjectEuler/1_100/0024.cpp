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
	string solve(int N) {
		int M[11];
		M[0] = M[1] = 1;
		for (int i = 2; i <= 10; ++i) {
			M[i] = i * M[i-1];
		}

		string S = "0123456789";
		string result;
		-- N;
		while (S.size()) {
			int k = N / M[S.size()-1];
			result.push_back(S[k]);
			N %= M[S.size()-1];
			S.erase(S.begin()+k);
		}

		return result;
	}
};

int main() {
	auto s = new Solution();
	cout << s->solve(1000000) << endl;
	delete s;
	return 0;
}
