// 【最大流】Edmonds Karp算法求最大流,复杂度 O(V*E^2)。

// 返回最大流,输入图容量
// 矩阵g[n][n],取非零值表示有边，s为源点，t为汇点，f[n][n]返回流量矩阵。

int EdmondsKarp(int n, int s, int t) {
    int i, j, k, c;
    int head, tail;
    int flow = 0;
    static int r[N][N];
    static int prev[N], visit[N];
    static int q[N];

    // 初始化流量网络和残留网络
    // r[][]: 残留网络
    for(i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            f[i][j] = 0;
            r[i][j] = g[i][j];
        }
    }

    // 在残留网络中找到一条s到t的最短路径
    while(1) {
        head = tail = 0;
        memset(visit, 0, sizeof(visit));
        q[tail++] = s;
        prev[s] = -1;
        visit[s] = true;

        // 宽度优先搜索从s到t的最短路径,记录路径的前驱，保存在prev[]里面
        while( head<tail && !visit[t] ) {
            k = q[head++];
            for(i=0; i<n; i++) {
                if( !visit[i] && r[k][i]>0 ) {
                    visit[i] = true;
                    prev[i] = k;
                    q[tail++] = i;
                }
            }
        }

        if( !visit[t] ) break;        //流量已达到最大

        // c: 当前增广路径所要增加的流量
        // j: 当前点
        // i: j的前驱点
        c = INFINITE;
        j = t;
        while( j!=s ) {
            i = prev[j];
            if( c>r[i][j] ) {
                c = r[i][j];
            }
            j = i;
        }
        //下面改进流量
        j = t;
        while( j!=s ) {
            i = prev[j];
            f[i][j] += c;
            f[j][i] = -f[i][j];
            r[i][j] = g[i][j]-f[i][j];
            r[j][i] = g[j][i]-f[j][i];
            j = i;
        }
        flow += c;
    }
    return flow;
}