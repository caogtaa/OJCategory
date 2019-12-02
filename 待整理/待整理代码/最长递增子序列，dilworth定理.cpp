// 584016 2008-04-22 18:50:40 Accepted 1051 15MS 116K 1249 B G++ WAC 
// dilworth定理，最长递增子序列，nlogn

#include <iostream>
#include <algorithm>

using namespace std;

struct Stick {
    int m_len;
    int m_wit;
};

bool MyRule(Stick s1, Stick s2) {
    if( s1.m_len == s2.m_len ) {
        return s1.m_wit > s2.m_wit;
    }
    return s1.m_len > s2.m_len;
}

Stick stick[5000];
int n;

int Solve() {
    // 求wit的最长递增子序列( > )
    int slen = 0;
    static int stk[5000];

    int value;
    stk[slen++] = stick[0].m_wit;

    int lft, rit, mid;

    for(int i=1; i<n; i++) {
        value = stick[i].m_wit;
        if( value > stk[slen-1] ) {
            stk[slen++] = value;
        }
        else {
            // 找最小的k，使stick[k]>=value，每次这里的符号要不要包含‘=’都应该特别注意
            lft = 0;
            rit = slen;
            while( lft <= rit ) {
                mid = (lft+rit)>>1;
                if( stk[mid] < value ) {
                    lft = mid+1;
                }
                else {
                    rit = mid-1;
                }
            }
            stk[lft] = value;
        }
    }

    return slen;
}

int main() {
    int T;
    scanf("%d", &T);
    while( T-- ) {
        scanf("%d", &n);
        for(int i=0; i<n; i++) {
            scanf("%d %d", &stick[i].m_len, &stick[i].m_wit);
        }
        sort(stick, stick+n, MyRule);
        printf("%d\n", Solve());
    }

    return 1;
}
