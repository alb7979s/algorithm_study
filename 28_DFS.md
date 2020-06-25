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
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> seen, order;
//알파벳 각 글자에 대한 인접 행렬
//간선 (i, j)는 알파벳 i가 j보다 앞에 와야함
void makeGraph(const vector<string>& words){
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	for (int j = 1; j < words.size(); j++){
		int i = j - 1, len = min(words[i].size(), words[j].size());
        //word[i]가 word[j] 앞에 오는 이유를 찾음
		for (int k = 0; k < len; k++)
			if (words[i][k] != words[j][k]){
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;
				break;
			}		
	}
}

void dfs(int here){
	seen[here] = 1;
	for (int there = 0; there < adj.size(); there++)
		if (adj[here][there] && !seen[there])
			dfs(there);
	order.push_back(here);
}
vector<int> topologicalSort(){
	int m = adj.size();
	seen = vector<int>(m, 0);
	order.clear();
	for (int i = 0; i < m; i++) if (!seen[i])dfs(i);
	reverse(order.begin(), order.end());
	//만약 그래프가 DAG아니면 역방향 간선 존재, 빈 벡터 반환
	for (int i = 0; i < m; i++)
		for (int j = i + 1; j < m; j++)
			if (adj[order[j]][order[i]])
				return vector<int>();
	return order;
}
int main(){
	int tc;
	cin >> tc;
	while (tc--){
		int n;
		cin >> n;
		vector<string> a(n);
		for (int i = 0; i < n; i++) cin >> a[i];
		makeGraph(a);
		vector<int> v = topologicalSort();
		if (v.empty()) cout << "INVALID HYPOTHESIS"; 
		else{
			for (int i = 0; i < v.size(); i++){
				cout << char(v[i] + 'a');
			}
		}
		cout << endl;
	}
	return 0;
}
```

