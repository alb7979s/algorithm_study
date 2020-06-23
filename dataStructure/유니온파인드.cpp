#include<vector>
#include<algorithm>
using namespace std;
//ġ��ģ Ʈ�� ���ϱ� ���� union-by-rank
//rank[] :: �ش� ��尡 �� Ʈ���� ��Ʈ�� ��� �ش� Ʈ���� ���̸� ����
//�� ��� ��ĥ �� ���̸� ���ؼ� ���� ������ ���� Ʈ���� ����Ƽ���� �����ϵ�, ������ ��� Ʈ�� ����+1
struct OptimizedDisjointSet {
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	if find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);	//��� ���� ����ȭ
	}
	void merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};
