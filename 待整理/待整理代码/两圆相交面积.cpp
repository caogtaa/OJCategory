ZJU 1597

#include <stdio.h>
#include <math.h>

#define PI	3.14159265358979323846264338327950288

inline double M2(double x){
	return x*x;
}

inline void Swap(double& d1, double& d2){
	d1 = d1+d2;
	d2 = d1-d2;
	d1 = d1-d2;
}

int main(){
	double x1, y1, r1, x2, y2, r2;
	double a, b, c;					// 三条边长
	double s, p;					// s:面积
	double deg1, deg2;
	double s1, s2;					// 拱形部分面积
	while( scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2) != EOF ){
		if( r1<r2 ){	// 第1组数据始终是大圆的
			Swap(x1, x2);
			Swap(y1, y2);
			Swap(r1, r2);
		}
		a = r1;
		b = r2;
		c = sqrt(M2(x1-x2)+M2(y1-y2));
		if( c>=a+b ){
			// 两圆不相交
			printf("%.3lf\n", 0.0);
			continue;
		}
		if( b+c<=a ){
			// 小圆在大圆内，相交面积为小圆面积
			printf("%.3lf\n", PI*M2(b));
			continue;
		}

		p = (a+b+c)/2;
		s = sqrt(p*(p-a)*(p-b)*(p-c));
		deg1 = 2*asin(2*s/a/c);

		deg2 = 2*asin(2*s/b/c);
		if( M2(a)>M2(b)+M2(c) ){
			// 小圆心两半径呈>PI的角
			deg2 = 2*PI-deg2;
		};


		double tem = asin(1.0);
		double tt = sin(90.0);
		double ta = sin(PI/4);

		s1 = deg1/2*M2(r1) - sin(deg1)*M2(r1)/2;
		if( M2(a)>M2(b)+M2(c) ){
			s2 = deg2/2*M2(r2) + sin(2*PI-deg2)*M2(r2)/2;
		}
		else{
			s2 = deg2/2*M2(r2) - sin(deg2)*M2(r2)/2;
		}

		printf("%.3lf\n", s1+s2);
	}

	return 1;
}



如果C++ 提交失败尝试使用C
余弦定理
a^2=b^2+c^2-2*b*c*CosA

HDU 1798

#include <stdio.h>
#include <math.h>

#define PI    acos(-1)

double M2(double x){
    return x*x;
}

void Swap(double* d1, double* d2){
	double tem = *d1;
	*d1 = *d2;
	*d2 = tem;
}

int main(){
    double x1, y1, r1, x2, y2, r2;
    double a, b, c;                    // 三条边长
    double deg1, deg2;
    double s1, s2;                    // 拱形部分面积
    while( scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2) != EOF ){
        if( r1<r2 ){    // 第1组数据始终是大圆的
            Swap(&x1, &x2);
            Swap(&y1, &y2);
            Swap(&r1, &r2);
        }
        a = r1;
        b = r2;
        c = sqrt(M2(x1-x2)+M2(y1-y2));
        if( c-a-b>-1e-5 ){
            // 两圆不相交
            printf("%.3lf\n", 0.0);
            continue;
        }
        if( b+c-a<-1e-5 ){
            // 小圆在大圆内，相交面积为小圆面积
            printf("%.3lf\n", PI*M2(b));
            continue;
        }

		// 余弦定理

		deg1 = 2*acos( (M2(a)+M2(c)-M2(b)) / 2/a/c );
		deg2 = 2*acos( (M2(b)+M2(c)-M2(a)) / 2/b/c );


		s1 = deg1/2*M2(r1) - sin(deg1)*M2(r1)/2;
		s2 = deg2/2*M2(r2) - sin(deg2)*M2(r2)/2;

        printf("%.3lf\n", s1+s2);
    }

    return 1;
}

积分法 from javaman

#include <stdio.h>
#include <math.h>
double area(double,double);
double area(double x,double r) {
	return 0.5*(x*sqrt(r*r-x*x)+r*r*asin(x/r));
}

#define PI acos(-1)
main() {
double x,xx,yy,d,r,x1,x2,y1,y2,j1,j2,a,r1,r2;
	while (scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&r1,&x2,&y2,&r2)!=EOF) {
		xx=x1-x2;
		yy=y1-y2;
		d=sqrt(xx*xx+yy*yy);
		r=(r1<r2)?r1:r2;
		if (d>=r1+r2) {printf("0.000\n");continue;}
		else if (d<=fabs(r1-r2)) {printf("%.3f\n",PI*r*r);continue;}
		x=(r1*r1-r2*r2)/2/d+d/2;
		a=-area(x,r1)+area(r1,r1)-area(-r2,r2)+area(x-d,r2);
		printf("%.3f\n",a*2);
	}
}
