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

##### 팰린드롬 만들기 655p

https://www.algospot.com/judge/problem/read/PALINDROMIZE

```c++
#include<iostream>
#include<string>
#include<vector>
#include<algorithm> 			
using namespace std;
typedef vector<int> V;			//python이랑 헷갈려서 typedef앞에 #붙임..ㅋㅋㅋ
V getPartialMatch(const string& N){
	int m = N.size();
	V pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched < m){
		if (N[begin + matched] == N[matched]){
			matched++;
			pi[begin + matched - 1] = matched;		//[begin+matched] 했다가 RTE뜸
		}
		else{
			if (!matched) begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}
int solve(const string& S, const string& RS){
	int n = S.size(), m = RS.size();
	V pi = getPartialMatch(RS);
	int begin = 0, matched = 0;
	while (begin < n){
		if (matched<m && S[begin + matched] == RS[matched]){
			matched++;
			if ((begin + matched) == n) return n + n - matched;
		}
		else{
			if (!matched) begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}
int main(){
	int tc;
	cin >> tc;
	while (tc--){
		string S, RS;
		cin >> S;
		for (int i = S.size()-1; i >= 0; i--) RS += S[i];
		cout << solve(S, RS) << endl;
	}
	return 0;
}
```

##### 재하의 금고 658p

https://www.algospot.com/judge/problem/read/JAEHASAFE

```c++
#include<iostream>
#include<string>
#include<vector>
#include<algorithm> 			
using namespace std;
typedef vector<int> V;	
V getPartialMatch(const string& N){
	int m = N.size();
	V pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched < m){
		if (N[begin + matched] == N[matched]){
			matched++;
			pi[begin + matched - 1] = matched;		
		}
		else{
			if (!matched) begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}
int solve(const string& S, const string& RS){
	int n = S.size(), m = RS.size();
	V pi = getPartialMatch(RS);
	int begin = 0, matched = 0;
	while (begin < n){
		if (matched<m && S[begin + matched] == RS[matched]){
			matched++;
			if (matched == m) return begin;
		}
		else{
			if (!matched) begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}
int shift(const string& original, const string& target){
	return solve(original + original, target);
}
int main(){
	int tc;
	cin >> tc;
	while (tc--){
		int n;
		cin >> n;
		vector<string> dial;
		for (int i = 0; i <= n; i++){
			string temp;
			cin >> temp;
			dial.push_back(temp);
		}
		int res = 0;
		for (int i = 0; i < n; i++){
			if (i % 2 != 0) res += shift(dial[i], dial[i + 1]);
			else res += shift(dial[i + 1], dial[i]);
		}
		cout << res << endl;
	}
	return 0;
}
```

##### 접미사 배열

```c++
#include<string>		//string 자료형으로 쓰려면 cstring 아닌 string
#include<algorithm>
#include<iostream>
using namespace std;
const int SIZE = (int)1e6;
string str;
int n, t, g[SIZE], tg[SIZE], SA[SIZE];
bool cmp(int x, int y){
	if (g[x] == g[y]) return g[x + t] < g[y + t];
	return g[x] < g[y];
}
void getSA(const string& str){
	t = 1;
	n = str.size();
	for (int i = 0; i < n; i++){
		SA[i] = i;
		g[i] = str[i] - 'a';
	}
	while (t <= n){
		g[n] = -1;
		sort(SA, SA + n, cmp);
		tg[SA[0]] = 0;
		for (int i = 0; i < n; i++){
			if (cmp(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1;
			else tg[SA[i]] = tg[SA[i - 1]];
		}
		for (int i = 0; i < n; i++) g[i] = tg[i];
		t <<= 1;
	}
}
int main(){
	cin >> str;
	getSA(str);
	cout << endl << "[Suffix Array]" << endl;
	for (int i = 0; i < n; i++) cout << str.substr(SA[i]) << endl;
	return 0;
}
//출처: https://www.crocus.co.kr/613
```

##### 원형 문자열 668p

```c++
string minShift(const string& s){
    string s2 = s + s;
    getSA(s2);
    for(int i=0; i<s2.size(); i++)
        if(SA[i] <= s.size()) return s2.substr(SA[i], s.size());
    return "nope";
}
```

##### 서로 다른 부분 문자열의 수 669p

