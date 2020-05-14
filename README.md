### 정리

---



#### DP

---

##### 외발뛰기 215p 

https://www.algospot.com/judge/problem/read/JUMPGAME

```c++
#include<cstdio>
#include<cstring> 	//memset
using namespace std;
int n;
int mem[101][101], a[101][101];
int dp(int x, int y){
	if(x > n-1 || y > n-1) return 0;
	if(x == n-1 && y == n-1) return 1;
	int& ret = mem[x][y];
	if(ret != -1) return ret;
	int next = a[x][y];
	return ret = (dp(x+next, y) || dp(x, y+next));
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		memset(mem, -1, sizeof(mem));
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				scanf("%d", &a[i][j]);
		printf(dp(0,0) ? "YES\n" : "NO\n");		//개행 안넣어서 틀렸었음..
	}
	return 0;
}
```



```python
#BFS로도 풀림
from sys import*
from collections import*
input = stdin.readline
for tc in range(int(input())):
    n = int(input())
    a=[list(map(int,input().split())) for _ in range(n)]
    q=deque()
    q.append((0,0))
    visit=[[0]*n for _ in range(n)]
    visit[0][0]=1
    f=False
    while q:
        x, y = q.popleft()
        d = a[x][y]
        for dx, dy in [(d,0), (0,d)]:
            nx, ny = x+dx, y+dy
            if nx<0 or ny<0 or nx>n-1 or ny>n-1 or visit[nx][ny]:continue
            visit[nx][ny]=visit[x][y]+1
            q.append((nx, ny))
            if nx == n-1 and ny == n-1:
                f=True
                break
    print('YES' if f else 'NO')
```

##### 와일드 카드 218p

https://www.algospot.com/judge/problem/read/WILDCARD

```c++
#include<cstdio>
#include<cstring> 	//memset
using namespace std;
bool match(const string& w, const string& s){
	int pos = 0;
	while(pos < s.size() && pos < w.size() && (w[pos]=='?' || w[pos]==s[pos])) ++pos;
	if(pos == w.size()) return pos == s.size();
	if(w[pos] == '*')
		for(int skip=0; pos+skip <= s.size(); ++skip)
			if(match(w.substr(pos+1), s.substr(pos+skip)))
				return true;
	return false;
}

int chche[101][101];
string W, S;
bool matchMemoized(int w, int s){
	int& ret = cache[w][s];
	if(ret!=-1) return ret;
	while(s < S.size() && w < W.size() && (W[w] =='?' || w[W] == S[s])){
		++w;
		++s;
	}
	if(w == W.size()) return ret = (s == S.size());
	if(W[w] == '*')
		for(int skip=0; skip+s <= S.size(); ++skip)
			if(matchMemoized(w+1, s+skip))
				return ret = 1;
	return ret = 0;
}

```

