#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <map>
#include <tuple>

using namespace std;

// Problem B
int main(int argc, const char * argv[])
{
   int N;
   cin >> N;
   vector<int> L(N);
   vector<int> R(N);
   
   int totalL = 0;
   int totalR = 0;
   for (int i = 0; i < N; ++i) {
       cin >> L[i] >> R[i];
       totalL += L[i];
       totalR += R[i];
   }
   
   int maxBeauty = abs(totalL - totalR);
   int result = 0;
   int tempTotalL = 0;
   int tempTotalR = 0;
   int tempBeauty;
   for (int i = 0; i < N; ++i) {
       tempTotalL = totalL - L[i] + R[i];
       tempTotalR = totalR - R[i] + L[i];
       tempBeauty = abs(tempTotalL - tempTotalR);
       if (tempBeauty > maxBeauty) {
           maxBeauty = tempBeauty;
           result = i + 1;
       }
   }
   
   cout << result;
   
   return 0;
}


