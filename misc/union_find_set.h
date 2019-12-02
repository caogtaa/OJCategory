#include <vector>

class UnionFindSet {
public:
	UnionFindSet(int n);

	int find(int x);

	void union2(int x1, int x2);

private:
	// _v[k]小于0时表示k点为该集的根，且|_v[k]|表示该集元素个数
	// _v[k]大于0时表示k点的父亲元素的ID号
	std::vector<int> _v;
};