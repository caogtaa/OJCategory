// 620356 2008-05-08 22:55:54 Accepted 1671 343MS 4060K 1514 B G++ WAC 
// 静态 Trie

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define KEYNUM    10            // 字母数
#define BRDSIZE    100000

struct Trie{
private:
    static int m_link[BRDSIZE][KEYNUM];        // 连接信息
    static int m_size;
    static bool m_bLeaf[BRDSIZE];            // 附加信息
public:
    static void Init() {
        memset(m_link, -1, sizeof(m_link));
        m_size = 1;
    }

    bool Search(char *);
    void Insert(char *);
};

int Trie::m_link[BRDSIZE][KEYNUM] = {-1};
int Trie::m_size = 1;
bool Trie::m_bLeaf[BRDSIZE] = {0};

bool Trie::Search(char* x)
{
    int cur = 0;
    int i = 0;
    int child;
    while( x[i]) {
        child = x[i]-'0';
        if( -1 == m_link[cur][child] ) {
            return false;
        }
        cur = m_link[cur][child];
        i ++;
    }
    return m_bLeaf[cur];    // 判断是否叶子
}

void Trie::Insert(char* x)
{
    int cur = 0;
    int i = 0;
    int child;
    while( x[i] ) {
        child = x[i]-'0';
        if( -1 == m_link[cur][child] ) {
            m_link[cur][child] = m_size ++;
            m_bLeaf[m_link[cur][child]] = true;
        }
        m_bLeaf[cur] = false;
        cur = m_link[cur][child];
        i ++;
    }
}

char str[10000][11];

int main() {
    int T;
    int nNum;
    int i;
    bool bRes;
    Trie t;
    scanf("%d", &T);
    while( T-- ) {
        scanf("%d", &nNum);
        t.Init();
        bRes = true;
        for(i=0; i<nNum; i++) {
            scanf("%s", str[i]);
            t.Insert( str[i] );
        }
        for(i=0; i<nNum; i++) {
            if( !t.Search(str[i]) ) {
                bRes = false;
                break;
            }
        }
        if( bRes ) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}