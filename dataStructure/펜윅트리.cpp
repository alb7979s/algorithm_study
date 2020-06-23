//배열의 구간합
#include<cstdio>
#include<vector>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	int sum(int pos) {
		++pos;	//index 1부터 시작한다고 가정
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//LSB 지워가며 다음 구간 탐색
			pos &= (pos - 1);
		}
		return ret;
	}
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			//LSB 추출해서 더해가며 포함된 구간들 탐색
			pos += (pos & -pos);
		}
	}
};
