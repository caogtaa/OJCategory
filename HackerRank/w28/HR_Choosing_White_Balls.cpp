//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>
#include <unordered_map>
#include <stack>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define FAST_HASH_MAX   4000000
typedef unsigned int state_type;

char S[40];
int N, K;
unordered_map<state_type, double> cache;
double fast_cache[FAST_HASH_MAX];
bool have_cache[FAST_HASH_MAX];

static const unsigned char ReverseTable[] =
{
    // 16*16 = 256
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
    0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
    0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
    0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
    0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
    0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
    0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
    0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
    0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
    0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
    0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
    0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
    0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
    0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

state_type bit_reverse(state_type x, int len)
{
    state_type mask = 1U << len;
    // x -= 1U << len;
    x -= mask;
    x = (state_type)(ReverseTable[x & 0xff] << 24) |
            (ReverseTable[(x >> 8) & 0xff] << 16) |
            (ReverseTable[(x >> 16) & 0xff] << 8) |
            (ReverseTable[(x >> 24) & 0xff]);
    
    x >>= (32 - len);
    // x &= ((1U << len) - 1);
    x &= mask - 1;
    // x += 1U << len;
    x += mask;
    return (state_type)x;

}

//state_type bit_reverse(long long x, int len)
//{
//    x -= 1LL << len;
//    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
//    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
//    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
//    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
//    x = (x >> 16) | (x << 16);
//    
//    x >>= (32 - len);
//    x &= ((1LL << len) - 1);
//    x += 1LL << len;
//    return (state_type)x;
//}

inline state_type remove_nxt(state_type state, int idx)
{
    state_type mask = 1U << idx;
    return ((state & ~(mask + mask-1)) >> 1) + ((mask - 1) & state);
}

inline bool is_white(state_type state, int idx)
{
    return (state & (1U << idx)) == 0;
}

double Func(state_type state, int len, int rest, int white)
{
    if (white == 0)
        // whatever you choose you get 0 white ball
        return 0.0;
    
    if (white == len)
        // you surely get (rest) white ball
        return rest;

//    if (rest == 1) {
//        if (len & 1 && is_white(state, len >> 1)) {
//            // middle is white
//            return (white * 2.0 - 1.0) / len;
//        } else {
//            return white * 2.0 / len;
//        }
//    }
    if (rest == 0 || len == 0)
        return 0.0;

    // ?????
    state_type mirror = bit_reverse(state, len);
    int halfLen = len >> 1;
    if (state == mirror) {
        // special flow
        if (state < FAST_HASH_MAX) {
            if (have_cache[state])
                return fast_cache[state];
        } else {
            auto iter = cache.find(state);
            if (iter != cache.end())
                return iter->second;
        }
        
        double result = 0.0;
        bool w;
        double t;
        for (int i = 0; i < halfLen; ++i) {
            w = is_white(state, i);
            if (w) {
                t = Func(remove_nxt(state, i), len-1, rest-1, white-1) + 1.0;
            } else {
                t = Func(remove_nxt(state, i), len-1, rest-1, white);
            }
            
            result += t;
        }
        
        result *= 2;
        
        if (len & 1) {
            int i = halfLen;
            w = is_white(state, i);
            if (w) {
                t = Func(remove_nxt(state, i), len-1, rest-1, white-1) + 1.0;
            } else {
                t = Func(remove_nxt(state, i), len-1, rest-1, white);
            }
            
            result += t;
        }
        
        result /= len;
        if (state < FAST_HASH_MAX) {
            have_cache[state] = true;
            fast_cache[state] = result;
        } else {
            cache.insert(make_pair(state, result));
        }

        return result;
    }
    
    state = min(mirror, state);
    
    if (state < FAST_HASH_MAX) {
        if (have_cache[state])
            return fast_cache[state];
    } else {
        auto iter = cache.find(state);
        if (iter != cache.end())
            return iter->second;
    }
    
    double result = 0.0;
    double t1, t2;
    bool w1, w2;
    for (int i = 0; i < halfLen; ++i) {
        w1 = is_white(state, i);
        w2 = is_white(state, len-i-1);
        //if (w1 == w2) {
            if (w1) {
                t1 = Func(remove_nxt(state, i), len-1, rest-1, white-1) + 1.0;
            } else {
                t1 = Func(remove_nxt(state, i), len-1, rest-1, white);
            }
            
            if (w2) {
                t2 = Func(remove_nxt(state, len-i-1), len-1, rest-1, white-1) + 1.0;
            } else {
                t2 = Func(remove_nxt(state, len-i-1), len-1, rest-1, white);
            }
            
            result += max(t1, t2);
//        } else {
        // greedy is not good
//            // maybe greedy is approved
//            if (w1) {
//                result += Func(remove_nxt(state, i), len-1, rest-1, white-1) + 1.0;
//            } else {
//                // w2 == true
//                result += Func(remove_nxt(state, len-i-1), len-1, rest-1, white-1) + 1.0;
//            }
//        }
    }
    
    result *= 2;
    if (len & 1) {
        int i = halfLen;
        bool w = is_white(state, i);
        double t;
        if (w) {
            t = Func(remove_nxt(state, i), len-1, rest-1, white-1) + 1.0;
        } else {
            t = Func(remove_nxt(state, i), len-1, rest-1, white);
        }
        
        result += t;

    }
    
    result /= len;
    
    if (state < FAST_HASH_MAX) {
        have_cache[state] = true;
        fast_cache[state] = result;
    } else {
        cache.insert(make_pair(state, result));
    }

    return result;
}

int main()
{
    scanf("%d %d", &N, &K);
    scanf("%s", S);
    cache.reserve(2000000);
    auto start = system_clock::now();
    int white_rest = 0;
    state_type state = 1U;
    for (int i = 0; i < N; ++i) {
        state <<= 1;
        state += (S[i] == 'B');
        white_rest += (S[i] == 'W');
    }
    
    if (N == K) {
        printf("%.10lf\n", white_rest * 1.0);
    } else {
        printf("%.10lf\n", Func(state, N, K, white_rest));
    }

    // with mirror 23900 vs. without mirror 23865
    // reserve and check synmtac 23438
    // fix bit error, 15446
    // use unordered_map, 7500
    // half search range of each level 4719
    // change long long to uint32_t 4565 (affect much more to online compiler)
    // use unsigned int instead of uint32_t, because platform may have 64bit arch
    // remove greedy.....  9000+
    // use custom hash, better again 4840
    // use fast bit reverse 4580
    // hash table reserve 4133
    auto end = system_clock::now();
    auto dur = duration_cast<milliseconds>(end - start);
    cout << endl << dur.count() << endl;

    return 0;
}
