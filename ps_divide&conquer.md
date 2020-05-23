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
#include<cstio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

typedef vector<int> VEC;
void normalize(VEC& num){
	num.push_back(0);
	for(int i=0; i<num.size()-1; i++){
		if(num[i] < 0){
			int borrow = ((abs(num[i])+9) / 10;
			num[i+1] -= borrow;
			num[i] += borrow;
		}
		else{
			num[i+1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while(num.size() > 1 && num.end()==0) num.pop_back();
}

VEC multi(VEC& a, VEC& b){
	VEC c(a.size() + b.size() - 1, 0);
	for(int i=0; i<a.size(); i++)	
		for(int j=0; j<b.size(); j++)
			c[i+j] += a[i] * b[j];
	normalize(c);
	return c;
}

void add(VEC& a, VEC& b, int k){
	int s = max(b.size() + k, a.size());
	a.resize(s, 0);
	b.resize(s, 0);
	for(int i=0; i<s-k; i++)
		a[i+k] += b[i];
}
void sub(VEC& a, VEC& b){
	int s = max(a.size(), b.size());
	a.resize(s, 0);
	b.resize(s, 0);
	for(int i=0; i<s; i++)
		a[i] -= b[i];
}
VEC karatsuba(VEC& a, VEC& b){
	if(a.size() < b.size()) return karatsuba(b, a);
	if(a.empty() || b.empty()) return VEC();
	if(a.size() <= 50) return multi(a, b);
	int half = a.size()/2;
	VEC a0(a.begin(), a.begin()+half);
	VEC a1(a.begin()+half, a.end());
	VEC b0(b.begin(), b.begin + min(b.size(), half));
	VEC b1(b.begin+min(b.size(), half), b.end());
	
	VEC z0, z1, z2;
	z0 = karatsuba(a0, b0);
	z2 = karatsuba(a1, b1);
	add(a0, a1, 0);
	add(b0, b1, 0);
	z1 = karatsuba(a0, b0);	//a0, b0가 더해져 있는 값들임 
	sub(z1, z0);
	sub(z1, z2);
	VEC res;
	add(res, z2, 0);
	add(res, z1, half);
	add(res, z0, half+half);
	return res;
}
	
	
```

