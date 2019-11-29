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
	long long F[100][100];
	int N;

public:
    long long Func(int m, int n) {
        if (m <= 0 || n <= 0) {
            return 1;
        }
        
        long long& ret = F[m][n];
        if (ret != -1)
            return ret;
        
        ret = Func(m-1, n) + Func(m, n-1);
        return ret;
    }
    
	long long uniquePaths(int m, int n) {
		memset(F, -1, sizeof(F));
		
		return Func(m-1, n-1);
	}

	long long solve() {
		return uniquePaths(21, 21);
	}
};

int main() {
	auto s = new Solution();
	s->N = 10;
	cout << s->solve() << endl;
	// = 137846528820
	// simple DP

	return 0;
}
