## 정리

##### RMQ(Range Minimum Tree)

```c++
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF = (int)1e9;
struct RMQ {
	int n;
	//각 구간의 최소치
	vector<int> rangeMin;		
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || left > nodeRight) return INF;
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);		//query(0, n-1); 하면 루트부터 츄르륵 훑음
	}
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || index>nodeRight) return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};


```

##### 정렬된 수열의 특정 구간에서 최대 출현 빈도 계산 744p

```c++
struct RangeResult {
	int size;
	//가장 자주 등장하는 숫자의 출현 횟수
	int mostFrequent;
	//왼쪽 끝 숫자와 왼쪽 끝 숫자의 출현 횟수
	int leftNumber, leftFreq;
	//오른쪽
	int rightNumber, rightFreq;
};
RangeResult merge(const RangeResult& a, const RangeResult& b) {
	RangeResult ret;
	ret.size = a.size + b.size;
	ret.leftNumber = a.leftNumber;
	ret.leftFreq = a.leftFreq;
	if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
		ret.leftFreq += b.leftFreq;
	ret.rightNumber = b.rightNumber;
	ret.rightFreq = b.rightFreq;
	if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
		ret.rightFreq += a.rightFreq;
	ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
	if (a.rightNumber == b.leftNumber)
		ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);
	return ret;
}
```

##### 등산로 746p

https://algospot.com/judge/problem/read/MORDOR

```c++
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF = (int)1e9;
struct RMQ {
	int n;
	//각 구간의 최소치
	vector<int> rangeMin;		
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || left > nodeRight) return INF;
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);		//query(0, n-1); 하면 루트부터 츄르륵 훑음
	}
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || index>nodeRight) return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};
int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		vector<int> minh, maxh;
		int n, q;				//표지판 수, 등산로 수
		scanf("%d %d", &n, &q);
		for (int i = 0; i < n; i++) {
			int h;
			scanf("%d", &h);
			minh.push_back(h);
			maxh.push_back(-h);
		}
		RMQ rMinq(minh);
		RMQ rMaxq(maxh);
		while (q--) {
			int a, b;
			scanf("%d %d", &a, &b);
			int MIN = rMinq.query(a, b);
			int MAX = -rMaxq.query(a, b);
			printf("%d\n", MAX - MIN);
		}
	}
	return 0;
}
```

##### 족보 탐험 747p

https://algospot.com/judge/problem/read/FAMILYTREE

```c++

```

##### 펜윅트리(binary index tree)

```c++
//배열의 구간합
#include<cstdio>
#include<vector>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	int sum(int pos) {
		++pos;	//index 1부터 시작한다고 가정
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//LSB 지워가며 다음 구간 탐색
			pos &= (pos - 1);
		}
		return ret;
	}
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			//LSB 추출해서 더해가며 포함된 구간들 탐색
			pos += (pos & -pos);
		}
	}
};
```

##### 삽입 정렬 시간 재기 758p

https://algospot.com/judge/problem/read/MEASURETIME

```c++
#include<cstdio>
#include<vector>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	int sum(int pos) {
		++pos;	//index 1부터 시작한다고 가정
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//LSB 지워가며 다음 구간 탐색
			pos &= (pos - 1);
		}
		return ret;
	}
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			//LSB 추출해서 더해가며 포함된 구간들 탐색
			pos += (pos & -pos);
		}
	}
};
//펜윅 트리 이용한 풀이
long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}
int main() {
	int tc;
	scanf("%d", &tc);
	while(tc--) {
		int n;
		scanf("%d", &n);
		vector<int> a;
		for (int i = 0; i < n; i++) {
			int t;
			scanf("%d", &t);
			a.push_back(t);
		}
		printf("%d\n", countMoves(a));
	}
	return 0;
}
```

