## 정리



#### 보글게임 150p

https://www.algospot.com/judge/problem/read/BOGGLE

```c++
#include<cstdio>
#include<vector>
#include<cstring>

using namespace std;
const int dx[] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[] = {-1, 0, 1, -1, 0, 1, -1, 1};
char word[11], board[5][5];
int mem[5][5][11]; //x, y, idx
int wordlen = 0;
bool hasWord(int x, int y, int idx){
	if(board[x][y] != word[idx]) return false;
	if(idx == wordlen-1) return true;
	int nx, ny, nidx;
	for(int i=0; i<8; i++){
		nx = x+dx[i], ny = y+dy[i], nidx=idx+1;
		if(nx<0 || ny<0 || nx>4 || ny>4 || mem[nx][ny][nidx]) continue;
		if(hasWord(nx, ny, nidx)) return true;
	}
	//위에서 못찾고 끝내면 이 길은 아님 
	mem[x][y][idx] = 1;
	return 0;
}
bool solve(){
	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			if(hasWord(i, j, 0)) return true;
	return false;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		for(int i=0; i<5; i++)
			scanf("%s", board[i]);
		int n;
		scanf("%d", &n);
		while(n--){
			memset(mem, 0, sizeof(mem));
			scanf("%s", word);
			wordlen = strlen(word);
			if(solve())
				printf("%s YES\n", word);
			else
				printf("%s NO\n", word);
		}
	}
	return 0;
}
```

#### 소풍 155p

https://www.algospot.com/judge/problem/read/PICNIC

```c++
#include<cstdio>
#include<cstring>
using namespace std;
int n;
bool areFriends[10][10];

int countPairings(bool taken[10]){
	int firstFree = -1;
	for(int i=0; i<n; ++i){
		if(!taken[i]){
			firstFree=i;
			break;
		}
	}
	if(firstFree==-1) return 1;
	int ret = 0;
	for(int i=firstFree+1; i<n; i++){
		if(!taken[i] && areFriends[firstFree][i]){
			taken[firstFree] = taken[i] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[i] = false;
		}
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		int m;
		scanf("%d %d", &n, &m);
		for(int i=0; i<10; i++)
			for(int j=0; j<10; j++)
				areFriends[i][j]=false;
		for(int i=0; i<m; i++){
			int t1, t2;
			scanf("%d %d", &t1, &t2);
			areFriends[t1][t2] = areFriends[t2][t1] = true;
		}
		bool taken[10] = {false,};
		printf("%d\n", countPairings(taken));
	}
	return 0;
}
```

#### 게임판 덮기 159p

https://www.algospot.com/judge/problem/read/BOARDCOVER

```c++
#include<cstring>
#include<cstdio>
using namespace std;
const int dd[4][3][2] = {{{0, 0}, {1, 0}, {1, 1}},
						{{0, 0}, {1, 0}, {1, -1}},
						{{0, 0}, {0, 1}, {1, 0}},
						{{0, 0}, {0, 1}, {1, 1}}};
int n, m, board[20][20];
char a[20][20];
bool set(int x, int y, int type, int delta){
	bool ok = true;
	for(int i=0; i<3; i++){
		int nx = x+dd[type][i][0], ny = y+dd[type][i][1];
		if(nx<0 || ny<0 || nx>n-1 || ny>m-1) ok = false;
		else if((board[nx][ny] += delta)>1) ok = false;
	}
	return ok;
}
int solve(){
	int x = -1, y = -1;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			if(board[i][j]==0){
				x = i, y = j;
				break;
			}
		if(x!=-1) break;
	}
	if(x==-1) return 1;
	int ret = 0;
	for(int i=0; i<4; i++){
		if(set(x, y, i, 1)) ret += solve();
		set(x, y, i, -1);
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &m);
		int white_cnt = 0;
		for(int i=0; i<n; i++){
			scanf("%s", a[i]);
			for(int j=0; j<m; j++)
				if(a[i][j]=='.'){
					white_cnt ++;
					board[i][j]=0;
				}
				else
					board[i][j]=1;
		}
		printf("%d\n", white_cnt%3==0? solve(): 0);
	}
	return 0;
}
```

#### 시계 맞추기 168p

https://www.algospot.com/judge/problem/read/CLOCKSYNC

```c++
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> linked[10] = {{0, 1, 2},
						  {3, 7, 9, 11},
						  {4, 10, 14, 15},
						  {0, 4, 5, 6, 7},
						  {6, 7, 8, 10, 12},
						  {0, 2, 14, 15},
						  {3, 14, 15},
						  {4, 5, 7, 14, 15},
						  {1, 2, 3, 4, 5},
						  {3, 4, 5, 9, 13}};
const int INF = (int)1e9;
int Clock[16];		//clock() 원래 있는거라 이름 겹쳐서 에러 났었음.. 
bool check(){
	for(int i=0; i<16; i++)
		if(Clock[i] != 12) return false;
	return true;
}
void push(int pos){
	for(int x: linked[pos]){
		Clock[x] += 3;
		if(Clock[x] == 15) Clock[x]=3;
	}
}
int solve(int pos, int cnt){
	int res = INF;
	if(pos == 10){
		if(check()) res = cnt;
		return res;
	}
	for(int i=0; i<4; i++){
		res = min(res, solve(pos+1, cnt+i));
		push(pos);
	}
	return res;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		for(int i=0; i<16; i++)
			scanf("%d", &Clock[i]);
		int res = solve(0, 0);
		printf("%d\n", res != INF ? res : -1);
	}
	return 0;
}
```

