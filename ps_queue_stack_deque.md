## 정리



##### 울타리 자르기 631p

https://www.algospot.com/judge/problem/read/FENCE

```c++
//스위핑 알고리즘 + 스택으로 O(N)
#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

vector<int> h;
int solveStack(){
	stack<int> remaining;
	h.push_back(0);
  	int ret = 0;
	for(int i=0; i<h.size(); i++){
		//남아 있는 판자 중 오른쪽 판자가 h[i]보다 높으면 이 판자는 끝
		while(!remaining.empty() && h[remaining.top()] >= h[i]){
			int j = remaining.top(); 	//남아 있는 것중 h[i] 보다 높은것들 처리
			remaining.pop();
			int width = -1;
			//j번째 판자 왼쪽에 판자가 없으면 left[j]=-1
			//아니면 남아 있는것중 가장 오른쪽(스택의 top)
			if(remaining.empty()) width = i;
			else width = (i - remaining.top() - 1);
			ret = max(ret, h[j]*width);
		}
		remaining.push(i);
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		h.clear();
		int n;
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			int temp;
			scanf("%d", &temp);
			h.push_back(temp);
		}
		printf("%d\n", solveStack());
	}
	return 0;
}
```

##### 짝이 맞지 않는 괄호 633p

https://www.algospot.com/judge/problem/read/BRACKETS2

```c++
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
string a;
bool solve(const string& a){
	string opening("({["), closing(")}]");
	stack<int> st;
	for(int i=0; i<a.size(); i++){
		if(opening.find(a[i]) != -1) st.push(opening.find(a[i]));
		else if(closing.find(a[i]) != -1){
			if(!st.empty() && st.top() == closing.find(a[i])) st.pop();
			else return false;
		}
	}
	if(!st.empty()) return false;
	return true;
}
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> a;
		printf(solve(a)? "YES\n" : "NO\n");
	}
	return 0;
}
```

##### 외계 신호 분석 635p

https://www.algospot.com/judge/problem/read/ITES

```c++
//온라인 알고리즘 활용
#include<cstdio>
#include<queue>
using namespace std;
struct RNG{
	unsigned seed;	//unsigned써서 2**32로 나눈 나머지 연산 할 필요 없어짐
	RNG() : seed(1983) {}
	unsigned next(){
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};

int countRanges(int k, int n){
	RNG rng;
	queue<int> q;
	int ret = 0, sum = 0;
	for(int i=0; i<n; i++){
		int newSignal = rng.next();
		sum += newSignal;
		q.push(newSignal);
		while(sum > k){
			sum -= q.front();
			q.pop();
		}
		if(sum==k) ret++;
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d" , &tc);
	while(tc--){
		int n, k;
		scanf("%d %d", &k, &n);
		printf("%d\n", countRanges(k, n));
	}
	return 0;
}
```

