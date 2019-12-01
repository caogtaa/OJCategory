#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

// DP，状态压缩, implementation
// 题意：一个最大 20x8的面板，每个格子为空或者已经被占，要求使用L型的积木嵌满空的格子，L型积木可以旋转或者翻转，求有多少种不同的嵌入方法
// 思路：题目规格较小，但是状态空间并不小，加上L型积木本身占据2x3的空间，所以DP的时候需要同时考虑3行的变化，每行的状态数是 2^8，三行就是2^24 = 16e6，再算上状态转移的系数，空间和时间都会超
// 通过优化可减小状态空间：考虑每次状态转移时，均将当前的行填满，然后只需要考虑后面两行的变化，状态空间会缩小到 20*2^16 = 1e6。这种状态转换需要预先计算出在当前行状态是s的时候，填满当前行对后面两行的状态影响，即代码中的nxt数组。
// 状态转移的系数比较不确定，根据当前状态的复杂度，后继状态数量相差较大，最多的情况是当前行全空（即state = 0)的情况，有276个。但是根据实际情况，状态空间并不会全部被占用，所以使用记忆化搜索能加快速度。
// 还做了一些预计算进行加速，但可能不是必须的
// 1. hi0: 8位表示中最高位0的bit位，用于快速取行状态中第一个未被占用的位置
// 2. hi1: 最高位1，用于快速取L型积木中第一行的宽度，该数据用于L型积木嵌入面板时，做对齐于空位

#define MOD 1000000007

// nxt[state]表示行状态为state时，放满该行能得到的所有后继状态，(后1行状态 << 8 + 后2行状态)
vector<pair<int, int>> nxt[256];
int G[20];              // 每行8位压缩表示，一行不足8位的以1填充，表示被占
int T, N, M;
const int _FULL = (1 << 8) - 1;
const int _EMPTY = 0;
long long F[20][256][256];
int hi0[256];
int hi1[256];

struct Tile
{
    void init(int h, int w, const string &s) {
        for (int i = 0; i < h; ++i) {
            _state[i] = 0;
            for (int k = 0; k < w; ++k) {
                _state[i] <<= 1;
                _state[i] += s[i*w+k] == '#';
            }
        }
        
        if (s[0] == '#') {
            _offset_x = w - 1;
            _offset_y = h - 1;
        } else {
            _offset_x = -w + 1;
            _offset_y = h - 1;
        }
    }

    int _state[3];
    int _offset_x;
    int _offset_y;
};

Tile tiles[8];

void EnumState(int s, int l0, int l1, int l2)
{
    if (l0 >= _FULL) {
        nxt[s].push_back(make_pair(l1, l2));
        return;
    }
    
    auto zerob = hi0[l0];
    // assert(zerob < 8)
    
    for (int i = 0; i < 8; ++i) {
        auto &t = tiles[i];
        auto toffset = hi1[t._state[0]];
        if (zerob - t._offset_x < 0 || zerob - t._offset_x >= 8)
            // out of range after placing the tile
            continue;
        
        auto offset = zerob - toffset; // adjust current state insert position to tile
        if ((l0 & (t._state[0] << offset)) || (l1 & (t._state[1] << offset)) || (l2 & (t._state[2] << offset)))
            // overlapped
            continue;
        
        EnumState(s, l0 | (t._state[0] << offset), l1 | (t._state[1] << offset), l2 | (t._state[2] << offset));
    }
}

void init()
{
    // init tile data
    tiles[0].init(3, 2,
                  "##"
                  "#."
                  "#.");
    tiles[1].init(3, 2,
                  "##"
                  ".#"
                  ".#");
    tiles[2].init(3, 2,
                  "#."
                  "#."
                  "##");
    tiles[3].init(3, 2,
                  ".#"
                  ".#"
                  "##");
    tiles[4].init(2, 3,
                  "###"
                  "#..");
    tiles[5].init(2, 3,
                  "###"
                  "..#");
    tiles[6].init(2, 3,
                  "#.."
                  "###");
    tiles[7].init(2, 3,
                  "..#"
                  "###");
    
    // init highest 1 bit
    hi1[0] = 0; // should not be used
    hi1[1] = 0;
    for (int s = 2; s < 1 << 8; ++s) {
        hi1[s] = (int)(log(s) / log(2.0));
    }

    // highest 0 bit in 8 bit presentation
    for (int s = 0; s < 1 << 8; ++s) {
        // todo: DP to faster
        for (int b = 7; b >= 0; --b) {
            if ((s & (1 << b)) == 0) {
                hi0[s] = b;
                break;
            }
        }
    }
    hi0[255] = 8;
    
    // EnumState(31, 31, 0, 0);
    
    // bruteforce to init nxt
    for (int s = 0; s < 1 << 8; ++s) {
        EnumState(s, s, 0, 0);
    }
    
}

long long Func(int row, int s0, int s1)
{
    if (row >= N)
        return 1LL;
    else if (row == N-1)
        return (s0 == _FULL && s1 == _EMPTY);
    
    if (s0 == _FULL)
        return Func(row + 1, s1, row+2<N ? G[row+2]:0);
    
    long long &ret = F[row][s0][s1];
    if (ret != -1)
        return ret;
    
    ret = 0;
    int l1, l2;
    for (auto &p : nxt[s0]) {
        l1 = p.first;
        l2 = p.second;
        if (l1 & s1)
            // next line overlap
            continue;
        if (row + 2 < N) {
            // second next line exist
            if (G[row+2] & l2)
                // but overlap
                continue;
            
            ret += Func(row + 1, l1 | s1, G[row+2] | l2);
        } else {
            if (l2)
                // Y-axis out of range
                continue;
            
            // second next line not exist
            ret += Func(row + 1, l1 | s1, 0);
        }
    }

    ret %= MOD;
    return ret;
}

int main()
{
    init();
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        
        // read grids, store in G
        char line[9];
        int space = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%s", line);
            int state = 0;
            for (int k = 0; k < M; ++k) {
                state <<= 1;
                if (line[k] == '#')
                    ++ state;
                else
                    ++ space;
            }
            
            if (M < 8) {
                // fill with 1
                state <<= (8-M);
                state += (1 << (8-M)) - 1;
            }

            G[i] = state;
        }
        
        if (N < 2 || M < 2 || space % 4 != 0) {
            printf("0\n");
            continue;
        }
        
        memset(F, -1, sizeof(F));
        printf("%lld\n", Func(0, G[0], G[1]));
    }
    
    return 0;
}
