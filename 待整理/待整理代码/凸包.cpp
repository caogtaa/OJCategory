// 2701636 caogtaa 3355 Accepted 792K 140MS C++ 2396B 2007-09-24 11:24:56 

// 求凸包

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    double x;
    double y;
    char str[50];
};

Node cor[10000];
int nNode;

int res[10000];
int nRes;

void Swap(Node& c1, Node& c2) {
    Node tem = c1;
    c1 = c2;
    c2 = tem;
}

double XMult(Node* n0, Node* n1, Node* n2) {
    return (n1->x-n0->x) * (n2->y-n0->y) -
           (n1->y-n0->y) * (n2->x-n0->x);
}

int Cmp(const void* c1, const void* c2) {
    double xm = XMult(cor+0, (Node*)c1, (Node*)c2);
    if( xm > 0 )    return -1;
    if( xm < 0 )    return 1;
    // xm == 0
    if( ((Node*)c1)->x < ((Node*)c2)->x )    return -1;
    return 1;
}

void Solve() {
    int id = 0;
    int i;

    // 找一个y坐标最小，x坐标尽量小的点
    for(i=1; i<nNode; i++) {
        if( cor[i].y < cor[id].y 
            || (cor[i].y == cor[id].y && cor[i].x < cor[id].x) ) {
            id = i;
        }
    }

    // 将这个点放在数组开头
    if( id != 0 ) {
        Swap(cor[0], cor[id]);
    }

    // 其他点根据极坐标优先、和cor[0]点距离次优先排序
    qsort(cor+1, nNode-1, sizeof(Node), Cmp);

    // 求凸包主要算法部分
    nRes = 0;
    res[nRes++] = 0;
    res[nRes++] = 1;
    int iter = 2;
    while( iter < nNode ) {
        while( nRes > 1 &&  XMult(cor+res[nRes-2], cor+res[nRes-1], cor+iter) <= 0 ) {
            -- nRes;
        }
        res[nRes++] = iter;
        ++ iter;
    }
}

void Output() {
    int i;
    printf("%s", cor[res[nRes-1]].str);
    for(i=0; i<nRes; i++) {
        printf(" %s", cor[res[i]].str);
    }
    printf("\n");
}

int main() {
    // freopen("input.txt", "r", stdin);
    char c;
    int read;
    while( nNode = 0, scanf("%s", cor[nNode].str) != EOF ) {
        sscanf(cor[nNode].str+1, "%lf%n", &cor[nNode].x, &read);
        sscanf(cor[nNode].str+read+2, "%lf", &cor[nNode].y);
        nNode ++;
        while( (c=getchar()) != '\n' ) {
            scanf("%s", cor[nNode].str);
            sscanf(cor[nNode].str+1, "%lf%n", &cor[nNode].x, &read);
            sscanf(cor[nNode].str+read+2, "%lf", &cor[nNode].y);
            nNode ++;
        }
        Solve();
        Output();
    }
    return 1;
}

