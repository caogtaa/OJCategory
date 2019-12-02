void InitPhi() {		// 适合迭代计算多个phi[x]
	phi[1] = 1;

	int k;
	int i;
	int a, b, c;
	for(k=2; k<MAXPHI; k++) {
		for(i=0; i<prmList.size(); i++) {
			if( k%prmList[i]==0 ) {
				if( k==prmList[i] ) {
					phi[k] = k-1;
					break;
				}
				a = prmList[i];
				b = k/prmList[i];
				c = gcd(a, b);
				phi[k] = phi[a]*phi[b]*c/phi[c];

				break;
			}
		}
	}
}

int AnotherPhi(int x) {			// 适合计算单个phi[x]
	double ret = x;
	int i;
	int lmt = (int)sqrt(x);
	for(i=0; prmList[i]<=lmt; i++) {	// 注意i不要超出prmList向量
		if( x%prmList[i]==0 ) {
			ret *= (1.0-1.0/prmList[i]);
		}
		while( x%prmList[i]==0 ) {
			x /= prmList[i];
		}
	}
	if( x>1 ) {
		ret *= (1.0-1.0/x);
	}
	return (int)(ret+0.5);
}