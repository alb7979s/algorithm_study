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

