### 정리

---



#### DP

---

1. 완탐 설계
2. 전체 답의 점수 반환이 아닌, 앞으로 남은 선택들에 해당하는 점수 반환토록 부분문제 정의
3. 선택 꼭 필요한것만 남기기
4. 입력 배열, 문자열이면 적절하게 변환하기
5. 메모이제이션

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
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;
int mem[101][101];
string W, S;
bool match(int w, int s){
	int& ret = mem[w][s];
	if(ret != -1) return ret;
	while(w < W.size() && s < S.size() && (W[w]=='?' || W[w]==S[s])){
		return ret = match(w+1, s+1);
	}
	if(w == W.size()) return ret = (s == S.size());
	if(W[w] == '*')
		return ret = (match(w+1, s) || (s<S.size() && match(w, s+1)));
	return ret=0;
}
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> W;
		int n;
		cin >> n;
		vector<string> res;
		while(n--){
			memset(mem, -1, sizeof(mem));
			cin >> S;
			if(match(0, 0)) res.push_back(S);
		}
		sort(res.begin(), res.end());
		for(auto x: res) cout << x << endl;
	}
	return 0;
}
```

#### 삼각형 최대 경로 228p

https://www.algospot.com/judge/problem/read/TRIANGLEPATH

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
int a[101][101], mem[101][101];
int solve(int x, int y){
	if(x == n-1) return a[x][y];
	int& ret = mem[x][y];
	if(ret != -1) return ret;
	return ret = max(solve(x+1, y), solve(x+1, y+1))+a[x][y];
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		for(int i=0; i<n; i++)
			for(int j=0; j<=i; j++)
				scanf("%d", &a[i][j]);
		memset(mem, -1, sizeof(mem));
		printf("%d\n", solve(0, 0));
	}
	return 0;
}

```

#### LIS 230p

https://www.algospot.com/judge/problem/read/LIS

```c++
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int SIZE = 501;
int n, S[SIZE], cache[SIZE+1];
int lis3(int start){
	int& ret = cache[start+1];
	if(ret != -1) return ret;
	ret = 1;
	for(int next = start+1; next<n; ++next)
		if(start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next)+1);
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		memset(cache, -1, sizeof(cache));
		for(int i=0; i<n; i++)
			scanf("%d", &S[i]);
		printf("%d\n", lis3(-1)-1);
	}
	return 0;
}
```

#### 합친 LIS 236p

https://www.algospot.com/judge/problem/read/JLIS

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<limits> //numeric_limits
using namespace std;
typedef long long ll;
const long long INF = numeric_limits<ll>:: max();
const int SIZE = 101;
int n, m, A[SIZE], B[SIZE], cache[SIZE+1][SIZE+1];
int jlis(int indexA, int indexB){
	int& ret = cache[indexA+1][indexB+1];
	if(ret != -1) return ret;
	ret = 2;	//-INF인 A[-1] B[-1] 항상 존재
	ll a = (indexA == -1 ? -INF : A[indexA]);
	ll b = (indexB == -1 ? -INF : B[indexB]);
	ll maxElement = max(a, b);
	for(int nextA = indexA + 1; nextA < n; ++nextA)
		if(maxElement < A[nextA])
			ret = max(ret, jlis(nextA, indexB)+1);
	for(int nextB = indexB + 1; nextB < m; ++nextB)
		if(maxElement < B[nextB])
			ret = max(ret, jlis(indexA, nextB)+1);
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &m);
		for(int i=0; i<n; i++) scanf("%d", &A[i]);
		for(int i=0; i<m; i++) scanf("%d", &B[i]);
		memset(cache, -1, sizeof(cache));
		printf("%d\n", jlis(-1, -1)-2);
	}
	return 0;
}
```

#### 원주율 외우기 239p

https://www.algospot.com/judge/problem/read/PI

```c++
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF = (int)1e9;
string N;
int classify(int a, int b){
	string M = N.substr(a, b-a);
	//첫 글자로만 이루어진 문자열 
	if(M == string(M.size(), M[0])) return 1;	//M.size만큼 M[0]으로 만든 문자열
	//등차 수열 검사
	bool progressive = true;
	for(int i=0; i<M.size()-1; i++)
		if(M[i+1] - M[i] != M[1] - M[0])
			progressive = false;
	if(progressive && abs(M[1]-M[0]) == 1) return 2;
	//번갈아 등장하는지
	bool alternating = true;
	for(int i=0; i<M.size(); i++)
		if(M[i] != M[i%2])		//짝수는 0이랑, 홀수는 1이랑 비교 
			alternating = false;
	if(alternating) return 4;
	if(progressive) return 5;
	return 10; 
}
int cache[10002];
int memorize(int begin){
	if(begin == N.size()) return 0;
	int& ret = cache[begin];
	if(ret!=-1) return ret;
	ret = INF;
	for(int L = 3; L <=5; ++L)
		if(begin + L <= N.size())
			ret = min(ret, memorize(begin + L)+classify(begin, begin+L));
	return ret;
}
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> N;
		memset(cache, -1, sizeof(cache));
		cout << memorize(0) << endl;
	}
	return 0;
}
```

#### Quantization 244p

https://www.algospot.com/judge/problem/read/QUANTIZE

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF = (int)1e9;
int n;
int A[101], psum[101], psqsum[101];
void precalc(){
	sort(A, A+n);
	psum[0] = A[0];
	psqsum[0] = A[0]*A[0];
	for(int i=1; i<n; ++i){
		psum[i] = psum[i-1] + A[i];
		psqsum[i] = psqsum[i-1] + (A[i]*A[i]);
	}
}
int minError(int lo, int hi){
	int sum = psum[hi] - (lo==0 ? 0 : psum[lo-1]);
	int sqsum = psqsum[hi] - (lo==0 ? 0 : psqsum[lo-1]);
	//반올림한 값으로 수 표현
	int m = int(0.5 + (double)sum / (hi - lo + 1));
	int ret = sqsum - 2*m*sum + m*m*(hi-lo+1);
	return ret;
}
int cache[101][11];
int quantize(int from, int parts){
	if(from == n) return 0;
	if(parts == 0) return INF;
	int& ret = cache[from][parts];
	if(ret!=-1) return ret;
	ret = INF;
	for(int i=1; from+i<=n; i++)
		ret = min(ret, minError(from, from + i - 1) + quantize(from+i, parts-1));
	return ret;
}

int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		int m;
		scanf("%d %d", &n, &m);
		for(int i=0; i<n; i++)
			scanf("%d", &A[i]);
		precalc();
		memset(cache, -1, sizeof(cache));
		printf("%d\n", quantize(0, m));
	}
	return 0;
}
```

#### 타일링 방법의 수 세기 252p

https://www.algospot.com/judge/problem/read/TILING2

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
const int MOD = int(1e9)+7;
const int SIZE = 101;
int n;
int mem[SIZE];
int dp(int x){
	if(x <= 1) return 1;
	int& ret = mem[x];
	if(ret!=-1) return ret;
	return ret = (dp(x-1))%MOD + (dp(x-2))%MOD;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		memset(mem, -1, sizeof(mem));
		printf("%d\n", dp(n)%MOD);
	}
	return 0;
}
```

#### 삼각형 위의 최대 경로 개수 세기 254p

https://www.algospot.com/judge/problem/read/TRIPATHCNT

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int SIZE = 101;
int mem[SIZE][SIZE], cntMem[SIZE][SIZE];
int a[SIZE][SIZE];
int n;
int maxPath(int x, int y){
	if(x==n-1) return a[x][y];
	int& ret = mem[x][y];
	if(ret!=-1)return ret;
	ret = 0;
	return ret = max(maxPath(x+1, y), maxPath(x+1, y+1)) + a[x][y];
}
int solve(int x, int y){
	if(x==n-1) return 1;
	int& ret = cntMem[x][y];
	if(ret!=-1)return ret;
	ret = 0;
	if(maxPath(x+1, y) >= maxPath(x+1, y+1)) ret += solve(x+1, y);
	if(maxPath(x+1, y) <= maxPath(x+1, y+1)) ret += solve(x+1, y+1);
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		for(int i=0; i<n; i++)
			for(int j=0; j<=i; j++)
				scanf("%d", &a[i][j]);
		memset(mem, -1, sizeof(mem));
		memset(cntMem, -1, sizeof(cntMem));
		printf("%d\n", solve(0, 0));
	}
	return 0;
}
```

#### 장마가 찾아왔다 258p

https://www.algospot.com/judge/problem/read/SNAIL

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int SIZE = 1001;
int n,m;
double mem[SIZE][SIZE*2+1];
double solve(int pos, int climed){
	if(pos == m){
		if(climed >= n) return 1;
		return 0;
	}
	double& ret = mem[pos][climed];
	if(ret != -1.0) return ret;
	return ret = (double)solve(pos+1, climed+1)*0.25 + (double)solve(pos+1, climed+2)*0.75;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &m);
		//double memset 주의
		for(int i=0; i<m; i++)
			for(int j=0; j<2*m+1; j++)
				mem[i][j] = -1.0; 
		printf("%.10f\n", solve(0, 0));
	}
	return 0;
}
```

#### 비대칭 타일링 260p

https://www.algospot.com/judge/problem/read/ASYMTILING

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MOD = (int)1e9 + 7;
int n, mem[101], mem2[101];
int tiling(int x){
	if(x <= 1) return 1;
	int& ret = mem[x];
	if(ret != -1) return ret;
	return ret = (tiling(x-1) + tiling(x-2))%MOD;	//여기 나머지 연산 안해줘서 틀렸었음 
}

int asymmetric(int x){
	int ret = tiling(x);
	if(x % 2 == 1) return (ret - tiling(x/2) + MOD) % MOD;
	ret = (ret - tiling(x/2) + MOD) % MOD;
	ret = (ret - tiling(x/2-1) + MOD) % MOD;
	return ret;
}

int asymmetric2(int x){	//직접 세기(양쪽 끝에서 동시에 진행) 
	if(x <= 2) return 0; 
	int& ret = mem2[x];
	if(ret != -1) return ret;
	ret = asymmetric2(x-2) % MOD;			//a
	ret = (ret + asymmetric2(x-4)) % MOD;	//b
	ret = (ret + tiling(x-3)) % MOD;		//c		요기 MOD연산 때문에 ret+= 했다 틀림
	ret = (ret + tiling(x-3)) % MOD;		//d		또, (ret+tiling(x-3))*2 % MOD틀림
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		memset(mem, -1, sizeof(mem));
		memset(mem2, -1, sizeof(mem2));
		printf("%d\n", asymmetric2(n));
	}
	return 0;
}
```

#### 폴리오미노 264p

https://www.algospot.com/judge/problem/read/POLY

```c++
#include<cstdio>
#include<cstring>
using namespace std;
const int SIZE = 101, MOD = (int)1e7;
int mem[SIZE][SIZE];
int solve(int n, int first){
	if(n==first) return 1;
	int& ret = mem[n][first];
	if(ret!=-1)return ret;
	ret=0;
	for(int i=1; i+first<=n; i++){
		int add= (first+i-1);
		add *= solve(n-first, i);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		int n, ans=0;
		scanf("%d", &n);
		memset(mem, -1, sizeof(mem));
		for(int i=1; i<=n; i++)
			ans+=solve(n, i);
			ans %= MOD;
		printf("%d\n", ans);
	}
	return 0;
}
```

#### 두니발 박사의 탈옥 275p

https://www.algospot.com/judge/problem/read/NUMB3RS

```c++
#include<cstdio>
#include<cstring>
using namespace std;
int n, d, p, q;
int deg[51], a[51][51];
double mem[51][101];
double solve(int here, int days){
	if(days==0) return (here==p ? 1.0 : 0.0);
	double& ret = mem[here][days];
	if(ret > -0.5) return ret;
	ret = 0.0;
	for(int there=0; there<n; there++)
		if(a[here][there])
			ret += solve(there, days-1)/deg[there];
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d %d", &n, &d, &p);
		memset(deg, 0, sizeof(deg));
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++){
				scanf("%d", &a[i][j]);
				if(a[i][j]) deg[i]++;
			}
		for(int i=0; i<51; i++)
			for(int j=0; j<101; j++)
				mem[i][j]=-1.0;
		int t;
		scanf("%d", &t);
		while(t--){
			scanf("%d", &q);
			printf("%.8f ", solve(q, d));
		}
		printf("\n");
	}
	return 0;
}
```

