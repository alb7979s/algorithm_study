## 정리

##### DFS

```c++
#include<vector>
#include<iostream>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
void dfs(int here) {
	cout << "DFS visits " << here << endl;
	visited[here] = true;
	for (int i = 0; i < adj[here].size; i++) {
		int there = adj[here][i];
		if (!visited[there]) {
			dfs(there);
		}
	}
}
void dfsAll() {		//얘를 호출해서 모든 정점 방문(모든 정점 연결되어 있다는 보장 없기 때문에)
	visited = vector<bool>(adj.size(), false);
	for (int i = 0; i < adj.size(); i++)
		if (!visited[i])
			dfs(i);
}
```

##### 위상정렬

::dfs() 종료할 때마다 정점 기록하고 뒤집으면 됨!

##### 고대어 사전 831p

https://algospot.com/judge/problem/read/DICTIONARY

```c++

```

