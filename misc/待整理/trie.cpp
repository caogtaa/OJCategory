#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define keyNum 26            // 字母数
#define MaxN 50                // 单词最大长度

struct trie{
    struct trieNode{        // trie结点的结构
        trieNode *link[keyNum];    // 下标为 'A' , 'B' , 'C' ,  , 'Z' 的指针数组
        bool bLeaf;                // 是否有某个单词的结尾在这个结点中
        trieNode(){
            memset(link,NULL,sizeof(link));
            bLeaf = false;
        }
        void init(){
            memset(link,NULL,sizeof(link));
            bLeaf = false;
        }
    };
    trieNode* root;
    trie()
    {
        root=(trieNode*)malloc(sizeof(trieNode));//初始化时为root申请了空间
        root->init();
    }
    ~trie() 
    {
        Delete(root);
    }
    bool Search(char *, int);
    void Insert(char *);
    void Delete(trieNode*);
};
bool trie::Search(char* x, int len)
{
    trieNode* cur = root;
    int i = 0;

    while( /*x[i]*/i<len ) {
        if( NULL == cur->link[x[i]-'a'] ) {
            return false;
        }
        cur = cur->link[x[i]-'a'];
        i ++;
    }
    return cur->bLeaf;    // 判断是否叶子
}

void trie::Delete(trieNode* t)
{
    int i;
    for(i=0;i<keyNum;i++)
        if(t->link[i])Delete(t->link[i]);
    delete(t);
}

void trie::Insert(char* x)
{
    trieNode *cur = root;
    int i = 0;
    while( x[i] ) {
        if( cur->link[x[i]-'a'] == NULL ) {
            cur->link[x[i]-'a'] = new trie::trieNode;
        }
        cur = cur->link[x[i]-'a'];
        i ++;
    }
    cur->bLeaf = true;
}
char c[50000][MaxN];