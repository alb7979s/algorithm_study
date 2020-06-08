## 정리



##### a~b합: psum[b] - psum[a-1]

##### 분산

```c++
#include<cstdio>
#include<vector>
using namespace std;
typedef vector<int> VEC;
void init(VEC& psum, VEC& sqpsum, const VEC& a){
    psum[0] = a[0];
    for(int i=1; i<a.size(); i++){
        psum[i] = psum[i-1] + a[i];
    }
    sqpsum[0] = a[0]*a[0];
    for(int i=1; i<a.size(); i++){
        sqpsum[i] = sqpsum[i-1] + a[i]*a[i];
    }
}
int rangeSum(VEC& psum, int a, int b){
	if(a==0) return psum[b];
	return psum[b] - psum[a-1];
}
double variance(VEC& sqpsum, VEC& psum, int a, int b){
	double mean = rangeSum(psum, a, b) / double(b-a+1);
	double ret = rangeSum(sqpsum, a, b) - 2*mean*rangeSum(psum, a, b) + (b-a+1)*mean*mean;
	return ret / (b-a+1);
}
```

##### 2차원 부분합

```c++
//sum(x1, y1, x2, y2) = psum[x2, y2] - psum[x2, y1-1] - psum[x1-1, y2] + psum[x1-1, y1-1]
int gridSum(const vector<vector<int>>& psum, int x1, int x2, int y1, int y2){
    int ret = psum[x2][y2];
    if(x1 > 0) ret -= psum[x1-1][y2];
    if(y1 > 0) ret -= psum[x2][y1-1];
    if(x1>0 && y1>0) ret += psum[x1-1][y1-1];
    return ret;
}
```

##### 크리스마스 인형 602p

https://www.algospot.com/judge/problem/read/CHRISTMAS

```c++
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
const int MOD = 20091101;
int n, k;
int waysToBuy(const vector<int>& psum){
	vector<long long> cnt(k, 0);
	int res = 0;
	for(int i=0; i<psum.size(); i++) cnt[psum[i]]++;
	for(int i=0; i<k; i++)
		if(cnt[i] >=2)
			res = (res + (cnt[i] * (cnt[i]-1) / 2)) % MOD;	// %MOD해야는디 res+=로 계산했다가 틀림 
	return res;
}
int maxBuys(const vector<int>& psum){
	vector<int> ret(psum.size(), 0);
	vector<int> prev(k, -1);
	for(int i=0; i<psum.size(); i++){
		if(i>0) ret[i] = ret[i-1];
		else ret[i] = 0;
		int loc = prev[psum[i]];
		if(loc != -1) ret[i] = max(ret[i], ret[loc]+1);
		prev[psum[i]] = i;
	}
	return ret.back();
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &k);
		vector<int> a(n);
		for(int i=0; i<n; i++) scanf("%d", &a[i]);
		vector<int> psum(n+1, 0);
		for(int i=0; i<n; i++)
			psum[i+1] = (psum[i] + a[i])%k;
		printf("%d %d\n", waysToBuy(psum), maxBuys(psum));
	}
	return 0;
}
```

