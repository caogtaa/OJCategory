void get_next(int& next[]){
    // 计算NEXT数组
    int i, j;
    next[0] = -1;
    j = -1;
    for(i=0; i<T.size(); ){
        // T为模式串, S为主串
        if( j==-1 || T[i]==T[j] ){
            i ++;
            j ++;
            next[i] = j;
        }
        else{
            j = next[j];
        }
    }
}

int sub_str(string& S, string& T, int spos){
    // spos 位置开始寻找与模式串T匹配的索引位置
    int i, j;
    i=spos;
    j=0;
    while( i<S.size() && j<T.size() ) {
        if (j==-1 || S[i] == T[j] ){
            i ++;
            j ++;
        }// 不失配则继续比较后续字符
        else {
            j = next[j];
        }
    }
    if( j>=T.size() )    return i-T.size();    // 子串结束，说明匹配成功
    else            return -1;        // 匹配失败
}

void get_nextval(int& nextval[]){
    int i, j;
    nextval[0] = -1;
    j = -1;
    for(i=0; i<T.size()-1; ){    // 这里更改过，之前是T.size()
        // T为模式串, S为主串
        if( j==-1 || T[i]==T[j] ){
            i ++;
            j ++;
            if( T[i]!=T[j] ){
                nextval[i] = j;
            }
            else{
                nextval[i] = nextval[j];
            }
        }
        else{
            j = nextval[j];
        }
    }

}
