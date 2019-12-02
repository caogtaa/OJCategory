//euclid & extenden_euclid
#include <iostream>
using namespace std;

int extenden_euclid(int a, int b, int& x, int& y){
    int x1, y1;
    int next;
    if(b==0){
        x=1;
        y=0;
        next=a;
        printf("gcd(%d, %d)=%d=%d*%d+%d*%d\n", a, b, next,a,x,b,y);
        return next;
    }
    next=extenden_euclid(b, a%b, x1, y1);
    x=y1;
    y=x1-a/b*y1;
    printf("gcd(%d, %d)=%d=%d*%d+%d*%d\n", a, b, next,a,x,b,y);
    return next;
}

int main(){
    int a, b;
    int x, y;
    scanf("%d %d", &a, &b);
    extenden_euclid(a, b, x, y);

    return 0;
}

http://www.cnblogs.com/frog112111/archive/2012/08/19/2646012.html