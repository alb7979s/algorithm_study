## 정리

##### 크루스칼 :: O(|E|log|E|)

```c++
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int SIZE = 100;
typedef pair<int, int> P;
int V;
vector<P> adj[SIZE];
struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int n): parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	void merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};
int kruskal(vector<P>& selected) {
	int ret = 0;
	selected.clear();
	vector<pair<int, P> > edges;
	for(int u=0; u<V; u++)
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
		}
	sort(edges.begin(), edges.end());
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		if (sets.find(u) == sets.find(v))continue;
		sets.merge(u, v);
		selected.push_back({ u, v });
		ret += cost;
	}
	return ret;
}
```

##### 프림:: O(|E|log|V|) 

```c++
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int SIZE = 100;
bool visit[SIZE];
typedef pair<int, int> P;
vector<P> adj[SIZE];
int V, E;
int prim(int start) {
	visit[start] = true;
	priority_queue<P, vector<P>, greater<P>> pq;	//오름차순(최소힙)
	for (int i = 0; i < adj[start].size(); i++) {
		int nc = adj[start][i].first, nx = adj[start][i].second;
		pq.push({ nc, nx });
	}
	int res = 0;
	while (!pq.empty()) {
		int c = pq.top().first;
		int x = pq.top().second;
		if (visit[x]) continue;
		res += c;
		visit[x] = true;
		for (int i = 0; i < adj[x].size(); i++) {
			int nc = adj[x][i].first;
			int nx = adj[x][i].second;
			pq.push({ nc, nx });
		}
	}
	return res;
}
```

##### 근거리 네트워크979p

https://algospot.com/judge/problem/read/LAN

```python
#시간초과남 c++로 바꿔보기
from sys import*
from heapq import*
input = stdin.readline
def find(u):
    if parent[u] == u: return u
    parent[u] = find(parent[u])
    return parent[u]
def union(u, v):
    u = find(u); v = find(v)
    if(u==v): return u
    if(rank[u] > rank[v]): u, v = v, u
    parent[u] = v
    if(rank[u] == rank[v]): rank[v]+=1
for tc in range(int(input())):
    n,m = map(int,input().split())
    X=list(map(int,input().split()))
    Y=list(map(int,input().split()))
    parent=[i for i in range(n)]
    rank=[1 for i in range(n)]
    dist=[]
    res=0
    for i in range(m):
        a,b=map(int,input().split())
        union(a,b)
    for i in range(n):
        for j in range(i+1,n):
            dist.append(((((X[i]-X[j])**2) + ((Y[i]-Y[j])**2))**0.5, i, j))
    dist.sort()
    for d, x, y in dist:
        x = find(x)
        y = find(y)
        if x!=y:
            union(x, y)
            res += d
    print(res)
            

```

