inline int mmin(int a, int b){
	return a<b?a:b;
}

inline int mmax(int a, int b){
	return a>b?a:b;
}

bool InRg(int v, int r1, int r2){
	return (v>=mmin(r1, r2) && v<=mmax(r1, r2));
}

int XMul(Pnt* pp, Pnt* p1, Pnt* p2){
	//向量(pp-p1)和(p2-p1)的叉积
	if( p1->cy>p2->cy ){
		Pnt* tem = p1;
		p1 = p2;
		p2 = tem;
	}
    return (pp->cx-p1->cx)*(p2->cy-p1->cy)-
	   (pp->cy-p1->cy)*(p2->cx-p1->cx);
}

int Intersect(Pnt* pp, Pnt* p1, Pnt* p2){
	//判断以pp为起始点向左的射线是否和线段p1p2相交
	//约定如果和顶点相交只认可Y坐标比较大的顶点，避免重复计算
	return InRg(pp->cy, p1->cy, p2->cy) &&
		pp->cy != mmin(p1->cy, p2->cy) &&
		XMul(pp, p1, p2)<0;
}

bool InEdge(Pnt* pp, Pnt* p1, Pnt* p2){
	//判断点pp是否在线段p1p2上
	return InRg(pp->cx, p1->cx, p2->cx) &&
			InRg(pp->cy, p1->cy, p2->cy) &&
			XMul(pp, p1, p2)==0;
}
