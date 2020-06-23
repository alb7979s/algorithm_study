#include<vector>
#include<algorithm>
using namespace std;
//치우친 트리 피하기 위한 union-by-rank
//rank[] :: 해당 노드가 한 트리의 루트인 경우 해당 트리의 높이를 저장
//두 노드 합칠 때 높이를 비교해서 낮은 ㅈ고을 높은 트리의 서브티르로 포함하되, 같으면 결과 트리 높이+1
struct OptimizedDisjointSet {
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	if find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);	//경로 압축 최적화
	}
	void merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};
