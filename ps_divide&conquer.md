### 정리

---



#### 분할정복



#### -큰 수의 곱

```c++
//입출력 거꾸로 해줘야함
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
void normalize(vector<int>& num){
	num.push_back(0);
	for(int i=0; i<num.size()-1; i++){
		if(num[i]<0){
			int borrow = (abs(num[i])+9) / 10;
			num[i+1] -= borrow;
			num[i] += borrow * 10;
		}
		else{
			num[i+1] += num[i]/10;
			num[i] = num[i]%10;
		}
	while(num.size() > 1 && num.end()==0) num.pop_back();
}
vector<int> multiply(vector<int>& a, vector<int>& b){
	vector<int>c(a.size()+b.size()-1, 0);
	for(int i=0; i<a.size(); i++)
		for(int j=0; j<b.size(); j++)
			c[i+j] += a[i] * b[j];
	normalize(c);
	return c;
}
```

#### -카라츠바 알고리즘

```c++
#include<iostream>
#include<vector>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
typedef vector<int> VEC;

VEC multi(VEC& a, VEC& b){
	VEC c(a.size() + b.size() - 1, 0);
	for(int i=0; i<a.size(); i++)
		for(int j=0; j<b.size(); j++)
			c[i+j] = a[i] * b[j];
	//normalize(c);
	return c;
}

void add(VEC& a, VEC& b, int k){
	int s = max(a.size(), b.size()+k);
	a.resize(s, 0);
	b.resize(s, 0);
	for(int i=0; i<s-k; i++) a[i+k] += b[i];
}
void sub(VEC& a, VEC& b){
	int s = max(a.size(), b.size());
	a.resize(s, 0);
	b.resize(s, 0);
	for(int i=0; i<s; i++) a[i] -= b[i];
}
VEC kara(VEC& a, VEC& b){
	int an = a.size();
	int bn = b.size();
	if(an==0 && bn==0) return VEC();
	if(an < bn) return kara(b, a);
	if(an <= 50) return multi(a, b);
	int half = an/2;
	VEC a0(a.begin(), a.begin()+half);
	VEC a1(a.begin()+half, a.end());
	VEC b0(b.begin(), b.begin()+min<int>(half, b.size()));
	VEC b1(b.begin()+min<int>(half, b.size()), b.end());
	VEC z0 = kara(a0, b0);
	VEC z2 = kara(a1, b1);
	add(a0, a1, 0);
	add(b0, b1, 0);
	VEC z1 = kara(a0, b0);
	sub(z1, z0);
	sub(z1, z2);
	VEC ret;
	add(ret, z2, half+half);
	add(ret, z1, half);
	add(ret, z0, 0);
	return ret;
}
```

#### -쿼드트리 뒤집기 189p

https://www.algospot.com/judge/problem/read/QUADTREE

```c++
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE = 1000;
string str;

string reverse(string::iterator& it){
	char head = *(it++);
	if(head=='b' || head=='w') return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> str;
		string::iterator it = str.begin();	//parameter 보낼 때 요렇게 쓰는거구나 
		cout << reverse(it) << endl;
	}
	return 0;
}
```

#### -울타리 잘라내기 195p

https://www.algospot.com/judge/problem/read/FENCE

```c++
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int h[20000];
int solve(int l, int r){
	if(l == r) return h[l];
	int mid = (l+r)/2;
	int ret = max(solve(l, mid), solve(mid+1, r));
	//걸치는 사각형 
	int lo = mid, hi = mid+1;
	int height = min(h[lo], h[hi]);
	//mid, mid+1만 포함하는 너비 2인 사각형 고려 
	ret = max(ret, height*2);
	while(l < lo || hi < r){
		if(hi < r && (lo == l || h[lo-1] < h[hi+1])){
			hi++;
			height = min(height, h[hi]);
		}
		else{
			lo--;
			height = min(height, h[lo]);
		}
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		int n;
		scanf("%d", &n);
		for(int i=0; i<n; i++)
			scanf("%d", &h[i]);
		printf("%d\n", solve(0, n-1));
	}
	return 0;
}
```

#### -팬미팅 201p

https://www.algospot.com/judge/problem/read/FANMEETING

```c++
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
typedef vector<int> VEC;

int max(int a, int b){
	return a > b ? a : b;
}
int min(int a, int b){
	return a < b ? a : b;
}
VEC multi(VEC& a, VEC& b){
	VEC c(a.size()+b.size()-1, 0);
	for(int i=0; i<a.size(); i++)
		for(int j=0; j<b.size(); j++)
			c[i+j] += a[i] * b[j];
	return c;
}
void add(VEC& a, VEC& b, int k){
	int s = max(a.size(), b.size()+k);
	a.resize(s, 0);
	b.resize(s, 0);
	for(int i=0; i<s-k; i++) a[i+k] += b[i];
}
void sub(VEC& a, VEC& b){
	int s = max(a.size(), b.size());
	a.resize(s, 0);
	b.resize(s, 0);
	for(int i=0; i<s; i++) a[i] -= b[i];
}
VEC kara(VEC& a, VEC& b){
	int an = a.size();
	int bn = b.size();
	if(an < bn) return kara(b, a);
	if(!an && !bn) return VEC();
	if(an <= 100) return multi(a, b);
	int half = an/2;
	//a = a1*10**half + a0 로 가정해야 a0가 앞부분 가져감 (뒤집어서 받으니까)
    //a = a0*10**half + a1 으로 가정하고 a0에 앞부분 부터 놨다가 틀렸었음
	VEC a0(a.begin(), a.begin()+half);
	VEC a1(a.begin()+half, a.end());
	VEC b0(b.begin(), b.begin()+min(half, b.size()));
	VEC b1(b.begin()+min(half,b.size()), b.end());
	VEC z0 = kara(a0, b0);
	VEC z2 = kara(a1, b1);
	add(a0, a1, 0);
	add(b0, b1, 0);
	VEC z1 = kara(a0, b0);
	sub(z1, z0);
	sub(z1, z2);
	VEC ret;
	add(ret, z0, 0);
	add(ret, z1, half);
	add(ret, z2, half+half);
	return ret;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int tc;
	cin >> tc;
	while(tc--){
		string group, fan;
		cin >> group;
		cin >> fan;
		int N = group.size(), M = fan.size();
		VEC A(N), B(M);
		for(int i=0; i<N; i++) A[i] = (group[i] == 'M');
		for(int i=0; i<M; i++) B[M-i-1] = (fan[i] == 'M');
		VEC C = kara(A, B);
		int cnt=0;
		for(int i=N-1; i<M; i++)
			if(C[i] == 0) cnt++;
		cout << cnt << endl;
	}
	return 0;
}
```

