#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>
using namespace std;

long long S[10];
int SN;
long long N;

map<long long, bool> F;

bool Func(long long x)
{
    if (F.count(x) > 0)
        return F[x];
    
    bool result = false; // ??
    for (int i = 0; i < SN; ++i) {
        if (x % S[i] > 0)
            continue;
        
        bool tmp = Func(x / S[i]);
        if (tmp == false || S[i] % 2 == 0) {
            result = true;
            break;
        }
    }
    
    F[x] = result;
    return result;
}

int main()
{
    cin >> N >> SN;
    for (int i = 0; i < SN; ++i) {
        cin >> S[i];
    }
    
    if (Func(N)) {
        cout << "First" << endl;
    } else {
        cout << "Second" << endl;
    }
    
    return 0;
}

