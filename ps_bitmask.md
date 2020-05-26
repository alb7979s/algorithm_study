## 정리



##### 주의

1. 우선순위 ==, != 보다 낮음, 괄호로 처리하기

2. c++에서 1은 부호있는 32비트 상수로 취급, unisgned long long 쓰려면 1뒤에 ull 붙여줘야함

   ```
   unsigned long long a;
   (a & 1ull << b) > 0; 
   ```

3. 부호 있는 정수형 사용 :: 부호 있는 정수형에서 MSB는 음수 표현, 따라서 32비트 다 사용하려면 부호없는 정수형 써야함

4. N비트 정수를 N비트 이상 왼쪽을 시프트하면 안됨. c++언어 명세에 결과 정의 안되어 있음



##### 비트 연산자

```c++
a & b //and
a | b //or
a ^ b //xor
~a 	  //not
a<<b  //shift
```

###### 

##### 집합

```c++
//공집합
a = 0;
//꽉 찬 집합
a = (1<<n) - 1;
//p번째 원소 추가
a |= (1 << p);
//p번째 원소 포함 여부 확인
a & (1<<p);		//return값이 0 or 1<<p임
//p번째 원소 삭제
a &= ~(1<<p);	// a -= (1<<p)는 원소 없을때 큰일남
//p번째 원소 토글
a ^= (1<<p);
//두 집합에 대한 연산
a | b;  //합집합
a & b;  //교집합
a & ~b; //a-b 차집합
a ^ b;	//a와 b중 한 곳에만 포함된 집합
```



##### 집합의 크기 구하기

```c++
int bitCount(int x){
	if(x==0) return 0;
	return x%2 + bitCount(x/2);		//x%2==1이면(켜져있으면) 숫자 증가, x/2는 x>>1
}
//gcc/g++ :: __builtin_popcount(a) 로도 가능
```

##### 최소 원소 찾기

```c++
//2의 보수로 음수 표현은 비트별 not 연산 후 +1 해줌 그러므로
lsb = a & -a;
//2의 보수why? 컴퓨터 뺄셈 회로 없고 보수 회로만 있어서 뺄셈할땐 보수를 취하고 더해주면 됨
//gcc/g++ :: ++builtin_ctz(a) 로도 가능, 단 a!=0
```

##### 최소 원소 지우기

```c++
a &= a-1;		//a-1이 최하위비트 끄고 그 밑 비트 모두 키는 역할
```

##### 모든 부분 집합 순회

```c++
for(int subset = a; a; subset=(subset-1)&a){
	//subset은 a의 부분집합
}
```

#### 

##### 에라토스테네스의 체

```c++
#include<cstdio>
#include<cmath>
#include<cstring>
const int SIZE=1000;
int n;
unsigned char sieve[(SIZE+7)/8];
//k>>3 == k/8, k&7 == k%8
bool isPrime(int k){
	return sieve[k>>3] & (1<<(k&7));
}
void setComposite(int k){
	sieve[k>>3] &= ~(1<<(k&7));
}
void eratos(){
	memset(sieve, 255, sizeof(sieve));
	setComposite(0);
	setComposite(1);
	int sqrtn = sqrt(n);
	for(int i=2; i<=sqrtn; i++)
		if(isPrime(i))
			for(int j=i*i; j<=n; j+=i)
				setComposite(j);
}
int main(){
	scanf("%d",&n);
	eratos();
	for(int i=0; i<n; i++)
		if(sieve[i>>3] & 1<<(i&7)) printf("%d ", i);
	printf("\n");
	return 0;
}
```

##### 극대 안정 집합 588p

```c++

```

##### 졸업학기 590p

https://www.algospot.com/judge/problem/read/GRADUATION

```c++
#include<cstdio>
#include<cstring>
using namespace std;
#define min(a, b) ((a) < (b) ? (a) : (b))
const int INF=(int)1e9, SIZE=12;
int n, k, m, l;
int mem[10][1<<SIZE];
int classes[10], pre[SIZE];
int bitCount(int n){
	if(n==0) return 0;
	return n%2 + bitCount(n/2);
}
int solve(int pos,int taken){
	if(bitCount(taken) >= k) return 0;
	if(pos == m) return INF;
	int& ret = mem[pos][taken];
	if(ret!=-1) return ret;
	ret = INF;
	int canTake = classes[pos] & ~(taken);
	for(int i=0; i<n; i++)
		if((canTake & (1<<i)) && ((pre[i] & taken) != pre[i]))
			canTake &= ~(1<<i);
	for(int i=canTake; i; i=(i-1)&canTake){
		if(bitCount(i) > l) continue;
		ret = min(ret, solve(pos+1, taken | i)+1);
	}
	ret = min(ret, solve(pos+1, taken));
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		memset(mem, -1, sizeof(mem));	//testcase마다 초기화 해야는디 밖에서 시켜줘서 틀림 
		memset(classes, 0, sizeof(classes));
		memset(pre, 0, sizeof(pre));
		scanf("%d %d %d %d", &n, &k, &m, &l);
		int cnt, temp;
		for(int i=0; i<n; i++){
			scanf("%d", &cnt);
			while(cnt--){
				scanf("%d", &temp);
				pre[i] |= (1<<temp);		//1<<temp 줘야는디 temp줘서 틀림 
			}
		}
		for(int i=0; i<m; i++){
			scanf("%d", &cnt);
			while(cnt--){
				scanf("%d", &temp);
				classes[i] |= (1<<temp);
			}
		}
		int res = solve(0, 0);
		if(res==INF) printf("IMPOSSIBLE\n");
		else printf("%d\n", res);
	}
	return 0;
}
```

