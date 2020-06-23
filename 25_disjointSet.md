## 정리

##### union-find

```c++
#include<cstdio>
#include<vector>
using namespace std;
struct NaiveDisjointSet{
    vector<int> parent;
    //초기화
    NaiveDisjointSet(int n): parent(n){
        for(int i=0; i<n; i++)
            parent[i] = i;
    }
    int find(int u) {
        if(u == parent[u]) return u;
        return find(parent[u]);
    }
    void merge(int u, int v){
        u = find(u), v = find(v);
        if(u==v) return;
        parent[u] = v;
    }
};
```

##### union-find 최적화

```c++
//치우친 트리 피하기 위한 union-by-rank
//rank[] :: 해당 노드가 한 트리의 루트인 경우 해당 트리의 높이를 저장
//두 노드 합칠 때 높이를 비교해서 낮은 ㅈ고을 높은 트리의 서브티르로 포함하되, 같으면 결과 트리 높이+1
struct OptimizedDisjointSet{
    vector<int> parent, rank;
    OptimizedDisjointSet(int n): parent(n), rank(n, 1){
        for(int i=0; i<n; i++)
            parent[i] = i;
    }
    if find(int u){
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);	//경로 압축 최적화
    }
    void merge(int u, int v){
        u = find(u), v = find(v);
        if(u==v) return;
        if(rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if(rank[u] == rank[v]) rank[v]++;
    }
};
```

##### 에디터 전쟁 772p

https://algospot.com/judge/problem/read/EDITORWARS

```c++
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
int n, m;
struct BipartiteUnionFInd {
	vector<int> parent, rank, enemy, size;
	BipartiteUnionFInd(int n) : parent(n), rank(n, 0), enemy(n, -1),
		size(n, 1) {
		for (int i = 0; i < n; i++)parent[i] = i;
	}
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	int merge(int u, int v) {
		//u or v가 공집합인 경우 나머지 하나 반환
		if (u == -1 || v == -1) return max(u, v);
		u = find(u), v = find(v);
		if (u == v) return u;
		if (rank[u] > rank[v]) swap(u, v);
		if (rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
		size[v] += size[u];
		return v;
	}
	//u와 v서로 적, 모순이면 false 반환
	bool dis(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return false;
		int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
		enemy[a] = b; enemy[b] = a;
		return true;
	}
	//u와 v서로 동지, 모순이면 false 반환
	bool ack(int u, int v) {
		u = find(u), v = find(v);
		if (enemy[u] == v) return false;
		int a = merge(u, v), b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		if (b != -1) enemy[b] = a;
		return true;
	}
};
int maxParty(BipartiteUnionFInd& buf) {
	int ret = 0;
	for (int node = 0; node < n; node++) {
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];
			if (enemy > node) continue;
			int mySize = buf.size[node];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
			ret += max(mySize, enemySize);
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		cin >> n >> m;
		BipartiteUnionFInd buf(n);
		int num = -1;
		bool flag = false;
		for (int i = 0; i < m; i++) {
			string s;
			int node1, node2;
			cin >> s >> node1 >> node2;
			if (flag) continue;
			if (s == "ACK") {
				if (!buf.ack(node1, node2)) {
					flag = true;
					num = i + 1;
				}
			}
			else {
				if (!buf.dis(node1, node2)) {
					flag = true;
					num = i + 1;
				}
			}
		}
		if (flag)
			cout << "CONTRADICTION AT " << num << endl;
		else
			cout << "MAX PARTY SIZE IS " << maxParty(buf) << endl;
	}
	return 0;
}
```

