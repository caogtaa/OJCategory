#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <map>
#include <tuple>

using namespace std;

// Problem D, 立方体拼接，找出内切球最大的一个？也可以只给一个立方体
// 内切球半径是最小的边长 / 2
// 3种组合都保存下来，留第3边较长的
// 用map过了，用unordred_map竟然反而没过。。。。。
#define COMB(x, y)  ((((long long)x) << 32) + y)

int best = 0;
pair<int, int> bestIndex;
map<long long, tuple<int, int, int, int> > cache;
inline void adjust(int a, int b, int c, int index)
{
   if (a > b)
       swap(a, b);

   long long key = COMB(a, b);
   auto iter = cache.find(key);
   if (iter == cache.end()) {
       cache.insert(make_pair(key, make_tuple(-1LL, c, -1, index)));
   } else {
       auto &v = iter->second;
       // replace the smaller, update best
       if (std::get<0>(v) < std::get<1>(v)) {
           std::get<0>(v) = c;
           std::get<2>(v) = index;
       } else {
           std::get<1>(v) = c;
           std::get<3>(v) = index;
       }
       
       int shortest = std::get<0>(v) + std::get<1>(v);
       shortest = min(shortest, a);
       //shortest = min(shortest, b);
       if (shortest > best) {
           best = shortest;// max(best, shortest);
           bestIndex.first = std::get<2>(v);
           bestIndex.second = std::get<3>(v);
       }
   }
}

int main(int argc, const char * argv[])
{
   int N;
   scanf("%d", &N);
   //cache.reserve(N * 3);
   int a, b, c;
   int mn;
   for (int i = 1; i <= N; ++i) {
       scanf("%d %d %d", &a, &b, &c);
       mn = min(min(a, b), c);
       // sort(edge, edge + 3);
       if (mn > best) {
           best = mn;
           bestIndex.first = -1;
           bestIndex.second = i;
       }
       
       adjust(a, b, c, i);
       if (b != c)
           adjust(a, c, b, i);
       if (a != c)
           adjust(b, c, a, i);
   }
   
   //printf("%lld\n", best);
   if (bestIndex.first == -1)
       printf("1\n%d\n", bestIndex.second);
   else
       printf("2\n%d %d\n", bestIndex.first, bestIndex.second);
       

   return 0;
}
