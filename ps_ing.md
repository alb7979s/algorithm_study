```c++
//https://www.acmicpc.net/problem/17140
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
#define max(a, b) ((a) > (b) ? (a) : (b))
int r, c, k;
int a[101][101], cnt[101];
int solve(){
	int maxN = 3, maxM = 3;
	int t = 101;
	while (t){
		if (a[r-1][c-1] == k) return 101 - t;
		if (maxN <= maxM){
			for (int i = 0; i < maxN; i++){
				memset(cnt, 0, sizeof(cnt));
				for (int j = 0; j < maxM; j++){
					if (a[i][j])
						cnt[a[i][j]]++;
				}
				vector<pair<int, int>> v;
				for (int j = 0; j < 101; j++){
					if (cnt[j]) v.push_back({ cnt[j], j });
				}
				sort(v.begin(), v.end());
				maxN = max(maxN, v.size() * 2);
				int idx = 0;
				while (idx < 100){
					for (int j = 0; j < v.size(); j++){
						if (idx >= 100)break;
						int x = v[j].second, y = v[j].first;
						a[i][idx] = x;
						a[i][idx + 1] = y;
						idx += 2;
					}
					a[i][idx] = 0;
					idx++;
				}
			}
		}
		else{
			for (int i = 0; i < maxM; i++){
				memset(cnt, 0, sizeof(cnt));
				for (int j = 0; j < maxN; j++){
					if (a[j][i])
						cnt[a[j][i]]++;
				}
				vector<pair<int, int>> v;
				for (int j = 0; j < 101; j++){
					if (cnt[j]) v.push_back({ cnt[j], j });
				}
				sort(v.begin(), v.end());
				maxN = max(maxN, v.size() * 2);
				int idx = 0;
				while (idx < 100){
					for (int j = 0; j < v.size(); j++){
						if (idx >= 100)break;
						int x = v[j].second, y = v[j].first;
						a[idx][i] = x;
						a[idx + 1][i] = y;
						idx += 2;
					}
					a[idx][i] = 0;
					idx++;
				}
			}
		}
		t--;
	}
	return -1;
}
int main(){
	scanf("%d %d %d", &r, &c, &k);
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			scanf("%d", &a[i][j]);
	printf("%d\n", solve());
	return 0;
}
```

##### treap, priority queue

