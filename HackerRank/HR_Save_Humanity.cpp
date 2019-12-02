//
//  main.cpp
//  testZAlgo
//
//  Created by tangtai on 10/19/16.
//

// Z Algorithm
// 因为允许出现一个字符的不一致，可以将匹配看成左右两段，正序匹配和反序匹配的长度累加 ＝ |P|-1就是匹配位置
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void makeZ(const string &S, int Z[])
{
    int len = (int)S.size();
    int L, R, K;
    
    // [L,R] make a window which matches with prefix of s
    L = R = 0;
    Z[0] = len;
    
    for (int i = 1; i < len; ++i) {
        if (i >= R) {
            // out of range, remake range [L, R)
            L = R = i;
            
            while (R < len && S[R-L] == S[R])
                ++R;

            Z[i] = R - L;
            // R--;
        } else {
            // i < R
            K = i - L;
            
            if (Z[K] < R - i)
                // have no chance to make range longer, get the remain length after k
                Z[i] = Z[K];
            else {
                // start from R and extend the range, now Z[L] == R - L ?
                // we start from R because we already know S[0...) == S[i...) for and Z[i] is at least R-i
                L = i;
                while (R < len && S[R-L] == S[R])
                    ++R;
                
                Z[i] = R - L;
                // R--;
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    int T;
    cin >> T;
    while (T-- > 0) {
        string S, P;
        cin >> S >> P;

        string combine = P;
        combine += "$";
        combine += S;
        
        string revS = S;
        reverse(revS.begin(), revS.end());
        string revP = P;
        reverse(revP.begin(), revP.end());
        
        string revCombine = revP;
        revCombine += "$";
        revCombine += revS;
        
        int *Z = new int[combine.size()];
        int *revZ = new int[revCombine.size()];
        
        makeZ(combine, Z);
        makeZ(revCombine, revZ);
        
        int sp = (int)P.size() + 1;
        vector<int> result;
        for (int i = 0; i <= (int)(S.size() - P.size()); ++i) {
            if (Z[sp+i] == P.size() || Z[sp+i] + revZ[sp+ S.size()-(i+P.size())] >= P.size()-1) {
                result.push_back(i);
            }
        }
        
        if (result.size() == 0) {
            cout << "No Match!" << endl;
        } else {
            for (int i = 0; i < (int)result.size(); ++i)
                cout << result[i] << " ";
            cout << endl;
        }
        
        delete[] Z;
        delete[] revZ;
    }
    
    return 0;
}

