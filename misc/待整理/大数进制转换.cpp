// 2007-03-15 21:39:11 Accepted 1352 C++ 00:00.00 400K 

// 大数进制转换

#include <stdio.h>
#include <string.h>

char data[1000];
int in[1000];
int out[1000];
char decode[62];    // 十进制到字符的转换 
int encode[256];    // 字符到十进制的转换     

int from, to;
int nin, nout;        // 转换前长度，转换后长度 

void Input()
{
    scanf("%d %d %s", &from, &to, data);
    nin = (int)strlen(data);
    for(int i=0; i<nin; i++){
        in[i] = encode[data[i]];        
    }
}

void Output()
{
    printf("%d %s\n", from, data);
    printf("%d ", to);
    for(int i=nout-1; i>=0; i--){
        printf("%c", decode[out[i]]);
    }
    printf("\n\n");
}

void Init()
{
    int i;
    for(i=0; i<10; i++){
        decode[i] = i+'0';
        encode[i+'0'] = i;
    }
    for(i=10; i<36; i++){
        decode[i] = i-10+'A';
        encode[i-10+'A'] = i;
    }
    for(i=36; i<62; i++){
        decode[i] = i-36+'a';
        encode[i-36+'a'] = i;
    }
}

void Solve(){
    // 从进制from转到进制to 
    int yu, i, j;
    j = 0;
    nout = 0;
    while( j<nin ){
        yu = 0;
        for(i=j; i<nin; i++){
            yu = yu*from+in[i];
            in[i] = 0;
            if(yu >= to){
                in[i] = yu/to;
                yu %= to;
            }
        }
        out[nout++] = yu;
        while( j<nin && in[j]==0 )
            j++;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    Init();
    while( T-- ){
        Input();
        Solve();
        Output();
    }

    return 1;
}

