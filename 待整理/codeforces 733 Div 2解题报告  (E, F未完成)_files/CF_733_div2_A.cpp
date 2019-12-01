#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <map>
#include <tuple>

using namespace std;

// Problem A
inline bool isVolwel(char c)
{
   return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

int main(int argc, const char * argv[])
{
   string s;
   cin >> s;
   s += 'A';

   int sp = -1;
   int maxLen = 0;

   for (int i = 0; i < (int)s.size(); ++i) {
       if (isVolwel(s[i])) {
           maxLen = max(maxLen, i-sp);
           sp = i;
       }
   }
   
   cout << maxLen;

   return 0;
}


