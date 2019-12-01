//
//  by caogtaa
//

#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>
#include <string.h>
#include <unordered_map>
#include <utility>

using namespace std;
int N;
int appear[26];
char g_S[2010];

int checkMisOrderIndex(const vector<int> &SA)
{
    for (size_t i = 0; i < SA.size(); ++i) {
        if (SA[i] != i) {
            return (int)i;
        }
    }
    
    return N;
}

unordered_map<string, int> g_cache;
int g_best;

int F(const string &S_origin, char target, int already)
{
    if (S_origin.size() == 0 || target == 'z') {
        g_best = min(g_best, already);
        return 0;
    }
    
    if (already >= g_best) {
        return g_best;
    }
    
    bool isOrdered = true;
    for (size_t i = 1; i < S_origin.size(); ++i) {
        if (S_origin[i] < S_origin[i-1]) {
            isOrdered = false;
            break;
        }
    }
    
    if (isOrdered) {
        g_best = min(g_best, already);
        return 0;
    }
    
    auto iter = g_cache.find(S_origin);
    if (iter != g_cache.end()) {
        return iter->second;
    }
    
    char nextGuess = 'z';
    vector<int> nextSPGuess;
    string S = S_origin;
    if (S[0] == target)
        S = S.substr(1);

    int len = (int)S.size();
    char nxtC;
    int targetCount = 0;
    for (size_t i = 0; i < len; ++i) {
        if (S[i] != target)
            continue;
        
        ++ targetCount;
        nxtC = S[(i+1)%len];
        if (nxtC < nextGuess) {
            nextSPGuess.resize(0);
            nextSPGuess.push_back((i+1)%len);
            nextGuess = nxtC;
        } else if (nxtC == nextGuess) {
            nextSPGuess.push_back((i+1)%len);
        }
    }
    
    if (already + targetCount >= g_best) {
        return g_best;
    }
    
    if (nextSPGuess.size() == 0) {
        // target not exist, try next char
        return F(S, target+1, already);
    }
    
    int localBest = N;
    for (size_t i = 0; i < nextSPGuess.size(); ++i) {
        // todo: optimize
        // todo: if nextSPGuess is 0, do not duplicate it
        string dup_S = S;
        string sub = dup_S.substr(nextSPGuess[i]);
        dup_S.insert(0, sub);
        dup_S.resize(S.size());
        dup_S.erase(remove_if(dup_S.begin(), dup_S.end(), [target](char c) {return c == target;}), dup_S.end());
        auto last = std::unique(dup_S.begin(), dup_S.end());
        dup_S.erase(last, dup_S.end());
        localBest = min(localBest, targetCount + F(dup_S, target+1, already+targetCount));
    }
    
    g_cache.insert(make_pair(S_origin, localBest));
    return localBest;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", g_S);
        string S(g_S);
        N = (int)S.size();
        g_best = N;

        auto last = std::unique(S.begin(), S.end());
        S.erase(last, S.end());
        
        printf("%d\n", F(S, 'a', 0));
    }
    return 0;
}