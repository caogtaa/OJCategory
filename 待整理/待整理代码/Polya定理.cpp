// polya定理

bool b1[100];
bool b2[100];
bool bj[100];

int gcd(int p,int q)
{
    return (p%q)?gcd(q,p%q):q;
}

double polya1(int c,int n)//旋转和翻转视为相同
{
    int i;
    double t=0.0;
    for (i=0;i<n;i++) 
        t+=pow((double)c,(double)gcd(i,n));
    if (n%2)
        for (i=0;i<n;i++)
            t+=pow((double)c,(double)(n/2+1));
    else
        for (i=0;i<n/2;i++)
            t+=pow((double)c,(double)(n/2))+pow((double)c,(double)(n/2+1));
    return t/(2*n);
}


double polya2(int c,int n)//旋转视为相同，翻转为异
{
       int i,j,k,x,y;
       double t=0.0;
       memset(bj,0,sizeof(bj));
       for (i=0;i<=n-1;i++)
       {
             for (x=y=j=0;j<=n-1;j++)
                   if (!bj[(i+j)%n])
                         for (x++,k=(i+j)%n;!bj[k];k=(i+k)%n)
                               bj[k]=true;
             t=t+pow((double)c,(double)x);
       }
       return t/n;
}

double polya3(int c,int n)//翻转视为相同，旋转为异
{
       int x=n/2;
       if (n%2)       x++;
       return (pow((double)c,(double)n)+pow((double)c,(double)x))/2;
}