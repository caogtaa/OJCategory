#define NONE -1
#define MULTI -2

struct Node{
    int m_sp, m_ep;
    int m_color;
    Node* m_pl;
    Node* m_pr;
    void Paint(int, int, int);
    void Construct(int, int);
};

Node STree[16000];
int treesize;

void Node::Construct(int sp, int ep){
    m_sp = sp;
    m_ep = ep;
    if(sp+1 == ep){
        m_pl = NULL;
        m_pr = NULL;
        return;
    }
    int mid = (sp+ep)>>1;
    m_pl = &STree[treesize++];
    m_pr = &STree[treesize++];

    m_pl->Construct(sp, mid);
    m_pr->Construct(mid, ep);
}

void Node::Paint(int sp, int ep, int color){
    if( color == m_color )
        return ;
    if( sp == m_sp && ep == m_ep ){
        m_color = color;
        return ;
    }
    int mid = (m_sp+m_ep)>>1;
    //------¾²Ì¬
    if( m_color != MULTI ){
        m_pl->m_color = m_color;
        m_pr->m_color = m_color;
        m_color = MULTI;
    }
    //-------
    //m_color == MULTI here
    if( ep <= mid ){
        m_pl->Paint(sp, ep, color);
        return ;
    }
    if( sp >= mid ){
        m_pr->Paint(sp, ep, color);
        return ;
    }
    m_pl->Paint(sp, mid, color);
    m_pr->Paint(mid, ep, color);
}
