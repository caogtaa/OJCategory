/*
https://www.hackerrank.com/contests/sears-dots-arrows/challenges/connection-queries

材料：
https://blog.anudeep2011.com/mos-algorithm/
思路是用离线算法处理Query，按照一定规则排序后应用原来的暴力解法

本题中将Query的区域分成sqrt(N)个block，如果一个Query的L属于某个block，那么这个Query就属于这个block
按照Query所在的block对所有query排序，同一个block内的Query按照R递增排序

对于每个block
1.其中的Query.R是升序排列的，右指针每次从左到右最多移动O(N)次，总共有sqrt(N)个block，总时间复杂度O(N*sqrt(N))
2.其中的Query.L是无序的，但是范围限定在这个block内，每个query最多移动sqrt(N)次，一个block里有Q个query就是Q*sqrt(N)，所有block累加就是 O(M*sqrt(N)), 其中M是query的总数

Most important. Let us talk about the right pointer first. For each block, the queries are sorted in increasing order, so clearly the right pointer (currentR) moves in increasing order. During the start of next block the pointer possibly at extreme end will move to least R in next block. That means for a given block, the amount moved by right pointer is O(N). We have O(Sqrt(N)) blocks, so the total is O(N * Sqrt(N)). Great!

Let us see how the left pointer moves. For each block, the left pointer of all the queries fall in the same block, as we move from query to query the left pointer might move but as previous L and current L fall in the same block, the moment is O(Sqrt(N)) (Size of the block). In each block the amount left pointer movies is O(Q * Sqrt(N)) where Q is number of queries falling in that block. Total complexity is O(M * Sqrt(N)) for all blocks.
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// MO algorithm
struct Query {
    int L, R;
    int result;
};

vector<bool> appear;
vector<int> A;
vector<Query> query;

int N, Q;
int result = 0;

void add(int v) {
    if (!appear[v-1] && !appear[v+1])
        ++result;
    else if (appear[v-1] && appear[v+1])
        --result;
    
    appear[v] = true;
}

void remove(int v) {
    if (!appear[v-1] && !appear[v+1])
        --result;
    else if (appear[v-1] && appear[v+1])
        ++result;
    
    appear[v] = false;
}

// FILE *fp = freopen("/Users/taobao/Downloads/input02.txt", "r", stdin);

int main() {
    cin >> N >> Q;
    if (Q == 0)
        return 0;

    A.resize(N+2);      // require 0 and N+1 for convinient, 1-based index
    appear.resize(N+2);
    query.resize(Q);    // query is 0-based

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    
    int minL = N, maxR = 1;
    for (int i = 0; i < Q; ++i) {
        cin >> query[i].L >> query[i].R;
        minL = min(minL, query[i].L);
        maxR = max(maxR, query[i].R);
    }

    int areaLen = (int)sqrt(1.0 * maxR + 1 - minL);
    areaLen = max(areaLen, 1);  // to make sure it's not 0???
    
    vector<Query *> pq(Q);
    for (int i = 0; i < Q; ++i) {
        pq[i] = &query[i];
    }
    
    sort(pq.begin(), pq.end(), [&](const Query *q1, const Query *q2) {
        int area1 = (q1->L - minL) / areaLen;
        int area2 = (q2->L - minL) / areaLen;
        if (area1 != area2)
            return area1 < area2;   // area in increasing order
        
        // R in increasing order for tie
        return q1->R < q2->R;
    });
    
    int currentL = 1;
    int currentR = 0;
    for (int i = 0; i < Q; ++i) {
        Query *q = pq[i];
        // move currentR to R rightward, add elemements
        while (currentR < q->R) {
            ++currentR;
            add(A[currentR]);
        }
        
        // move currentL to L leftward, add elements
        while (currentL > q->L) {
            --currentL;
            add(A[currentL]);
        }
        
        // move currentL to L rightward, remove elements
        while (currentL < q->L) {
            remove(A[currentL]);
            ++currentL;
        }
        
        // move currentR to R leftward, remove elements
        while (currentR > q->R) {
            remove(A[currentR]);
            --currentR;
        }
        
        q->result = result;
    }
    
    for (int i = 0; i < Q; ++i) {
        cout << query[i].result << endl;
    }
    
    return 0;
}
