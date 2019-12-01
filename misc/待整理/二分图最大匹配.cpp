//--------initialize
memset(m1to2, -1, sizeof(int)*nc);
memset(m2to1, -1, sizeof(int)*(ns+1));
//

int nc, ns;            //一部中点数、二部中点数
bool map[100][301];        //一部中点i到二部中点j是否有直接路径
int m1to2[100];            //一部中的点k和二部中的m1to2[k]匹配，-1表示点k未匹配
int m2to1[301];            //二部中的点k和一部中的m2to1[k]匹配，-1表示点k未匹配
bool visited[301];        //寻找赠广路径时点k是否已经被访问过，只需记录二部中的点

bool FindPath(int nn){
    //每次进入前需要将visited全部置false
    //寻找赠广路径，如果找到时该路径反转并返回true，否则返回false
    int i;
    for(i=1; i<=ns; i++){
        if(map[nn][i] && !visited[i]){
            visited[i] = true;
            if(m2to1[i]==-1 || FindPath(m2to1[i])){
                m1to2[nn] = i;
                m2to1[i] = nn;
                return true;
            }
        }
    }
    return false;
}

//----1140中的调用
bool Solve(){
    // 判断是否能获得最大匹配
    int i;
    for(i=0; i<nc; i++){
        if(m1to2[i] == -1){        // 这行不必要
            memset(visited, false, sizeof(bool)*(ns+1));
            if(!FindPath(i)){
                return false;
            }
        }
    }
    return true;
}

//------如果计算最大匹配，则
int Match(){
    int ret = 0;
    for(int i=0; i<nc; i++){
        memset(visited, false, sizeof(visited));
        ret += FindPath(i);
    }
    return ret;
}
