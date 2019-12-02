map[i][j]    :bool值，表示点i到点j是否有直接路径
fee[i][j]    :边(i,j)的权
final[k]    :是否已经求出源点到点k的最短路径
dist[k]        :已知的源点到点k的最短路径长度
INFINITE    :程序中不可达到的无穷大

int Dijkstra(int from, int to){
    //caculate distance from 'from' to 'to'
    //'nhi' indicate nodes amount
    int i, k;
    int mindist, nearest;
    memset(final, false, sizeof(bool)*nhi);
    final[from] = true;
    for(k=0; k<nhi; k++){
        if(!final[k] && map[from][k]){
            dist[k] = fee[from][k];
        }
        else{
            dist[k] = INFINITE;
        }
    }
    for(i=1; i<nhi && !final[to]; i++){                //nhi-1次
        //find nearest node not in set
        nearest = -1;
        mindist = INFINITE;
        for(k=0; k<nhi; k++){
            if(!final[k] && dist[k]<mindist){
                mindist = dist[k];
                nearest = k;
            }
        }
        if( nearest == -1 )
            return INFITITE;
        //include this node
        final[nearest] = true;
        //refresh distance to other node not in set
        for(k=0; k<nhi; k++){
            if(!final[k] && map[nearest][k] && (dist[k]>dist[nearest]+fee[nearest][k]) ){
                dist[k] = dist[nearest]+fee[nearest][k];
            }
        }
    }

    return dist[to];
}
