UFSet[k]    :小于0时表示k点为该集的根，且|UFSet[k]|表示该集元素个数
        :大于0时表示k点的父亲元素的ID号

int UFSet[100];

memset(UFSet, -1, sizeof(int)*100);

int FindSet(int x){
    int root, tem;
    root = tem = x;
    while( UFSet[root]>=0 ){
        root = UFSet[root];
    }
    //压缩路径
    while( x != root ){
        tem = UFSet[x];
        UFSet[x] = root;
        x = tem;
    }
    return root;
}

void UnionSet(int x1, int x2){
    //元素少的集合并到元素多的集合里面
    x1 = FindSet(x1);
    x2 = FindSet(x2);
    if( x1==x2 )        return ;
    if( UFSet[x1]<UFSet[x2] ){
        UFSet[x1] += UFSet[x2];
        UFSet[x2] = x1;
    }
    else{
        UFSet[x2] += UFSet[x1];
        UFSet[x1] = x2;
    }
}
