inline int LowBit(int x){
    // 求x最低位1的权
    return x & (x^(x-1));
}
定义C[i] = a[i-2^k+1]+a[i-2^k+2]+...+a[i];
若要修改 a[k]的值，则C数组的修改过程如下：(n为C数组的大小)
void Change(int k, int delta){
    while( k<=n ){
        C[k] += delta;
        k += LowBit(k);
    }
}

求a中1..k元素的和
int Getsum(int k){
    int ret = 0;
    while( k>0 ){
        ret += C[k];
        k -= LowBit(k);
    }
    return ret;
}

若要求i..j的元素和的值，则求出
1~i-1和1~j的值，相减即可

注意树状数组从下标1开始存。Lowbit(0) = 0