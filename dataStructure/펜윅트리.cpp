//�迭�� ������
#include<cstdio>
#include<vector>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	int sum(int pos) {
		++pos;	//index 1���� �����Ѵٰ� ����
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//LSB �������� ���� ���� Ž��
			pos &= (pos - 1);
		}
		return ret;
	}
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			//LSB �����ؼ� ���ذ��� ���Ե� ������ Ž��
			pos += (pos & -pos);
		}
	}
};
