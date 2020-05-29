## 정리

##### kmp 알고리즘

```c++
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
typedef vector<int> VEC;
VEC getPartialMatch(const string& N){
	int m = N.size();
	VEC pi(m, 0);
	int begin=1, matched=0;
	while(begin + matched < m){
		if(N[begin+matched] == N[matched]){
			matched++;
			pi[begin + matched -1] = matched;
		}
		else{
			if(!matched) begin++;
			else{
				begin += matched-pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}
VEC kmp(const string& H, const string& N){
	int n = H.size(), m = N.size();
	VEC pi = getPartialMatch(N);
	VEC ret;
	int begin=0, matched=0;
	while(begin <= n-m){
		if(matched<m && H[begin+matched] == N[matched]){
			matched++;
			if(matched == m) ret.push_back(begin);
		}
		else{
			if(!matched) begin++;
			else{
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return ret;
}
```

```c++
//논문에 나온 구현
vector<int> kmp(const string& H, const string& N){
	int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);
    int matched = 0;
    for(int i=0; i<n; i++){
        while(matched>0 && H[i] != N[matched])
            matched = pi[matched-1];
        if(H[i] == N[matched]){
            matched++;
            if(matched==m){
                ret.push_back(i - m + 1);
                matched = pi[matched-1];
            }
        }
    }
    return ret;
}
```



##### 접두사/접미사 654p

https://www.algospot.com/judge/problem/read/NAMING#

```c++
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
vector<int> getPartialMatch(const string& a){
	int n = a.size();
	vector<int> pi(n, 0);
	int begin=1, matched=0;
	while(begin + matched < n){
		if(a[begin+matched] == a[matched]){
			matched++;
			pi[begin+matched-1] = matched;
		}
		else{
			if(!matched) begin++;
			else{
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}
void solve(const string& a){
	vector<int> pi = getPartialMatch(a);
	vector<int> ret;
	int k = a.size();
	while(k > 0){
		ret.push_back(k);
		k = pi[k-1];
	}
	while(!ret.empty()){
		cout << ret.back() << ' ';
		ret.pop_back();
	}
}
int main(){
	string a, b;
	cin >> a >> b;
	solve(a+b);
	return 0;
}
```

