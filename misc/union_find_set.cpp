// #include <xutility>
#include "union_find_set.h"

using namespace std;

UnionFindSet::UnionFindSet(int n) {
	_v.resize(n);
	fill(_v.begin(), _v.end(), -1);
}

int UnionFindSet::find(int x) {
	int root, tem;
	root = tem = x;
	while (_v[root] >= 0) {
		root = _v[root];
	}

	// 压缩路径
	while (x != root) {
		tem = _v[x];
		_v[x] = root;
		x = tem;
	}

	return root;
}

void UnionFindSet::union2(int x1, int x2) {
	// 元素少的集合并到元素多的集合里面
	x1 = find(x1);
	x2 = find(x2);
	if (x1 == x2)
		return;

	if (_v[x1] < _v[x2]) {
		_v[x1] += _v[x2];
		_v[x2] = x1;
	} else {
		_v[x2] += _v[x1];
		_v[x1] = x2;
	}
}
