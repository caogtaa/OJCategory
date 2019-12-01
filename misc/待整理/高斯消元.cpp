/*
高斯消元法的应用 

  应用范围：求解多元一次方程组(特别在解决几何题目时比较有用)
  sample input：
  2 5 8
  9 2 12
  sample output:
  x1:1.073171
  x2:1.170732
  对应方程如下:
  {2x + 5y = 8
  {9x + 2y = 12   
*/

#include <stdio.h>
#include <stdlib.h>

void main( void )
{
    int n, i, j, k;
    double client, temp = 0.0;
    double **a;

    printf("输入方式如下(系数以0表示无),最后一列是B的值:\n");
    printf("4 5 2 3 2 5\n");
    printf("4 6 2 1 0 2\n");
    printf("4 5 2 1 3 2\n");
    printf("1 2 1 2 3 2\n");
    printf("0 2 5 1 1 3\n");

    printf("请输入未知量的个数:");
    scanf("%d", &n);
    printf("\n请输入系数矩阵和右端向量\n");

    //分配内存空间
    a = new double *[n]; 
    for (i =0 ; i < n; i++)
        a[i]= new double[n + 1];

    //输入数据
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    for(k = 0; k < n - 1; k++) {
        // 消除第k元
        for(i = k + 1; i < n; i++) {
            client = a[i][k]/a[k][k];
            for(j = k + 1; j <= n; j++) {
                a[i][j] = a[i][j] - client * a[k][j];    // 第i行-=第k行*client
            }
        }
    }

    a[n - 1][n] = a[n - 1][n]/a[n - 1][n - 1];            // 求第n-1元
    for(i = n - 2; i >= 0; i--) {
        temp=0.0;
        for (j = i + 1; j < n; j++) {                // 代入第i+1~n-1元
            temp += a[i][j] * a[j][n];
        }
        a[i][n] = (a[i][n] - temp) / a[i][i];            // 计算第i元
    }

    for(i = 0; i < n; i++) {
        printf("X%d = %lf\n", i + 1, a[i][n]);
    }
}
