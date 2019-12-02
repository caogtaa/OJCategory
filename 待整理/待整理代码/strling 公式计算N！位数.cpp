 double sum = 1.0;
 for ( int i = 1; i <= n; ++i )
  sum += log10( i ); // 然后对x取整，再加1

 return (int)sum;
