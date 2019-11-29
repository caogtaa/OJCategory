#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"

using namespace std;

class Solution
{
public:
	long long solve() {
		long long hexagonal;
		for (long long i=144; ; ++i) {
			hexagonal = i*(2*i-1);
			if (SpecialNumber::isTriangleNumber(hexagonal) && 
				SpecialNumber::isPentagonalNumber(hexagonal)) {
				return hexagonal;
			}
		}

		return -1;
	}
};

int main()
{
	Solution s;
	cout << s.solve() << endl;
	
	return 0;
}

// enum each hexagonal and check if it's also triangle number and pentagonal number