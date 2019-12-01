#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <map>
#include <tuple>

using namespace std;

// Problem C, 吃怪物，步骤还原
long long A[500];
long long B[500];
int AN, BN;
long long sum[500];
vector<pair<int, int>> area;    // []

bool checkValidity()
{
    long long base = 0;
    long long *sp = sum;
    long long *pos;
    for (int i = 0; i < BN; ++i) {
        pos = lower_bound(sp, sum+AN, base + B[i]);
        if (pos >= sum+AN)
            return false;
        
        // for B last, must search to sum last
        if (i == BN-1 && pos != sum+AN-1)
            return false;
        
        if (*pos != base + B[i])
            return false;
        
        area.push_back(make_pair(sp-sum, pos-sum));
        base = *pos;
        sp = pos + 1;
    }
    
    return true;
}

bool checkValidity2()
{
    for (const auto &p : area) {
        if (p.first == p.second)
            continue;

        bool same = true;
        for (int i = p.first+1; i <= p.second; ++i) {
            if (A[i] != A[i-1]) {
                same = false;
                break;
            }
        }
        
        if (same)
            return false;
    }
    
    return true;
}

int main(int argc, const char * argv[])
{
    cin >> AN;
    for (int i = 0; i < AN; ++i) {
        cin >> A[i];
    }
    
    sum[0] = A[0];
    for (int i = 1; i < AN; ++i) {
        sum[i] = sum[i-1] + A[i];
    }
    
    cin >> BN;
    for (int i = 0; i < BN; ++i) {
        cin >> B[i];
    }
    
    if (!checkValidity()) {
        cout << "NO" << endl;
        return 0;
    }
    
    if (!checkValidity2()) {
        cout << "NO" << endl;
        return 0;
    }
    
    cout << "YES" << endl;
    int eaten = 0;
    for (const auto &p : area) {
        if (p.first == p.second)
            continue;

        // find max
        int maxIndex = p.first;
        for (int i = p.first + 1; i <= p.second; ++i) {
            if (A[i] > A[maxIndex] || (A[i] == A[maxIndex] && (A[i] > A[i-1] || (i < p.second && A[i] > A[i+1])))) {
                maxIndex = i;
            }
        }
        
        int lft = maxIndex - p.first;
        int rit = p.second - maxIndex;
        if (maxIndex > p.first && A[maxIndex] > A[maxIndex-1]) {
            ++maxIndex;
            maxIndex -= eaten;
            while (lft--) {
                cout << maxIndex << " L" << endl;
                ++eaten;
                --maxIndex;
            }
            while (rit--) {
                cout << maxIndex << " R" << endl;
                ++eaten;
            }
        } else {
            ++maxIndex;
            maxIndex -= eaten;
            while (rit--) {
                cout << maxIndex << " R" << endl;
                ++eaten;
            }
            while (lft--) {
                cout << maxIndex << " L" << endl;
                --maxIndex;
                ++eaten;
            }
        }
    }

    return 0;
}

