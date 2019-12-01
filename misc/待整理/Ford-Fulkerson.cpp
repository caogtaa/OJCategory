#include <stdio.h>
#include <string.h>
#define maxn 250
struct Map
{
    int f;
    int c;
}map[maxn][maxn];
int pre[maxn];
int q[maxn*maxn];
int v[maxn];
int N,M;
int s,t;
int abs( int x ){ return x > 0 ? x : -x ; }
int min( int x, int y ){ return  x < y ? x : y; }
void init()
{
    int i, S, E, C;
    memset( map, 0, sizeof(map) );
    for(i=0;i<N;i++)
    {
        scanf( "%d%d%d", &S, &E, &C );
        map[S][E].c += C;
    } 
}
void solve()
{
    int i,j;
    int head,tail;
    s = 1;
    t = M;
    while(true)
    {
        memset( pre, 0, sizeof(pre) );
        head = 0, tail = 1;
        q[0] = s;
        v[s] = 1000000000;
        pre[s] = s;
        while( head < tail && pre[t] == 0 )
        {
            i = q[head];
            for( j = 1; j <= M; j++ )
            {
                if( pre[j] == 0 )
                {
                    if( map[i][j].f < map[i][j].c )
                        pre[j] = i , q[tail++] = j , v[j] = min( v[i], map[i][j].c-map[i][j].f );
                    else if( map[j][i].f > 0 )
                        pre[j] = -i, q[tail++] = j , v[j] = min( v[i], map[j][i].f );
                }
            }
            head++;
        }
        if( pre[t] == 0 )break;

        i = t;
        while( i != s )
        {
            j = abs( pre[i] );
            if( pre[i] > 0 )map[j][i].f += v[t];
            else map[i][j].f -= v[t];
            i = j;
        }
    }
    int ans = 0;
    for( i = 1; i <= M; i++ )ans += map[s][i].f;
    printf("%d\n",ans);
}
int main()
{
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}